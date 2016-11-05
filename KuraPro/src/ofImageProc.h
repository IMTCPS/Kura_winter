//著者：長谷川　隆成
#pragma once
#include<ofMain.h>
#include<thread>
#include"ofxOpenCv\src\ofxOpenCv.h"

//以下をコメントアウトするとシングルスレッドになります(通常はマルチスレッディング)
//#define USE_MULTI_THREADING

#ifdef USE_MULTI_THREADING
#include"ofTaskQeue.h"
#endif

//こちらはkinectの取得したボールの情報(座標はスクリーン上のもの)
typedef struct _tCircleInfo {
	//四捨五入した位置(x方向はxの値が小さくなるほど誤差が大きいです)
	int x, y;
	//もとの位置データ(Hough変換の結果をそのまま保存)
	float origin[2];
	//ボールの大きさ
	float r;
	//色(領域の平均値を取得するので精度は悪いです)
	int id;
	//もとのデータから切り抜いた画像です
	ofxCvColorImage mColorBuffer;
	ofxCvGrayscaleImage mDepthBuffer;
} CIRCLE_INFO;
//HSV空間の構造体
typedef struct _tHSV {
	unsigned char t[3];
	unsigned char &h = t[0];//別名をつけたかった
	unsigned char &s = t[1];//別名をつけたかった
	unsigned char &v = t[2];//別名をつけたかった
} HSV;
//ボールの色をHSVで記録
typedef struct _tTable {
	HSV min, max;
	//Looking up tableの略であらかじめデータを計算しておく
	unsigned char LUT[3][256];
} TABLE;



//円とその色を距離センサおよび色センサから取得するためのクラス
class ofImageProc {
public:
	//最後、二つの引数はボールの色を指定(LUTは計算するので、maxとminだけ指定してください)
	ofImageProc(int color_w,int color_h,int depth_w,int depth_h,TABLE* table,int table_size,unsigned char max_ball_size = 0xff);
	~ofImageProc();

	//処理を実行(戻り値は検出したボールの情報群です)
	CIRCLE_INFO* update(ofImage color,ofImage depth,int* ret_size);
private:
	//デフォルトコンストラクタは禁止
	ofImageProc();

	//TABLE構造体のLUTを設定
	void setLUT(TABLE* table);

	//depth bufferを登録する(中では登録場所の更新及び、closingの処理を施しています)
	void setDepth(ofxCvGrayscaleImage depth);

	//color bufferを登録する(RGB空間 => HSV空間に変換します)
	void setColor(ofxCvColorImage color);

	//データがその範囲内か計算する(中で色バッファおよび深度バッファから切り取り、1x1に圧縮)
	bool judgeTable(int target_index,HSV ball_color);

	//出力用のデータの初期化
	void resetOutTable();

	//ハフ変換してデータを取得(平滑化処理も内部でやるので差分処理の結果をそのまま渡してください)
	int Hough(ofxCvGrayscaleImage depth);
private:
	//初回はDepth Bufferが足りないので処理を見逃すためのフラグです
	bool mIsFirst;
	//色の取得用なので最新のものだけを持ちます(RGB空間ではなく、HSV空間のものです)
	ofxCvColorImage mColorBuf;
	//差分処理をするため前のデータも持ちます(データは平滑化したものです)
	ofxCvGrayscaleImage mDepthBuf[2];
	//Depth bufferの追加位置を記録します
	unsigned int mAddCounter;
	//ボールの色の判別用に用いるテーブルです。開放はクラスのユーザーが開放してください
	TABLE* mPlayerTable;
	//テーブルの大きさです
	int mTableSize;
	//出力用メモリです(サイズが大きすぎるとメモリ不足になります)
	CIRCLE_INFO* mAllocTable;
	//確保したメモリサイズになるので参考に使ってください
	int mAllocTableSize;
#ifdef USE_MULTI_THREADING
	TaskQeue mThread;
#endif
};