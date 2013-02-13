//
//  ofxSimpleButton.h
//  ofxSimpleButton
//
//  Created by kim jung un a.k.a azuremous on 4/15/12.
//  Copyright (c) 2012 azuremous.net All rights reserved.
//

#pragma once

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
    
private:
    
    bool buttonRender;
    bool appear;
    bool selected;
    
public:
    
    ofRectangle AreaRect;
    ofPoint namePos;
    
    ofImage buttonImg[2];
    ofColor buttonColor;
    
    BUTTON_TYPE buttonType;
    BUTTON_SHAPE buttonShape;
    
    string buttonName;
    
    bool bImgButton;
    bool useName;
    bool bePressed;
    
    ofxSimpleButton();
    
    void setup(float x, float y, float w, float h, bool eventPress, BUTTON_TYPE _buttonType = BUTTON, BUTTON_SHAPE _buttonShape = RECT_BUTTON,bool setManualRender = false, const ofColor &_color = 255);
    
    void setup(float x, float y, string buttonImageName, bool eventPress, BUTTON_TYPE _buttonType = BUTTON, bool setManualRender = false);
    
    void setAppear(bool _appear){ appear = _appear; }
    void setRender(bool _render){ buttonRender = _render; }
    void setName(string _buttonName,float name_x = 10, float name_y = 15);
    
    void setButtonType(BUTTON_TYPE _buttonType){ buttonType = _buttonType; }
    
    void setButtonShape(BUTTON_SHAPE _buttonShape){ buttonShape = _buttonShape; }
    
    void setColor(const ofColor &_color){ buttonColor = _color;}
    
    void render(ofEventArgs &event);
    void render();
    void down(ofTouchEventArgs &touch);
    void press(ofMouseEventArgs &mouse);
    void up(ofTouchEventArgs &touch);
    void released(ofMouseEventArgs &mouse);
    void buttonAction();
    bool pressed(float x, float y);
    bool getIsAppear() const;
    bool getIsRender() const;
    bool beSelected() const;
    
};


