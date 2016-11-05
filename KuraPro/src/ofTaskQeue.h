#pragma once
#include<thread>
#include<future>
#include<list>
#include<vector>

class ofTaskBase {
public:
	virtual ~ofTaskBase();
	virtual void run() = 0;
};

class ofTaskQeue {
public:
	ofTaskQeue();
	ofTaskQeue(int thred_num);
	~ofTaskQeue();

	//登録するための関数です。(関数を汎用的に登録するため先頭にいろいろ付いています)
	template<class Ret,class F,class... Args>
	std::promise<Ret> pushTask(F&& func_name,Args&&... args);

	//クラス単位での並列処理をする場合はこちらで指定してください(条件としてofTaskBaseを継承しているクラスです)
	void pushTask(ofTaskBase*);

	//このクラスが管理している全てのスレッドを停止します
	void join();

	//スレッドの数を返します
	unsigned int size();

	//スレッド数を変えます(増やすことしかできません)
	void resize(int add);

	//現在待機中の処理の数を示します
	void getTaskNum();
private:
	//実際にスレッド毎で実行される関数です(無限ループになっているので、他の人は呼ばないでください)
	void process();

	//セマフォの初期化を行います
	void initSemaphore(int start_counter,int min,int max);

	//セマフォの終了処理を行います
	void releaseSemaphore();

	//セマフォのカウンタを引数の数値分、増やします(値が最大値を超える場合は強制的に最大値になります)
	void increaseSemaphore(int size);

	//セマフォのカウンタを引数の数値分、減らします(値が最小値を超える場合は強制的に最小値になります)
	void decreaseSemaphore(int size);

	//listからデータを取得します(要素がなかった場合は追加されるまで待ちます)
	ofTaskBase* pop();

	//listへ要素を追加します
	void push(ofTaskBase*);
private:
	std::list<ofTaskBase*> mQeue;
	//以下二つはセマフォにするための変数(listの要素数をセマフォで管理をします)
	std::mutex mQeueLock,mSemaphoreLock;
	int mCounter;
	//実際に実行するスレッド群
	std::vector<std::thread> mThreads;
};