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
    
    if (eventPress) ofAddListener(ofEvents.touchDown, this, &ofxSimpleButton::press);
    
    ofAddListener(ofEvents.touchUp, this, &ofxSimpleButton::up);
    
    if (!setManualRender) {
        ofAddListener(ofEvents.draw, this, &ofxSimpleButton::render);
    }
}

void ofxSimpleButton::setup(float x, float y, string buttonImageName, bool eventPress, bool setManualRender, BUTTON_TYPE _buttonType)
{
    
    setButtonType(_buttonType);
    buttonImg.loadImage(buttonImageName);
    
    AreaRect.set(x, y, buttonImg.getWidth(), buttonImg.getHeight());
    bImgButton = true;
    
    if (eventPress) ofAddListener(ofEvents.touchDown, this, &ofxSimpleButton::press);
    
    ofAddListener(ofEvents.touchUp, this, &ofxSimpleButton::up);
    
    if (!setManualRender) {
        ofAddListener(ofEvents.draw, this, &ofxSimpleButton::render);
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
                if (buttonShape) { ofEllipse(AreaRect.width/2, AreaRect.height/2, AreaRect.width - 10,AreaRect.height - 10);}
                else{ ofRect(5, 5, AreaRect.width - 10, AreaRect.height - 10);}
                
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
                if (buttonShape) { ofEllipse(AreaRect.width/2, AreaRect.height/2, AreaRect.width - 10,AreaRect.height - 10);}
                else{ ofRect(5, 5, AreaRect.width - 10, AreaRect.height - 10);}
                
            }
            
        }
        ofPopMatrix();
    }
}

void ofxSimpleButton::press(ofTouchEventArgs &touch)
{
    //cout<<"pressevent"<<endl;
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
    //cout<<"pressed:"<<selected<<endl;
}

void ofxSimpleButton::up(ofTouchEventArgs &touch)
{
    
    if (!buttonType && selected) selected = false;
    bePressed = false;
    
}

bool ofxSimpleButton::pressed(float x, float y)
{
    
    if (!appear) return false;
    return x>= AreaRect.x && x <= AreaRect.x + AreaRect.width && y >= AreaRect.y && y <= AreaRect.y + AreaRect.height ;
    
}