//
//  ofxSimpleButton.h
//
//  Created by kim jung un a.k.a azuremous on 4/15/12.
//  Copyright (c) 2012~ azuremous.net All rights reserved.
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
    ofRectangle _areaRect;
    ofPoint _namePos;
    ofPoint _valuePos;
    ofColor _buttonColor;
    ofColor _pressedColor;
    
    ofImage _buttonImg[2];

    BUTTON_TYPE _buttonType;
    BUTTON_SHAPE _buttonShape;
    
    string _buttonName;
    string _buttonValue;
    
    bool _bImgButton;
    bool _useName;
    bool _useValue;
    bool _buttonRender;
    bool _appear;
    bool _selected;
    
protected:
    void buttonAction();
    bool pressed(float x, float y);
    bool _bePressed;
    
public:
    explicit ofxSimpleButton();
    virtual~ofxSimpleButton();
    
    void setup(float x, float y, float w, float h, bool eventPress, BUTTON_TYPE buttonType = BUTTON, BUTTON_SHAPE buttonShape = RECT_BUTTON, bool manualRender = false, const ofColor &color = ofColor::white);
    void setup(float x, float y, string buttonImageName, bool eventPress, BUTTON_TYPE buttonType = BUTTON, bool setManualRender = false);
    void setAppear(bool appear){ _appear = appear; }
    void setRender(bool render){ _buttonRender = render; }
    void setName(string buttonName, float name_x = 10, float name_y = 15);
    void setValue(string buttonValue, float value_x = 10, float value_y = - 10);
    void setButtonType(BUTTON_TYPE buttonType){ _buttonType = buttonType; }
    void setButtonShape(BUTTON_SHAPE buttonShape){ _buttonShape = buttonShape; }
    void setColor(const ofColor &color){ _buttonColor = color; }
    void setSelectedColor(const ofColor &color){ _pressedColor = color; }
    void setPos(float x, float y){ _areaRect.x = x; _areaRect.y = y; }
    void useMouseMoved();
    void useTouchMoved();
    void render(ofEventArgs &event);
    void render();
    void down(ofTouchEventArgs &touch);
    void up(ofTouchEventArgs &touch);
    void press(ofMouseEventArgs &mouse);
    void press(float x, float y);
    void released(ofMouseEventArgs &mouse);
    void movedTouch(ofTouchEventArgs &touch);
    void movedMouse(ofMouseEventArgs &mouse);
    void toggleOut(){ _selected = false; }
    
    bool getIsAppear() const { return _appear; }
    bool getIsRender() const { return _buttonRender; }
    bool bPressed() const { return _bePressed; }
    bool bSelected() const { return _selected; }
    
    float getX() const { return _areaRect.x; }
    float getY() const { return _areaRect.y; }
    float getWidht() const { return _areaRect.width; }
    float getHeight() const {return _areaRect.height; }
    
};

class ofxSimpleSlider {
private:
    ofRectangle _areaRect;
    ofPoint _namePos;
    ofPoint _valuePos;
    ofColor _sliderColor;
    bool _bHorizon;
    bool _valueChanged;
    bool _useName;
    bool _useValue;
    bool _appear;
    
    int _minValue;
    int _maxValue;
    int _value;
    
    string _sliderName;
    string _sliderValue;
    
protected:
    double line(double val, double inMin, double inMax, double outMin, double outMax);
    void moveButtonTouch(ofTouchEventArgs &touch);
    void moveButtonMouse(ofMouseEventArgs &mouse);
    void resetValueTouch(ofTouchEventArgs &touch);
    void resetValueMouse(ofMouseEventArgs &mouse);
    
public:
    ofxSimpleButton button;
    explicit ofxSimpleSlider();
    virtual~ofxSimpleSlider();
    
    void setup(float x, float y, float w, float h, bool bHorizontal = true ,bool setManualRender = false);
    void setAppear(bool appear){ _appear = appear; }
    void setColor(const ofColor &color){ _sliderColor = color; }
    void setMinValue(int value){ _minValue = value; }
    void setMaxValue(int value){ _maxValue = value; }
    void setName(string sliderName, float name_x = 10, float name_y = -8);
    void setValue(string sliderValue, float value_x = 10, float value_y = 15);
    void render(ofEventArgs &event);
    void render();
    int getValue() const { return _value; }
    int getMapValue(int min, int max);
    double getMapValue(double min, double max);
    bool bSelected() const { return _valueChanged; }
};


