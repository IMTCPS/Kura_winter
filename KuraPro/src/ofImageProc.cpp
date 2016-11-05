#include"ofImageProc.h"


ofImageProc::ofImageProc(int color_w,int color_h,int depth_w,int depth_h,TABLE* table,int table_size,unsigned char max_ball_size){
	mIsFirst = true;
	mColorBuf.allocate(color_w, color_h);
	mDepthBuf[0].allocate(depth_w, depth_h);
	mDepthBuf[1].allocate(depth_w, depth_h);
	//テーブルの作成
	mPlayerTable = table;
	mTableSize = table_size;
	//テーブルのLUTを作成
	for (int i = 0; i < table_size; i++) {
#ifdef  USE_MULTI_THREADING
		//TODO
#else
		setLUT(&mPlayerTable[i]);
#endif //  USE_MULTI_THREADING

	}
	//出力用メモリ確保
	mAllocTable = new CIRCLE_INFO[max_ball_size];
	mAllocTableSize = max_ball_size;
}
ofImageProc::~ofImageProc() {
	delete[] mAllocTable;
	mColorBuf.clear();
	mDepthBuf[0].clear();
	mDepthBuf[1].clear();
}

void ofImageProc::setLUT(TABLE* table) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 256; j++) {
			if (table->min.t[i] <= j && table->max.t[i] >= j) {
				table->LUT[i][j] = 0x01;
			}
			else {
				table->LUT[i][j] = 0x00;
			}
		}
	}
}
void ofImageProc::setDepth(ofxCvGrayscaleImage depth) {
	int index = (mAddCounter++) % 2;
	//以下二回closing処理をする
	depth.dilate();
	depth.dilate();
	depth.erode();
	depth.erode();
	//データの更新
	depth.flagImageChanged();
	//最後にメンバ変数へ代入して終わり
	mDepthBuf[index] = depth;
}
void ofImageProc::setColor(ofxCvColorImage color) {
	color.convertRgbToHsv();
	color.flagImageChanged();
	mColorBuf = color;
}
int ofImageProc::Hough(ofxCvGrayscaleImage depth) {
	//平滑化処理
	depth.blurGaussian();
	cv::Mat work_img;
	//強引にデータを持ってくる(なぜかopenframeworksのオブジェクトとOpenCvのデータの互換性がない)
	work_img.data = const_cast<unsigned char*>(depth.getPixels().begin());
	//一時的に置いておく場所(そのまま出力用配列を渡すことができないので)
	vector<cv::Vec3f> temp;
	///ここの数値は要調整(CV_HOUGH_GRADIENTより以降のデータをいじってください)
	cv::HoughCircles(work_img, temp, CV_HOUGH_GRADIENT, 1, 100, 20, 50);
	//各データを出力用に書き込む
	vector<cv::Vec3f>::iterator it = temp.begin(), end = temp.end();
	//バッファオーバーフローのチェック
	if (temp.size() > mAllocTableSize) {
		cout << "hough error:Buffer Overfllow" << endl;
		return 0;
	}
	for (int i = 0; it != end;i++) {
		//データを送る(深度バッファのxは画面上のzとなり不要)
		mAllocTable[i].origin[0] = (*it)[0];
		mAllocTable[i].origin[1] = (*it)[1];
		mAllocTable[i].r = (*it)[2];
		//四捨五入して代入
		mAllocTable[i].y = mAllocTable[i].origin[1] + 0.5f;
	}
	return temp.size();
}
