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
	
    ofSetColor(255);
    
    float x = 20;
    float y = 60;
    
    // draw single line
	font.draw( titleText,  largeFontSize, x, y);
    
    // draw multiline text (left aligned)
    font.drawMultiLine( wrappedText,  smallFontSize, x, y + 40, FONS_ALIGN_LEFT);
    
    // centre aligned
    font.drawMultiLine( wrappedText,  smallFontSize, x + 450, y + 40, FONS_ALIGN_CENTER);
    
    // right aligned
    font.drawMultiLine( wrappedText,  smallFontSize, x + 900, y + 40, FONS_ALIGN_RIGHT);
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::touchDown(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void ofApp::touchMoved(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void ofApp::touchUp(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void ofApp::touchDoubleTap(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void ofApp::touchCancelled(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void ofApp::lostFocus(){

}

//--------------------------------------------------------------
void ofApp::gotFocus(){

}

//--------------------------------------------------------------
void ofApp::gotMemoryWarning(){

}

//--------------------------------------------------------------
void ofApp::deviceOrientationChanged(int newOrientation){

}
