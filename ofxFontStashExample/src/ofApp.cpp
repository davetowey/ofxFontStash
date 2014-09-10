#include "ofApp.h"


string titleText = "ofxFontStash";
string longText = "This text needs to be broken down line by line. At vero eos et accusamus et iusto odio dignissimos ducimus qui blanditiis praesentium voluptatum deleniti atque corrupti quos dolores et quas molestias excepturi sint occaecati cupiditate non provident, similique sunt in culpa qui officia deserunt mollitia animi, id est laborum et dolorum fuga. Et harum quidem rerum facilis est et expedita distinctio.";
string wrappedText = "";
int largeFontSize = 28;
int smallFontSize = 14;

//--------------------------------------------------------------
void ofApp::setup(){

    ofEnableAlphaBlending();
	ofSetFrameRate(60);
	ofBackground(22, 22, 22, 255);
    
    // default ttf only
    font.setup("Vera.ttf");//Inconsolata.otf");
    
    // for otfs, need to #define FONS_USE_FREETYPE in ofxFontStash.h (althought freetype doesn't render as nice)
    //font.setup("Inconsolata.otf");
    
    font.setLineHeight(1.5);
    
    int maxTextWidth = 280;
    wrappedText = font.wrapString(longText, smallFontSize, maxTextWidth);

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    
    float x = 20;
    float y = 60;
    
    // draw single line
    ofSetColor(0,255,255);
	font.draw( titleText,  largeFontSize, x, y);
    
    ofSetColor(255);
    // draw multiline text (left aligned)
    font.drawMultiLine( wrappedText,  smallFontSize, x, y + 40, FONS_ALIGN_LEFT);
    
    // centre aligned
    ofSetColor(255,255,0);
    font.drawMultiLine( wrappedText,  smallFontSize, x + 450, y + 40, FONS_ALIGN_CENTER);
    
    // right aligned
    ofSetColor(255,128);
    font.drawMultiLine( wrappedText,  smallFontSize, x + 900, y + 40, FONS_ALIGN_RIGHT);
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
