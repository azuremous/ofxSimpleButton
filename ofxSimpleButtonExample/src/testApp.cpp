#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    rectButton[0].setup(30, 30, 30, 30, true);
    rectButton[0].setAppear(true);//You need setup for button appear
    rectButton[0].setName("first triiger",-10,-5);
    
    rectButton[1].setup(30, 100, 50, 50, false);
    rectButton[1].setAppear(false);
    rectButton[1].setRender(false);
    rectButton[1].setName("second trigger",-10,-5);
    
    circleButton[0].setup(200, 30, 30, 30, true, TOGGLE ,CIRCLE_BUTTON);
    circleButton[0].setAppear(true);
    circleButton[0].setName("toggle button", 35);
    
    ofColor a;
    a.set(255, 0, 0);
    circleButton[1].setup(200, 100, 30, 30, true,BUTTON, CIRCLE_BUTTON, true, a);
    
    imageButton.setup(400, 30, "img/button", true);//it works with png
    imageButton.setAppear(true);
    
    //This button not appear but work with image.
    image[0].loadImage("img/button.png");
    image[1].loadImage("img/button_.png");
    dummyButton.setup(400, 100, image[0].getWidth(), image[0].getHeight(), true);
    dummyButton.setAppear(true);
    dummyButton.setRender(false);
    numImg = false;

}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    
    circleButton[1].render();
    ofPushMatrix();
    ofPushStyle();
    ofEnableAlphaBlending();
    ofSetColor(255);
    ofTranslate(dummyButton.getX(), dummyButton.getY());
    image[numImg].draw(0, 0);
    ofDisableAlphaBlending();
    ofPopStyle();
    ofPopMatrix();
    
    
    ofDrawBitmapString("image buttons", imageButton.getX(), imageButton.getY() - 3);
    ofDrawBitmapString("firtly toggle button On", circleButton[1].getX(), circleButton[1].getY() - 10);

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    rectButton[1].press(x, y);
    dummyButton.press(x, y);
    if(rectButton[1].bSelected()){ //if you setup eventPress is false, you can make your own action
        a_s = !a_s;
        rectButton[0].setRender(a_s);
    }
    
    numImg = dummyButton.bSelected();

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

    
    if (rectButton[0].bSelected()) {
        rectButton[1].setAppear(true);
        rectButton[1].setRender(rectButton[1].getIsAppear());
        a_s = rectButton[1].getIsRender();
    }
    
    circleButton[1].setAppear(circleButton[0].bSelected());//When circle button 0 be selected, circle button 1 will works.
    
    numImg = false;
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}