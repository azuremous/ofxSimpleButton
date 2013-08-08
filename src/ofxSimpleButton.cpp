//
//  ofxSimpleButton.cpp
//
//  Created by kim jung un a.k.a azuremous on 12/10/12.
//  Copyright (c) 2012~ azuremous.net All rights reserved.
//

#include "ofxSimpleButton.h"

//--------------------------------------------------------------
/*public */ofxSimpleButton::ofxSimpleButton()
:_bImgButton(false)
,_useName(false)
,_useValue(false)
,_buttonRender(true)
,_appear(true)
,_selected(false)
,_bePressed(false)
,_buttonColor(ofColor::white)
,_pressedColor(ofColor::yellow)
{}

//--------------------------------------------------------------
/*public */ofxSimpleButton::~ofxSimpleButton(){}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::setup(float x, float y, float w, float h, bool eventPress, BUTTON_TYPE buttonType, BUTTON_SHAPE buttonShape, bool manualRender,const ofColor &color)
{
    
    setButtonType(_buttonType);
    setButtonShape(_buttonShape);
    if (!_appear) { setAppear(true); }
    _buttonColor = color;
    _areaRect.set(x, y, w, h);
    
    if(ofGetTargetPlatform() == OF_TARGET_IPHONE){ //iOS
     
        if (eventPress) ofAddListener(ofEvents().touchDown, this, &ofxSimpleButton::down);
        ofAddListener(ofEvents().touchUp, this, &ofxSimpleButton::up);
        
    }else{ //MAC_OS
        
        if (eventPress) ofAddListener(ofEvents().mousePressed , this, &ofxSimpleButton::press);
        ofAddListener(ofEvents().mouseReleased, this, &ofxSimpleButton::released);
    }
    
    if (!manualRender) { ofAddListener(ofEvents().draw, this, &ofxSimpleButton::render); }
    
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::setup(float x, float y, string buttonImageName, bool eventPress, BUTTON_TYPE buttonType, bool manualRender)//set image button
{
    
    setButtonType(buttonType);
    
    char * dummyName = new char[50];
    sprintf(dummyName, ".png");
    string _buttonImgName = buttonImageName;
    _buttonImgName.append(dummyName);
    
    _buttonImg[0].loadImage(_buttonImgName);
    
    string _buttonImgName_p = buttonImageName.append(1,'_');
    _buttonImgName_p.append(dummyName);
    
    _buttonImg[1].loadImage(_buttonImgName_p);
    
    _buttonImgName_p.clear();
    _buttonImgName.clear();
    delete [] dummyName;
    
    
    if (!_appear) { setAppear(true); }
    _areaRect.set(x, y, _buttonImg[0].getWidth(), _buttonImg[0].getHeight());
    _bImgButton = true;
    
    if(ofGetTargetPlatform() == OF_TARGET_IPHONE){ //iOS
        if (eventPress) ofAddListener(ofEvents().touchDown, this, &ofxSimpleButton::down);
        ofAddListener(ofEvents().touchUp, this, &ofxSimpleButton::up);
        
    }else{ //MAC_OS
        if (eventPress) ofAddListener(ofEvents().mousePressed , this, &ofxSimpleButton::press);
        ofAddListener(ofEvents().mouseReleased, this, &ofxSimpleButton::released);
    }
    
    if (!manualRender) ofAddListener(ofEvents().draw, this, &ofxSimpleButton::render);
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::setName(string buttonName, float name_x, float name_y){
    
    _buttonName = buttonName;
    _useName = true;
    _namePos.set(name_x, name_y);
    if (!_appear) { setAppear(true); }
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::setValue(string buttonValue, float value_x, float value_y){
    _buttonValue = buttonValue;
    _useValue = true;
    _valuePos.set(value_x, value_y);
    if (!_appear) { setAppear(true); }
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
    
    if (_buttonRender) {
        
        ofPushMatrix();
        ofTranslate(_areaRect.x, _areaRect.y);
        
        if (_useName) {
            ofPushStyle();
            ofSetColor(_buttonColor);
            ofDrawBitmapString(_buttonName, _namePos);
            ofPopStyle();
        }
        
        if (_useValue) {
            ofPushStyle();
            ofSetColor(_buttonColor);
            ofDrawBitmapString(_buttonValue, _valuePos);
            ofPopStyle();
        }
        
        if (_bImgButton) {
            ofEnableAlphaBlending();
            ofSetColor(255);
            if (!_selected) { _buttonImg[0].draw(0, 0); }
            else { _buttonImg[1].draw(0, 0); }
            ofDisableAlphaBlending();
        
        }else {
            ofPushStyle();
            ofNoFill();
            ofSetLineWidth(2);
            ofSetColor(_buttonColor,255);
            if (_buttonShape) { ofEllipse(_areaRect.width/2, _areaRect.height/2, _areaRect.width,_areaRect.height); }
            else { ofRect(0, 0, _areaRect.width, _areaRect.height);}
            ofPopStyle();
            
            if (_selected){
                ofPushStyle();
                ofSetColor(_pressedColor);
                if (_buttonShape) { ofEllipse(_areaRect.width/2, _areaRect.height/2, _areaRect.width - (_areaRect.width / 10 * 2),_areaRect.height - (_areaRect.width / 10 * 2));}
                else{ ofRect(_areaRect.width / 10 , _areaRect.width / 10, _areaRect.width - (_areaRect.width / 10 * 2), _areaRect.height - (_areaRect.width / 10 * 2));}
                ofPopStyle();
            }
        }
        ofPopMatrix();
    }
    
}


//--------------------------------------------------------------
/*public */void ofxSimpleButton::render(ofEventArgs &event)
{
    
    if (_buttonRender) {
        
        ofPushMatrix();
        ofTranslate(_areaRect.x, _areaRect.y);
        
        if (_useName) {
            ofPushStyle();
            ofSetColor(_buttonColor);
            ofDrawBitmapString(_buttonName, _namePos);
            ofPopStyle();
        }
        
        if (_useValue) {
            ofPushStyle();
            ofSetColor(_buttonColor);
            ofDrawBitmapString(_buttonValue, _valuePos);
            ofPopStyle();
        }
        
        if (_bImgButton) {
            ofEnableAlphaBlending();
            ofSetColor(255);
            if (!_selected) { _buttonImg[0].draw(0, 0); }
            else { _buttonImg[1].draw(0, 0); }
            ofDisableAlphaBlending();
        }else {
            ofPushStyle();
            ofNoFill();
            ofSetLineWidth(2);
            ofSetColor(_buttonColor,255);
            if (_buttonShape) { ofEllipse(_areaRect.width/2, _areaRect.height/2, _areaRect.width, _areaRect.height); }
            else { ofRect(0, 0, _areaRect.width, _areaRect.height);}
            ofPopStyle();
            
            if (_selected){
                ofPushStyle();
                ofSetColor(255, 255, 0);
                if (_buttonShape) { ofEllipse(_areaRect.width/2, _areaRect.height/2, _areaRect.width - (_areaRect.width / 10 * 2), _areaRect.height - (_areaRect.width / 10 * 2));}
                else{ ofRect(_areaRect.width / 10 , _areaRect.width / 10, _areaRect.width - (_areaRect.width / 10 * 2), _areaRect.height - (_areaRect.width / 10 * 2));}
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
/*public */void ofxSimpleButton::press(float x, float y) { if (pressed(x, y)) buttonAction(); }

//--------------------------------------------------------------
/*public */void ofxSimpleButton::up(ofTouchEventArgs &touch)
{
    if (!_buttonType && _selected) _selected = _bePressed = false;
    else _bePressed = false;
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::released(ofMouseEventArgs &mouse)
{
    if (!_buttonType && _selected) _selected = _bePressed = false;
    else _bePressed = false;
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::movedTouch(ofTouchEventArgs &touch){
    if (pressed(touch.x, touch.y)) buttonAction(); 
    else _selected = false;
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::movedMouse(ofMouseEventArgs &mouse){
    if (pressed(mouse.x, mouse.y)) buttonAction();
    else _selected = false;
}

//--------------------------------------------------------------
/*protected */void ofxSimpleButton::buttonAction(){
    
    switch (_buttonType) {
        case 0:
            _selected = true;
            break;
        case 1:
            _selected = !_selected;
            break;
    }
}

//--------------------------------------------------------------
/*protected */bool ofxSimpleButton::pressed(float x, float y)
{
    if (!_appear) return false;
    return _bePressed = x>= _areaRect.x && x <= _areaRect.x + _areaRect.width && y >= _areaRect.y && y <= _areaRect.y + _areaRect.height ;
}

//--------------------------------------------------------------
/*public */ofxSimpleSlider::ofxSimpleSlider()
:_valueChanged(false)
,_sliderColor(ofColor::yellowGreen)

{}

//--------------------------------------------------------------
/*public */ofxSimpleSlider::~ofxSimpleSlider(){}

//--------------------------------------------------------------
/*public */void ofxSimpleSlider::setup(float x, float y, float w, float h, bool bHorizontal, bool setManualRender){
    
    if (bHorizontal) {
        button.setup(x, y, h, h, true, BUTTON, RECT_BUTTON, true);//set manual render;
    }else{
        button.setup(x, y, w, w, true, BUTTON, RECT_BUTTON, true);//set manual render;
    }
    _bHorizon = bHorizontal;
    _areaRect.set(x, y, w, h);
    
    setMinValue(0);
    setMaxValue(127);
    
    if(ofGetTargetPlatform() == OF_TARGET_IPHONE){ //iOS
        ofAddListener(ofEvents().touchDown, this, &ofxSimpleSlider::moveButtonTouch);
        ofAddListener(ofEvents().touchMoved, this, &ofxSimpleSlider::moveButtonTouch);
        ofAddListener(ofEvents().touchUp, this, &ofxSimpleSlider::resetValueTouch);
    }else{ //MAC_OS
        ofAddListener(ofEvents().mousePressed, this, &ofxSimpleSlider::moveButtonMouse);
        ofAddListener(ofEvents().mouseDragged, this, &ofxSimpleSlider::moveButtonMouse);
        ofAddListener(ofEvents().mouseReleased, this, &ofxSimpleSlider::resetValueMouse);
    }
    if (!setManualRender) { ofAddListener(ofEvents().draw, this, &ofxSimpleSlider::render); }
}

//--------------------------------------------------------------
/*public */void ofxSimpleSlider::setName(string sliderName, float name_x, float name_y){
    
    _sliderName = sliderName;
    _useName = true;
    _namePos.set(name_x, name_y);
    if (!_appear) { setAppear(true); }
}

//--------------------------------------------------------------
/*public */void ofxSimpleSlider::setValue(string sliderValue, float value_x, float value_y){
    sliderValue = _sliderValue;
    _useValue = true;
    _valuePos.set(value_x, value_y);
    if (!_appear) { setAppear(true); }
}

//--------------------------------------------------------------
/*public */void ofxSimpleSlider::render(ofEventArgs &event){
    if (_appear) {
        ofPushMatrix();
        ofTranslate(_areaRect.x, _areaRect.y);
        if (_useName) {
            ofPushStyle();
            ofSetColor(_sliderColor);
            ofDrawBitmapString(_sliderName, _namePos);
            ofPopStyle();
        }
        
        if (_useValue) {
            ofPushStyle();
            ofSetColor(_sliderColor);
            ofDrawBitmapString(_sliderValue, _valuePos);
            ofPopStyle();
        }
        
        ofPushStyle();
        ofNoFill();
        ofSetLineWidth(2);
        ofSetColor(_sliderColor);
        ofRect(0, 0, _areaRect.width, _areaRect.height);
        ofPopStyle();
        ofPopMatrix();
        
        button.render();
    }
}

//--------------------------------------------------------------
/*public */void ofxSimpleSlider::render(){
    if (_appear) {
        ofPushMatrix();
        ofTranslate(_areaRect.x, _areaRect.y);
        if (_useName) {
            ofPushStyle();
            ofSetColor(_sliderColor);
            ofDrawBitmapString(_sliderName, _namePos);
            ofPopStyle();
        }
        
        if (_useValue) {
            ofPushStyle();
            ofSetColor(_sliderColor);
            ofDrawBitmapString(_sliderValue, _valuePos);
            ofPopStyle();
        }
        
        ofPushStyle();
        ofNoFill();
        ofSetLineWidth(2);
        ofSetColor(_sliderColor);
        ofRect(0, 0, _areaRect.width, _areaRect.height);
        ofPopStyle();
        ofPopMatrix();
        
        button.render();
    }
}

//--------------------------------------------------------------
/*public */int ofxSimpleSlider::getMapValue(int min, int max){
    int value = 0;
    if (bSelected()) {
        value = (int)line(getValue(), _minValue, _maxValue, min, max);
        char * _valueString = new char[255];
        sprintf(_valueString, "%d", value);
        setValue(_valueString);
        delete [] _valueString;
    }
    return value;
}

//--------------------------------------------------------------
/*public */double ofxSimpleSlider::getMapValue(double min, double max){
    double value = 0.0;
    if (bSelected()) {
        value = line(getValue(), _minValue, _maxValue, min, max);
        char * _valueString = new char[255];
        sprintf(_valueString, "%f", value);
        setValue(_valueString);
        delete [] _valueString;
    }
    return value;
}

//--------------------------------------------------------------
/*protected */double ofxSimpleSlider::line(double val, double inMin, double inMax, double outMin, double outMax){
    return ((val - inMin) / (inMax - inMin) * (outMax - outMin)) + outMin;
}


//--------------------------------------------------------------
/*protected */void ofxSimpleSlider::moveButtonTouch(ofTouchEventArgs &touch){
    int _gap = 3;
    if (_appear) {
        if (_bHorizon) {
            if (touch.y > _areaRect.y - _gap && touch.y < _areaRect.y + _areaRect.height + _gap) {
                if (touch.x > _areaRect.x - _gap && touch.x < _areaRect.x + _areaRect.width + _gap) {
                    float barwidth = touch.x;
                    if (barwidth <= _areaRect.x) { barwidth = _areaRect.x; }
                    else if (barwidth >= _areaRect.x + _areaRect.width - _areaRect.height){
                        barwidth = _areaRect.x + _areaRect.width - _areaRect.height;
                    }
                    _value = (int)line(barwidth, _areaRect.x, _areaRect.x + _areaRect.width - _areaRect.height, _minValue, _maxValue);
                    button.setPos(barwidth, _areaRect.y);
                    _valueChanged = true;
                }
            }
        }
    }
}

//--------------------------------------------------------------
/*protected */void ofxSimpleSlider::resetValueTouch(ofTouchEventArgs &touch){ _valueChanged = false; }

//--------------------------------------------------------------
/*protected */void ofxSimpleSlider::moveButtonMouse(ofMouseEventArgs &mouse){
    int _gap = 3;
    if (_appear) {
        if (_bHorizon) {
            if (mouse.y > _areaRect.y - _gap && mouse.y < _areaRect.y + _areaRect.height + _gap) {
                if (mouse.x > _areaRect.x - _gap && mouse.x < _areaRect.x + _areaRect.width + _gap) {
                    float barwidth = mouse.x;
                    if (barwidth <= _areaRect.x) { barwidth = _areaRect.x; }
                    else if (barwidth >= _areaRect.x + _areaRect.width - _areaRect.height){
                        barwidth = _areaRect.x + _areaRect.width - _areaRect.height;
                    }
                    _value = (int)line(barwidth, _areaRect.x, _areaRect.x + _areaRect.width - _areaRect.height, _minValue, _maxValue);
                    button.setPos(barwidth, _areaRect.y);
                    _valueChanged = true;
                }
            }
        }
    }
}

//--------------------------------------------------------------
/*protected */void ofxSimpleSlider::resetValueMouse(ofMouseEventArgs &mouse){ _valueChanged = false; }
