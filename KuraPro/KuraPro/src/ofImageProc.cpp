#include"ofImageProc.h"


ofImageProc::ofImageProc(int color_w,int color_h,int depth_w,int depth_h,TABLE* table,int table_size,unsigned char max_ball_size){
	mIsFirst = true;
	mColorBuf.allocate(color_w, color_h, ofImageType::OF_IMAGE_COLOR_ALPHA);
	mDepthBuf[0].allocate(depth_w, depth_h, ofImageType::OF_IMAGE_GRAYSCALE);
	mDepthBuf[1].allocate(depth_w, depth_h, ofImageType::OF_IMAGE_GRAYSCALE);
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