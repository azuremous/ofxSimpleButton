#include "ofApp.h"

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
    
    imageButton.setup(220, 15, "button");
    
    animationImageButton.setup(220 + imageButton.getWidht() + 20, 15, "button");
    animationImageButton.setAsAnimationButton(400);
    animationImageButton.show();//also use show() when start to animation.
    
}

//--------------------------------------------------------------
void ofApp::update(){

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

    rectButton[0].mousePressed(x, y);
    
    if (rectButton[0].getIsSelect()) { rectButton[1].show(); }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

    if (rectButton[1].getIsSelect()) { rectButton[1].hide(); }
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
