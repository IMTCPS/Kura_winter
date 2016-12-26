#include"Functions.h"

 string rollingSnowBall(ofAnimation* anim){
	//y座標を取り出して-3している
	int y = anim->pop("y");
	anim->push("y", y - 3);
	if (anim->pop("y") < 0)return "breakingSnowBall";
	return "rollingSnowBall";
}

 string breakingSnowBall(ofAnimation* anim) {
	//画面を超えそうなので壊れるモーションを打ち込む;
	static int inc = 0;
	anim->push("x", 0);
	anim->push("y", 0);
	if ((inc++) % 5000 != 0) {
		anim->push("flag", anim->pop("flag") + 1);
	}
	return "breakingSnowBall";
}

//=========================================================

 string initSnowBall(ofAnimation* anim) {
	//スタックに必要な変数を初期化しつつ登録
	anim->push("x", 220);
	anim->push("y", anim->pop("height"));
	anim->push("w", 280);
	anim->push("h", 280);
	anim->push("flag", 0);
	return "rollingSnowBall";
}
//=========================================================

 string BackGround(ofAnimation* anim2) {
	 anim2->push("x", 320);
	 anim2->push("y", 240);
	 anim2->push("w", 80);
	 anim2->push("h", 80);
	 anim2->push("flag", 0);
	 return "background";
	 
 }

//=========================================================

 void drawBall(ofAnimation* anim, ofImageManager* manager) {
	static const char* file_key_list1[] = { "ball" };
	int index = anim->pop("flag");
	if (index >= 8)return;
	ofImage* img = NULL;
	//trueになった場合はアニメーションが起動
	if (index > 0) {
		stringstream key("");
		key << "break_ball_" << (index - 1);
		img = manager->getImage(key.str());
		anim->push("h", 660);
	}
	else {
		img = manager->getImage(file_key_list1[anim->pop("flag")]);
	}
	//最終的に描画
	if (img) {
		img->draw(anim->pop("x"), anim->pop("y"), anim->pop("w"), anim->pop("h"));
	}
}

 //========================================================

 void drawBack(ofAnimation* anim2, ofImageManager* manager2) {
	 static const char* file_key_list2[] = { "back" };
	 int index = anim2->pop("flag");
	 if (index >= 8)return;
	 ofImage* img = NULL;
	 img = manager2->getImage(file_key_list2[anim2->pop("flag")]);
	 //最終的に描画
	 if (img) {
		 img->draw(anim2->pop("x"), anim2->pop("y"), anim2->pop("w"), anim2->pop("h"));
	 }
 }

 unsigned char judgingByKinect(IBody** body, int size) {
	return 0;
}