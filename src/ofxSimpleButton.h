//
//  ofxSimpleButton.h
//
//  Created by kim jung un a.k.a azuremous on 4/15/12.
//  Copyright (c) 2012 azuremous.net All rights reserved.
//

#pragma once

#include "ofMain.h"

typedef enum {
    BUTTON,
    TOGGLE,
    
}BUTTON_TYPE;

typedef enum { 
    RECT_BUTTON,
    CIRCLE_BUTTON,
    
}BUTTON_SHAPE;

class ofxSimpleButton {
    
private:
    ofRectangle AreaRect;
    ofPoint namePos;
    ofColor buttonColor;
    ofColor pressedColor;
    
    ofImage buttonImg[2];

    BUTTON_TYPE buttonType;
    BUTTON_SHAPE buttonShape;
    
    string buttonName;
    
    bool bImgButton;
    bool useName;
    bool buttonRender;
    bool appear;
    bool selected;
    
protected:
    
    void buttonAction();
    bool pressed(float x, float y);
    
public:
    bool bePressed;
    
    explicit ofxSimpleButton();
    virtual~ofxSimpleButton();
    
    void setup(float x, float y, float w, float h, bool eventPress, BUTTON_TYPE _buttonType = BUTTON, BUTTON_SHAPE _buttonShape = RECT_BUTTON, bool setManualRender = false, const ofColor &_color = 255);
    void setup(float x, float y, string buttonImageName, bool eventPress, BUTTON_TYPE _buttonType = BUTTON, bool setManualRender = false);
    void setAppear(bool _appear){ appear = _appear; }
    void setRender(bool _render){ buttonRender = _render; }
    void setName(string _buttonName, float name_x = 10, float name_y = 15);
    void setButtonType(BUTTON_TYPE _buttonType){ buttonType = _buttonType; }
    void setButtonShape(BUTTON_SHAPE _buttonShape){ buttonShape = _buttonShape; }
    void setColor(const ofColor &_color){ buttonColor = _color; }
    void setSelectedColor(const ofColor &_color){ pressedColor = _color; }
    void setPos(float _x, float _y){ AreaRect.x = _x; AreaRect.y = _y; }
    //event
    void useMouseMoved();
    void render(ofEventArgs &event);
    void render();
    void down(ofTouchEventArgs &touch);
    void up(ofTouchEventArgs &touch);
    void press(ofMouseEventArgs &mouse);
    void press(float x, float y);
    void released(ofMouseEventArgs &mouse);
    void moved(ofMouseEventArgs &mouse);
    
    bool getIsAppear() const { return appear; }
    bool getIsRender() const { return buttonRender; }
    bool bSelected() const { return selected; }
    
};

class ofxSimpleSlider {
private:
    ofRectangle AreaRect;
    ofColor SliderColor;
    int value;
    int MaxVlaue;
    bool bHorz;
    bool valueChanged;
    
protected:
    void moveButtonTouch(ofTouchEventArgs &touch);
    void moveButtonMouse(ofMouseEventArgs &mouse);
    void resetValueTouch(ofTouchEventArgs &touch);
    void resetValueMouse(ofMouseEventArgs &mouse);
    
public:
    ofxSimpleButton button;
    explicit ofxSimpleSlider();
    virtual~ofxSimpleSlider();
    
    void setup(float x, float y, float w, float h, bool bHorizontal);
    void setMaxValue(int _value){ MaxVlaue = _value; }
    void render();
    int getValue() const { return value; }
    bool bSelected() const { return valueChanged; }
};


