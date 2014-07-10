#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofEnableAlphaBlending();
	ofSetFrameRate(60);
	ofBackground(22, 22, 22, 255);
    
	font.setup("Inconsolata.otf");//Vera.ttf"); // TODO: test with otf "Inconsolata.otf"
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    float x = 20;
	float y = 60;
    float fontSize = 28;
	
	string demoText = (string)"ofxFontStash can draw multiline text" + "\n" +
    "Here is another line" + "\n";
    
    string longText = "This text needs to be broken down line by line. At vero eos et accusamus et iusto odio dignissimos ducimus qui blanditiis praesentium voluptatum deleniti atque corrupti quos dolores et quas molestias excepturi sint occaecati cupiditate non provident, similique sunt in culpa qui officia deserunt mollitia animi, id est laborum et dolorum fuga. Et harum quidem rerum facilis est et expedita distinctio.";
    
    ofSetColor(255);
	//font.draw( demoText,  fontSize, x, y);
    font.drawMultiLine( demoText,  fontSize, x, y);
    
    font.drawMultiLine( longText,  fontSize*.5, x, 200);
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
