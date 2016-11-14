#include "ofApp.h"

#define SEQUENCE_TITLE		0x00000000
#define SEQUENCE_GAME		0x00000001
#define SEQUENCE_RESULT		0x00000002

//--------------------------------------------------------------
void ofApp::setup(){
	//TODO:ここで各自の初期化関数を呼び出してください
}

//--------------------------------------------------------------
void ofApp::update(){
	//ここではSequence処理をします(関数ポインタでデータを管理した方が高速だが、初心者には見づらいのでこちらの方式を用います)
	switch (mType) {
		case SEQUENCE_TITLE:
			//TODO:タイトル画面
			break;
		case SEQUENCE_GAME:
			//TODO:ゲーム中の画面
			break;
		case SEQUENCE_RESULT:
			//TODO:結果画面
			break;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	//TODO:画面を初期化します
	//TODO:背景を出力します
	//TODO:ここはアニメーションを表示など背景以外を描写してください
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
