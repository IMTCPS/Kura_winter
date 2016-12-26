#pragma once
#include<ofMain.h>
#include"ofAnimation.h"
#include"ofKinect.h"

//
extern string rollingSnowBall(ofAnimation* anim);

//壊れたときのモーション
extern string breakingSnowBall(ofAnimation* anim);

//===================================================

extern string a(ofAnimation* anim2);

//スタックを初期化したりする
extern string initSnowBall(ofAnimation* anim);

//描画を任されてる
extern void drawBall(ofAnimation* anim, ofImageManager* manager);

extern void a(ofAnimation* anim2, ofImageManager* manager2);

//これはキネクトの制御に用いる
extern unsigned char judgingByKinect(IBody**, int);
