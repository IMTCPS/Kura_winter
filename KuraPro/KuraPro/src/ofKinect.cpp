#include"ofKinect.h"
#include<Kinect.h>

#pragma comment(lib,"Kinect20.lib")

//ofKinectの真髄
namespace {
	//変数定義
	typedef unsigned char(*UPDATE_DEPTH)(unsigned short* buf,int w,int h);
	typedef unsigned char(*UPDATE_COLOR)(unsigned char* buf, int w, int h);
	//ofKinectクラスの実装クラス
	class ofKinectImpl {
	private:
		IKinectSensor* mSensor;
		HRESULT mLatestResult;
		//Depth Buffer
		IDepthFrameReader* mDepthReader;
		UPDATE_DEPTH mDepthFunc;
		//Color Buffer
		IColorFrameReader* mColorReader;
		UPDATE_COLOR mColorFunc;
	public:
		ofKinectImpl() :mSensor(NULL),
						mLatestResult(S_OK),
						mDepthReader(NULL),
						mDepthFunc(NULL),
						mColorReader(NULL),
						mColorFunc(NULL)
		{}
		bool open(){
			mLatestResult = GetDefaultKinectSensor( &mSensor );
			if ( SUCCEEDED(mLatestResult) ) {
				mLatestResult = mSensor->Open();
			}
			else return false;
			return true;
		}
		~ofKinectImpl() {
			if ( mDepthReader ) {
				mDepthReader->Release();
				mDepthReader = NULL;
			}
			if ( mColorReader ) {
				mColorReader->Release();
				mColorReader = NULL;
			}
			mSensor->Close();
			mSensor = NULL;
		}
		bool EnableDepth(UPDATE_DEPTH func) {
			mDepthFunc = func;
			//DepthReaderの取得
			IDepthFrameSource* pDepthSource;
			mLatestResult = mSensor->get_DepthFrameSource(&pDepthSource);
			if (SUCCEEDED(mLatestResult)) {
				mLatestResult = pDepthSource->OpenReader(&mDepthReader);
			}
			else {
				mDepthFunc = NULL;
				return false;
			}
			pDepthSource->Release();
			return true;
		}
		bool EnableColor(UPDATE_COLOR func){
			mColorFunc = func;
			//ColorReaderの取得
			IColorFrameSource* pColorSource;
			mLatestResult = mSensor->get_ColorFrameSource(&pColorSource);
			if (SUCCEEDED(mLatestResult)) {
				mLatestResult - pColorSource->OpenReader(&mColorReader);
			}
			else {
				mColorFunc = NULL;
				return false;
			}
			pColorSource->Release();
			return true;
		}
		HRESULT getResult() { return mLatestResult; }
		bool isEnableDepth() { return (mDepthReader != NULL); }
		bool isEnableColor() { return (mColorReader != NULL); }
		void update() {
			//アプリ開始直後はKinectが取得できないことがあるので一応確認
			if (mSensor) {
				//DepthBufferを取得
				unsigned short* buffer;
				unsigned int buffer_size;
				IDepthFrame* pDepthFrame;
				if (mDepthReader) {
					mLatestResult = mDepthReader->AcquireLatestFrame(&pDepthFrame);
					if (SUCCEEDED(mLatestResult)) {
						mLatestResult = pDepthFrame->AccessUnderlyingBuffer(&buffer_size, &buffer);
						if (SUCCEEDED(mLatestResult)) {
							//関数ポインタで関数を呼び出す
							mDepthFunc(buffer,512,384);
						}
					}
					pDepthFrame->Release();
					pDepthFrame = NULL;
				}
			}
			return;
		}
	};
}
//上記のクラスのインスタンス
static ofKinectImpl* gImpl = NULL;


//ofKinectクラスのメンバ関数の定義
ofKinect::ofKinect() {
	if (!gImpl) {
		gImpl = new ofKinectImpl();
	}
}
ofKinect::~ofKinect() {
	if (gImpl)delete gImpl;
	gImpl = NULL;
}

bool ofKinect::Open() {
	if (gImpl) {
		return gImpl->open();
	}
	return false;
}
void ofKinect::Release() {
	if (gImpl) {
		delete gImpl;
		gImpl = NULL;
	}
}
ofKinect& ofKinect::instance() {
	static ofKinect inst;
	return inst;
}

bool ofKinect::isEnableDepth() {
	if (!gImpl)return false;
	return gImpl->isEnableDepth();
}
bool ofKinect::isEnableColor() {
	if (!gImpl)return false;
	return gImpl->isEnableColor();
}
bool ofKinect::EnableDepth(unsigned char(*update)(unsigned short* buf,int w,int h)) {
	if (!gImpl)return false;
	return gImpl->EnableDepth(update);
}
bool ofKinect::EnableColor(unsigned char(*func)(unsigned int* buf, int w, int h)) {
	if (!gImpl)return false;
	return gImpl->EnableColor((UPDATE_COLOR)func);
}
void ofKinect::Update() {
	if (!gImpl)return;
	gImpl->update();
}
HRESULT ofKinect::GetLatestResult() {
	if (!gImpl)return -1;
	return gImpl->getResult();
}
