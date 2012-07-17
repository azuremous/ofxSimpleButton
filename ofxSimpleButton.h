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

typedef enum { 
    RECT_BUTTON,
    CIRCLE_BUTTON,
    
}BUTTON_SHAPE;



class ofxSimpleButton {
    
public:
    
    ofRectangle AreaRect;
    ofPoint namePos;
    
    ofImage buttonImg;
    ofColor buttonColor;
    
    BUTTON_TYPE buttonType;
    BUTTON_SHAPE buttonShape;
    
    string buttonName;
    
    bool bImgButton;
    bool appear;
    bool useName;
    bool selected;
    bool bePressed;
    
    ofxSimpleButton():
    bImgButton(false),
    appear(false),
    useName(false),
    selected(false),
    bePressed(false)
    {
        
    }
    
    void setup(float x, float y, float w, float h, bool eventPress, BUTTON_TYPE _buttonType = BUTTON, BUTTON_SHAPE _buttonShape = RECT_BUTTON, const ofColor &_color = 255)
    {
        
        setButtonType(_buttonType);
        setButtonShape(_buttonShape);
        buttonColor = _color;
        AreaRect.set(x, y, w, h);
        
        if (eventPress) ofAddListener(ofEvents.touchDown, this, &ofxSimpleButton::press);
        
        ofAddListener(ofEvents.touchUp, this, &ofxSimpleButton::up);
        ofAddListener(ofEvents.draw, this, &ofxSimpleButton::render);
        
    }
    
    void setup(float x, float y, string buttonImageName, bool eventPress, BUTTON_TYPE _buttonType = BUTTON)
    {
        
        setButtonType(_buttonType);
        buttonImg.loadImage(buttonImageName);
        
        AreaRect.set(x, y, buttonImg.getWidth(), buttonImg.getHeight());
        bImgButton = true;
        
        if (eventPress) ofAddListener(ofEvents.touchDown, this, &ofxSimpleButton::press);
        
        ofAddListener(ofEvents.touchUp, this, &ofxSimpleButton::up);
        ofAddListener(ofEvents.draw, this, &ofxSimpleButton::render);
    }
    
    void setAppear(bool _appear){ appear = _appear; }
    
    void setName(string _buttonName,float name_x = 10, float name_y = 15)
    {
        
        buttonName = _buttonName;
        useName = true;
        namePos.set(name_x, name_y);
    }
    
    void setButtonType(BUTTON_TYPE _buttonType){ buttonType = _buttonType; }
    void setButtonShape(BUTTON_SHAPE _buttonShape){ buttonShape = _buttonShape; }
    
    void render(ofEventArgs &event)
    {
        
        if (appear) {
            
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
    
    void press(ofTouchEventArgs &touch)
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
    
    void up(ofTouchEventArgs &touch)
    {
        
        if (!buttonType && selected) selected = false;
        bePressed = false;
        
    }
    
    bool pressed(float x, float y)
    {
        
        if (!appear) return false;
        return x>= AreaRect.x && x <= AreaRect.x + AreaRect.width && y >= AreaRect.y && y <= AreaRect.y + AreaRect.height ;
        
    }
    
};


#endif
