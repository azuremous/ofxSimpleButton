//
//  ofxSimpleButton.cpp
//  ofxSimpleButton
//
//  Created by kim jung un a.k.a azuremous on 12/10/12.
//  Copyright (c) 2012 azuremous.net All rights reserved.
//

#include "ofxSimpleButton.h"

ofxSimpleButton::ofxSimpleButton():
bImgButton(false),
appear(false),
useName(false),
selected(false),
buttonRender(true),
bePressed(false)
{
    
    
}

void ofxSimpleButton::setup(float x, float y, float w, float h, bool eventPress, bool setManualRender, BUTTON_TYPE _buttonType, BUTTON_SHAPE _buttonShape, const ofColor &_color)
{
    
    setButtonType(_buttonType);
    setButtonShape(_buttonShape);
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

void ofxSimpleButton::setup(float x, float y, string buttonImageName, bool eventPress, bool setManualRender, BUTTON_TYPE _buttonType)
{
    
    setButtonType(_buttonType);
    buttonImg.loadImage(buttonImageName);
    
    AreaRect.set(x, y, buttonImg.getWidth(), buttonImg.getHeight());
    bImgButton = true;
    
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

void ofxSimpleButton::setName(string _buttonName,float name_x, float name_y)
{
    
    buttonName = _buttonName;
    useName = true;
    namePos.set(name_x, name_y);
}

void ofxSimpleButton::render(){
    
    if (buttonRender) {
        
        ofPushMatrix();
        ofTranslate(AreaRect.x, AreaRect.y);
        
        if (useName) {
            
            ofSetColor(255);
            ofDrawBitmapString(buttonName, namePos);
            
        }
        
        if (bImgButton) {
            
            ofEnableAlphaBlending();
            ofSetColor(255);
            buttonImg.draw(0, 0);
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
                
                ofSetColor(255, 255, 0);
                if (buttonShape) { ofEllipse(AreaRect.width/2, AreaRect.height/2, AreaRect.width - (AreaRect.width / 10 * 2),AreaRect.height - (AreaRect.width / 10 * 2));}
                else{ ofRect(AreaRect.width / 10 , AreaRect.width / 10, AreaRect.width - (AreaRect.width / 10 * 2), AreaRect.height - (AreaRect.width / 10 * 2));}
                
            }
            
        }
        ofPopMatrix();
    }
    
}


void ofxSimpleButton::render(ofEventArgs &event)
{
    
    if (buttonRender) {
        
        ofPushMatrix();
        ofTranslate(AreaRect.x, AreaRect.y);
        
        if (useName) {
            
            ofSetColor(255);
            ofDrawBitmapString(buttonName, namePos);
            
        }
        
        if (bImgButton) {
            
            ofEnableAlphaBlending();
            ofSetColor(255);
            buttonImg.draw(0, 0);
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
                
                ofSetColor(255, 255, 0);
                if (buttonShape) { ofEllipse(AreaRect.width/2, AreaRect.height/2, AreaRect.width - (AreaRect.width / 10 * 2),AreaRect.height - (AreaRect.width / 10 * 2));}
                else{ ofRect(AreaRect.width / 10 , AreaRect.width / 10, AreaRect.width - (AreaRect.width / 10 * 2), AreaRect.height - (AreaRect.width / 10 * 2));}
                
            }
            
        }
        ofPopMatrix();
    }
}

void ofxSimpleButton::down(ofTouchEventArgs &touch)
{
    
    if (touch.id == 0) {
        
        if (pressed(touch.x, touch.y)){
            
            bePressed = true;
            
            switch (buttonType) {
                case 0:
                    selected = true;
                    break;
                case 1:
                    selected = !selected;
                    break;
                    
                default:
                    break;
            }
            
        }
    }
}

void ofxSimpleButton::press(ofMouseEventArgs &mouse){
    
    if (pressed(mouse.x, mouse.y)){
        bePressed = true;
        
        switch (buttonType) {
            case 0:
                selected = true;
                break;
            case 1:
                selected = !selected;
                break;
                
            default:
                break;
        }
        
    }
}

void ofxSimpleButton::up(ofTouchEventArgs &touch)
{
    
    if (!buttonType && selected) selected = false;
    bePressed = false;
    
}

void ofxSimpleButton::released(ofMouseEventArgs &mouse){
    
    if (!buttonType && selected) selected = false;
    bePressed = false;
}

bool ofxSimpleButton::pressed(float x, float y)
{
    
    if (!appear) return false;
    return x>= AreaRect.x && x <= AreaRect.x + AreaRect.width && y >= AreaRect.y && y <= AreaRect.y + AreaRect.height ;
    
}