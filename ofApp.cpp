#include "ofApp.h"
#include"Functions.h"

ofApp::ofApp() {}

ofApp::~ofApp() {
	list<ofAnimation*>::iterator it = m_AnimationList.begin(), end = m_AnimationList.end();
	while (it != end) {
		delete (*it);
		it = m_AnimationList.erase(it);
	}
}

//--------------------------------------------------------------
void ofApp::setup(){
//	ofSetVerticalSync(false);
//	ofSetFrameRate(0);
//	ofSetFullscreen(true);

	//アニメーションの登録(現在これで一個)
	ofAnimation* anim = new ofAnimation();
	ofAnimation* anim2 = new ofAnimation();
	//関数の指定(下３行のうち上ひとつと残りは同義なのだが、なぜかこうしないと登録されない)
	anim->setDrawFunc(drawBall, &m_Manager);
	
	anim2->setDrawFunc(drawBack, &m_Manager);

	anim->setUpdateFunc(REGIST_FUNC(initSnowBall));
	anim->setUpdateFunc(REGIST_FUNC(rollingSnowBall));
	anim->setUpdateFunc(REGIST_FUNC(breakingSnowBall));

	anim2->setUpdateFunc(REGIST_FUNC(BackGround));

	//ちょっとサンプルとしてウィンドウのサイズを登録
	anim->push("width", ofGetWidth());
	anim->push("height", ofGetHeight());

	//リスト追加
	m_AnimationList.push_back(anim);

	ofBackground(0, 0, 0);
	cout << "animation object:" << m_AnimationList.size() << endl;	//"cout"=オブジェクト.coutを通じ,文字列"Animation object:"を出力."endl"は改行.

	//ここでリソースの読み込みを全て行う
	m_Manager.setImage("snowman2", "snowman_release_2.png");
	m_Manager.setImage("ball", "snowball.png");
	m_Manager.setImage("back","background.png");
	stringstream path(""), key("");
	for (int i = 0; i < 8; i++) {
		path << "break_ball/" << i << ".png";
		key << "break_ball_" << i;
		m_Manager.setImage(key.str(), path.str());
		path.str(""); key.str("");
	}

//	m_Manager.setImage("snowman2", "snowman_release_2.png");
//	m_Manager.setImage("back", "background.png");
}

//--------------------------------------------------------------
void ofApp::update(){
	list<ofAnimation*>::iterator it = m_AnimationList.begin(), end = m_AnimationList.end();
	while (it != end) {
		(*it)->update();
		it++;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	//描画の制御
	list<ofAnimation*>::iterator it = m_AnimationList.begin(), end = m_AnimationList.end();
	while (it != end) {
		(*it)->draw();
		it++;
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
