#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofEnableAlphaBlending();
	ofSetFrameRate(60);
	ofBackground(22, 22, 22, 255);
    
	font.setup("Vera.ttf"); // TODO: test with otf "Inconsolata.otf"
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    float x = 20;
	float y = 20;
    float fontSize = 28;
	
	string demoText = (string)"ofxFontStash can draw multiline text" + "\n" +
    "Here is another line" + "\n";
    
    ofSetColor(255);
	font.draw( demoText,  fontSize, x, y);
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
