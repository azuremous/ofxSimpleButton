//
//  buttonObject.h
//  scratchPainter
//
//  Created by 정운 김 on 4/15/12.
//  Copyright (c) 2012 pinkroad.co.cc. All rights reserved.
//

#ifndef scratchPainter_buttonObject_h
#define scratchPainter_buttonObject_h

#include "ofMain.h"

typedef enum {
    
    BUTTON,
    TOGGLE
    
}BUTTON_TYPE;

class ofxSimpleButton {
    
public:
    
    ofRectangle AreaRect;
    ofPoint namePos;
    
    ofImage buttonImg;
    ofColor buttonColor;
    BUTTON_TYPE type;
    
    string b_name;
    
    bool bImgButton;
    bool appear;
    bool useName;
    bool selected;
    
    ofxSimpleButton():
    bImgButton(false),
    appear(false),
    useName(false),
    selected(false)
    {
        
    }
    
    void setup(float x, float y, float w, float h,BUTTON_TYPE _type = BUTTON ,const ofColor &_color = 255){
        type = _type;
        buttonColor = _color;
        AreaRect.set(x, y, w, h);
        ofAddListener(ofEvents.touchDown, this, &ofxSimpleButton::press);
        ofAddListener(ofEvents.touchUp, this, &ofxSimpleButton::up);
        ofAddListener(ofEvents.draw, this, &ofxSimpleButton::render);
        
    }
    
    void setup(float x, float y, string _name , BUTTON_TYPE _type = BUTTON){
        
        type = _type;
        buttonImg.loadImage(_name);
        
        AreaRect.set(x, y, buttonImg.getWidth(), buttonImg.getHeight());
        bImgButton = true;
        
        ofAddListener(ofEvents.touchDown, this, &ofxSimpleButton::press);
        ofAddListener(ofEvents.touchUp, this, &ofxSimpleButton::up);
        ofAddListener(ofEvents.draw, this, &ofxSimpleButton::render);
    }
    
    void setAppear(bool _appear){
        
        appear = _appear;
    }
    
    void setName(string _name,float name_x = 10, float name_y = 15){
        
        b_name = _name;
        useName = true;
        namePos.set(name_x, name_y);
    }
    
    void render(ofEventArgs &event){
        
        if (appear) {
            ofPushMatrix();
            ofTranslate(AreaRect.x, AreaRect.y);
            
            if (useName) {
                ofSetColor(255,255,255);
                ofDrawBitmapString(b_name, namePos);
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
                ofRect(0, 0, AreaRect.width, AreaRect.height);
                ofPopStyle();
                if (selected){
                    
                    ofSetColor(255, 255, 0);
                    ofRect(5, 5, AreaRect.width - 10, AreaRect.height - 10);
                }
            }
            ofPopMatrix();
        }
    }
    
    void press(ofTouchEventArgs &touch){
        
        if (touch.id == 0) {
            if (pressed(touch.x, touch.y)){
                
                switch (type) {
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
    
    void up(ofTouchEventArgs &touch){
        
        if (!type && selected) selected = false;
        
    }
    
    bool pressed(float x, float y){
        
        if (!appear) return false;
        
        return x>= AreaRect.x && x <= AreaRect.x + AreaRect.width && y >= AreaRect.y && y <= AreaRect.y + AreaRect.height ;
        
    }
    
};


#endif
