#include "ofApp.h"

float a = 0.;
float acc = 0.1;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetCircleResolution(80);
    ofEnableSmoothing();
    
    rectButton[0].setup(30, 30, 30, 30, false, false); //x, y, width, height, useEvent, manualRender
    rectButton[0].setName("trigger");
    
    rectButton[1].setup(30, 90);
    rectButton[1].setName("hide button");
    rectButton[1].setColor(ofColor::orange);
    rectButton[1].setToggleColor(ofColor::paleGreen);
    rectButton[1].hide();
    
    circleButton.setup(110, 25, 40, 40, true, true, TYPE_TOGGLE, BUTTON_CIRCLE);
    circleButton.setName("toggle", circleButton.getWidht() + 5, circleButton.getHeight()/2);
    circleButton.show();//If manualRender's value is a true, you need to use show() for displaying button.
    
    imageButton.setup(220, 15, "button.png", true);
    
    animationImageButton.setup(220 + imageButton.getWidht() + 20, 15, "button.png", true);
    animationImageButton.setAsAnimationButton(400);
    animationImageButton.show();//also use show() when start to animation.
}

//--------------------------------------------------------------
void ofApp::update(){
    a+= acc;
    if(a >= 1.0 || a < 0.0){ acc *= -1.; }
    imageButton.setAlpha(a);
}

//--------------------------------------------------------------
void ofApp::draw(){
    circleButton.render();
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
