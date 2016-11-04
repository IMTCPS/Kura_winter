//著者：長谷川　隆成
#pragma once
#include"ofMain.h"

//kinect v2の制御
class ofKinect {
public:
	~ofKinect();

	//このクラスを使用するときtrueが返されるまで呼んでください(中身は初期化処理が書いてあります)
	static bool Open();

	//このクラスを使用しなくなったら以下で終了させてください(プログラム終了時などにお願いします)
	static void Release();

	//このクラスはインスタンスを作成できないので、以下の関数から直接使ってください
	//例)ofKinect::instance().Update();
	static ofKinect& instance();

	//Depth bufferの取得準備の有無を返します(kinect自身がオープンしていない場合もfalseになります)
	bool isEnableDepth();
	
	//Color bufferの取得準備の有無を返します(上記同様、kinect自身によってfalseも返します)
	bool isEnableColor();

	//失敗時：falseを返します
	//引数は取得データの処理を書いた関数のポインタです。詳細は各自で調べてください。
	bool EnableDepth(unsigned char(*update)(unsigned short* buf,int w,int h));

	//失敗時：falseを返します
	//引数は取得データの処理を書いた関数のポインタです。詳細は各自で調べてください。また、サイズは一画素につき4byteです。
	bool EnableColor(unsigned char(*update)(unsigned int* buf,int w,int h));

	//Kinectからデータを取得します(毎フレーム読んで頂ければ大丈夫です)
	void Update();

	//最新の結果を返します(大抵の結果は戻り値でわかりますが、Update()で呼ばれた関数の戻り値はこちらで取得します)
	HRESULT GetLatestResult();
private:
	//シングルトンにするためにコンストラクタを使用することはこのクラス自身しかできません
	ofKinect();
	//以下のコピー系関数は使用禁止です(定義すらしないことで使用時、コンパイルエラーになりわかりやすいです)
	ofKinect(const ofKinect&);
	ofKinect& operator=(const ofKinect&);
};