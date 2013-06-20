//
//  ofxSimpleButton.cpp
//
//  Created by kim jung un a.k.a azuremous on 12/10/12.
//  Copyright (c) 2012 azuremous.net All rights reserved.
//

#include "ofxSimpleButton.h"

//--------------------------------------------------------------
/*public */ofxSimpleButton::ofxSimpleButton()
:bImgButton(false)
,appear(true)
,useName(false)
,selected(false)
,buttonRender(true)
,bePressed(false)
{
    pressedColor.set(255, 255, 0);
    
}

//--------------------------------------------------------------
/*public */ofxSimpleButton::~ofxSimpleButton(){}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::setup(float x, float y, float w, float h, bool eventPress, BUTTON_TYPE _buttonType, BUTTON_SHAPE _buttonShape, bool setManualRender,const ofColor &_color)
{
    
    setButtonType(_buttonType);
    setButtonShape(_buttonShape);
    setAppear(true);
    buttonColor = _color;
    AreaRect.set(x, y, w, h);
    
    if(ofGetTargetPlatform() == OF_TARGET_IPHONE){
     
        if (eventPress) ofAddListener(ofEvents().touchDown, this, &ofxSimpleButton::down);
        ofAddListener(ofEvents().touchUp, this, &ofxSimpleButton::up);
        
    }else{
        
        if (eventPress) ofAddListener(ofEvents().mousePressed , this, &ofxSimpleButton::press);
        ofAddListener(ofEvents().mouseReleased, this, &ofxSimpleButton::released);
    }
    
    if (!setManualRender) {
        ofAddListener(ofEvents().draw, this, &ofxSimpleButton::render);
    }
    
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::setup(float x, float y, string buttonImageName, bool eventPress, BUTTON_TYPE _buttonType, bool setManualRender)//set image button
{
    
    setButtonType(_buttonType);
    
    char * dummyName = new char[50];
    sprintf(dummyName, ".png");
    string _buttonImgName = buttonImageName;
    _buttonImgName.append(dummyName);
    
    buttonImg[0].loadImage(_buttonImgName);
    
    string _buttonImgName_p = buttonImageName.append(1,'_');
    _buttonImgName_p.append(dummyName);
    
    buttonImg[1].loadImage(_buttonImgName_p);
    
    _buttonImgName_p.clear();
    _buttonImgName.clear();
    delete [] dummyName;
    
    
    setAppear(true);
    AreaRect.set(x, y, buttonImg[0].getWidth(), buttonImg[0].getHeight());
    bImgButton = true;
    
    if(ofGetTargetPlatform() == OF_TARGET_IPHONE){
        if (eventPress) ofAddListener(ofEvents().touchDown, this, &ofxSimpleButton::down);
        ofAddListener(ofEvents().touchUp, this, &ofxSimpleButton::up);
        
    }else{
        if (eventPress) ofAddListener(ofEvents().mousePressed , this, &ofxSimpleButton::press);
        ofAddListener(ofEvents().mouseReleased, this, &ofxSimpleButton::released);
    }
    
    if (!setManualRender) ofAddListener(ofEvents().draw, this, &ofxSimpleButton::render);
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::setName(string _buttonName,float name_x, float name_y){
    
    buttonName = _buttonName;
    useName = true;
    namePos.set(name_x, name_y);
    setAppear(true);
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::useMouseMoved()
{
    ofAddListener(ofEvents().mouseMoved, this, &ofxSimpleButton::movedMouse);
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::useTouchMoved()
{
    ofAddListener(ofEvents().touchMoved, this, &ofxSimpleButton::movedTouch);
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::render(){
    
    if (buttonRender) {
        
        ofPushMatrix();
        ofTranslate(AreaRect.x, AreaRect.y);
        
        if (useName) {
            ofPushStyle();
            ofSetColor(buttonColor);
            ofDrawBitmapString(buttonName, namePos);
            ofPopStyle();
        }
        
        if (bImgButton) {
            ofEnableAlphaBlending();
            ofSetColor(255);
            if (!selected) { buttonImg[0].draw(0, 0); }
            else { buttonImg[1].draw(0, 0); }
            ofDisableAlphaBlending();
        
        }else {
            ofPushStyle();
            ofNoFill();
            ofSetLineWidth(2);
            ofSetColor(buttonColor,255);
            if (buttonShape) { ofEllipse(AreaRect.width/2, AreaRect.height/2, AreaRect.width,AreaRect.height); }
            else { ofRect(0, 0, AreaRect.width, AreaRect.height);}
            ofPopStyle();
            
            if (selected){
                ofPushStyle();
                ofSetColor(pressedColor);
                if (buttonShape) { ofEllipse(AreaRect.width/2, AreaRect.height/2, AreaRect.width - (AreaRect.width / 10 * 2),AreaRect.height - (AreaRect.width / 10 * 2));}
                else{ ofRect(AreaRect.width / 10 , AreaRect.width / 10, AreaRect.width - (AreaRect.width / 10 * 2), AreaRect.height - (AreaRect.width / 10 * 2));}
                ofPopStyle();
            }
        }
        ofPopMatrix();
    }
    
}


//--------------------------------------------------------------
/*public */void ofxSimpleButton::render(ofEventArgs &event)
{
    
    if (buttonRender) {
        
        ofPushMatrix();
        ofTranslate(AreaRect.x, AreaRect.y);
        
        if (useName) {
            ofPushStyle();
            ofSetColor(buttonColor);
            ofDrawBitmapString(buttonName, namePos);
            ofPopStyle();
        }
        
        if (bImgButton) {
            ofEnableAlphaBlending();
            ofSetColor(255);
            if (!selected) { buttonImg[0].draw(0, 0); }
            else { buttonImg[1].draw(0, 0); }
            ofDisableAlphaBlending();
        }else {
            ofPushStyle();
            ofNoFill();
            ofSetLineWidth(2);
            ofSetColor(buttonColor,255);
            if (buttonShape) { ofEllipse(AreaRect.width/2, AreaRect.height/2, AreaRect.width,AreaRect.height); }
            else { ofRect(0, 0, AreaRect.width, AreaRect.height);}
            ofPopStyle();
            
            if (selected){
                ofPushStyle();
                ofSetColor(255, 255, 0);
                if (buttonShape) { ofEllipse(AreaRect.width/2, AreaRect.height/2, AreaRect.width - (AreaRect.width / 10 * 2),AreaRect.height - (AreaRect.width / 10 * 2));}
                else{ ofRect(AreaRect.width / 10 , AreaRect.width / 10, AreaRect.width - (AreaRect.width / 10 * 2), AreaRect.height - (AreaRect.width / 10 * 2));}
                ofPopStyle();
            }
        }
        ofPopMatrix();
    }
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::down(ofTouchEventArgs &touch)
{
    if (touch.id == 0 && pressed(touch.x, touch.y)) buttonAction();
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::press(ofMouseEventArgs &mouse)
{
    if (pressed(mouse.x, mouse.y)) buttonAction();
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::press(float x, float y)
{
     if (pressed(x, y)) buttonAction();
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::up(ofTouchEventArgs &touch)
{
    if (!buttonType && selected){
        selected = bePressed = false;
    }else{
        bePressed = false;
    }
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::released(ofMouseEventArgs &mouse)
{
    if (!buttonType && selected){
        selected = bePressed = false;
    }else{
        bePressed = false;
    }
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::movedTouch(ofTouchEventArgs &touch){
    if (pressed(touch.x, touch.y)) {
        buttonAction();
    }else{
        selected = false;
    }
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::movedMouse(ofMouseEventArgs &mouse){
    if (pressed(mouse.x, mouse.y)){
        buttonAction();
    }else{
        selected = false;
    }
}

//--------------------------------------------------------------
/*protected */void ofxSimpleButton::buttonAction(){
    
    switch (buttonType) {
        case 0:
            selected = true;
            break;
        case 1:
            selected = !selected;
            break;
    }
}

//--------------------------------------------------------------
/*protected */bool ofxSimpleButton::pressed(float x, float y)
{
    if (!appear) return false;
    return bePressed = x>= AreaRect.x && x <= AreaRect.x + AreaRect.width && y >= AreaRect.y && y <= AreaRect.y + AreaRect.height ;
}

//--------------------------------------------------------------
/*public */ofxSimpleSlider::ofxSimpleSlider()
:SliderColor(ofColor(255,255,255))
,MaxVlaue(127)
,valueChanged(false)
{}

//--------------------------------------------------------------
/*public */ofxSimpleSlider::~ofxSimpleSlider(){}

//--------------------------------------------------------------
/*public */void ofxSimpleSlider::setup(float x, float y, float w, float h, bool bHorizontal){
    
    if (bHorizontal) {
        button.setup(x, y, h, h, true, BUTTON, RECT_BUTTON, true);//set manual render;
    }else{
        button.setup(x, y, w, w, true, BUTTON, RECT_BUTTON, true);//set manual render;
    }
    bHorz = bHorizontal;
    AreaRect.set(x, y, w, h);
    
    if(ofGetTargetPlatform() == OF_TARGET_IPHONE){
        ofAddListener(ofEvents().touchDown, this, &ofxSimpleSlider::moveButtonTouch);
        ofAddListener(ofEvents().touchMoved, this, &ofxSimpleSlider::moveButtonTouch);
        ofAddListener(ofEvents().touchUp, this, &ofxSimpleSlider::resetValueTouch);
    }else{
        ofAddListener(ofEvents().mousePressed, this, &ofxSimpleSlider::moveButtonMouse);
        ofAddListener(ofEvents().mouseDragged, this, &ofxSimpleSlider::moveButtonMouse);
        ofAddListener(ofEvents().mouseReleased, this, &ofxSimpleSlider::resetValueMouse);
    }
}

//--------------------------------------------------------------
/*public */void ofxSimpleSlider::render(){
    
    ofPushMatrix();
    ofPushStyle();
    ofNoFill();
    ofSetLineWidth(2);
    ofSetColor(SliderColor);
    ofRect(AreaRect);
    ofPopStyle();
    ofPopMatrix();
    button.render();
}

//--------------------------------------------------------------
/*protected */void ofxSimpleSlider::moveButtonTouch(ofTouchEventArgs &touch){
    
    if (bHorz) {
        if (touch.y > AreaRect.y - 3 && touch.y < AreaRect.y+ AreaRect.height + 3) {
            float barwidth = touch.x;
            if (barwidth <= AreaRect.x) { barwidth = AreaRect.x; }
            else if (barwidth >= AreaRect.x + AreaRect.width - AreaRect.height){
                barwidth = AreaRect.x + AreaRect.width - AreaRect.height;
            }
            value = (int)ofMap(barwidth, AreaRect.x, AreaRect.x + AreaRect.width - AreaRect.height, 0, MaxVlaue);
            button.setPos(barwidth, AreaRect.y);
            valueChanged = true;
        }
    }
}

//--------------------------------------------------------------
/*protected */void ofxSimpleSlider::resetValueTouch(ofTouchEventArgs &touch){ valueChanged = false; }

//--------------------------------------------------------------
/*protected */void ofxSimpleSlider::moveButtonMouse(ofMouseEventArgs &mouse){
    
    if (bHorz) {
        if (mouse.y > AreaRect.y - 3 && mouse.y < AreaRect.y+ AreaRect.height + 3) {
            float barwidth = mouse.x;
            if (barwidth <= AreaRect.x) { barwidth = AreaRect.x; }
            else if (barwidth >= AreaRect.x + AreaRect.width - AreaRect.height){
                barwidth = AreaRect.x + AreaRect.width - AreaRect.height;
            }
            value = (int)ofMap(barwidth, AreaRect.x, AreaRect.x + AreaRect.width - AreaRect.height, 0, MaxVlaue);
            button.setPos(barwidth, AreaRect.y);
            valueChanged = true;
        }
    }
}

//--------------------------------------------------------------
/*protected */void ofxSimpleSlider::resetValueMouse(ofMouseEventArgs &mouse){ valueChanged = false; }
