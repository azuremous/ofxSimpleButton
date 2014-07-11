//
//  ofxSimpleButton.cpp
//
//  Created by kim jung un a.k.a azuremous on 12/10/12.
//  Copyright (c) 2012~ azuremous.net All rights reserved.
//

#include "ofxSimpleButton.h"

//--------------------------------------------------------------
/*public */ofxSimpleButton::ofxSimpleButton()
:useName(false)
,useValue(false)
,bRender(false)
,bAppear(false)
,fixPos(true)
,bSelect(false)
,bToggle(false)
,bDoubleTab(false)
,b_c(ofColor::white)
,b_b_c(ofColor::gray)
,b_t_c(ofColor::yellow)
{}

//--------------------------------------------------------------
/*public */ofxSimpleButton::~ofxSimpleButton(){}

//--------------------------------------------------------------
/*public */bool ofxSimpleButton::setup(float x, float y, float w, float h){
    
    setType(TYPE_BUTTON); //default type is button
    setShape(BUTTON_RECT); //defalut shape is rectangle
    
    b_rect.set(x, y, w, h); //set rectangle position and size
    
    if (w > 0 && h > 0 && !bAppear) {
        setAppear(true);
        setRender(true);
        if (ofGetTargetPlatform() == OF_TARGET_IOS) {
            ofAddListener(ofEvents().touchDown, this, &ofxSimpleButton::touchDown);
            ofAddListener(ofEvents().touchUp, this, &ofxSimpleButton::touchUp);
            ofAddListener(ofEvents().touchMoved, this, &ofxSimpleButton::touchMoved);
            ofAddListener(ofEvents().touchDoubleTap, this, &ofxSimpleButton::touchDoubleTap);
        }else{
            ofAddListener(ofEvents().mousePressed , this, &ofxSimpleButton::mousePressed);
            ofAddListener(ofEvents().mouseReleased, this, &ofxSimpleButton::mouseReleased);
            ofAddListener(ofEvents().mouseMoved, this, &ofxSimpleButton::mouseMoved);
            ofAddListener(ofEvents().mouseDragged, this, &ofxSimpleButton::mouseDragged);
        }
        ofAddListener(ofEvents().draw, this, &ofxSimpleButton::render);
        return bAppear;
    }
    ofLog(OF_LOG_ERROR, "Button's size is not correct. Button couldn't setup.");
    return bAppear;
}

//--------------------------------------------------------------
/*public */bool ofxSimpleButton::setup(float x, float y, float w, float h, bool useEvent, bool manualRender, TYPE_BUTTONS type, BUTTON_SHAPES shape, const ofColor &c)
{
    setType(type);
    setShape(shape);
    
    b_rect.set(x, y, w, h);
    
    if (w > 0 && h > 0 && !bAppear) {
        setAppear(true);
        b_c = c;
        if (ofGetTargetPlatform() == OF_TARGET_IOS) {
            if (useEvent) { ofAddListener(ofEvents().touchDown, this, &ofxSimpleButton::touchDown); }
            ofAddListener(ofEvents().touchMoved, this, &ofxSimpleButton::touchMoved);
            ofAddListener(ofEvents().touchDoubleTap, this, &ofxSimpleButton::touchDoubleTap);
            ofAddListener(ofEvents().touchUp, this, &ofxSimpleButton::touchUp);
        }else{
            if (useEvent) { ofAddListener(ofEvents().mousePressed , this, &ofxSimpleButton::mousePressed); }
            ofAddListener(ofEvents().mouseReleased, this, &ofxSimpleButton::mouseReleased);
            ofAddListener(ofEvents().mouseMoved, this, &ofxSimpleButton::mouseMoved);
            ofAddListener(ofEvents().mouseDragged, this, &ofxSimpleButton::mouseDragged);
        }
        
        if (!manualRender) {
            setRender(true);
            ofAddListener(ofEvents().draw, this, &ofxSimpleButton::render);
        }
        
        return bAppear;
    }
    
    ofLog(OF_LOG_ERROR, "Button's size is not correct. Button couldn't setup.");
    return bAppear;
}

//--------------------------------------------------------------
/*public */bool ofxSimpleButton::setup(float x, float y, string imgRoute, bool useEvent, bool manualRender, TYPE_BUTTONS type)
{
    setType(type);
    setShape(BUTTON_IMAGE);
    
    //load image and add to vector
    char * extention = new char[255];
    sprintf(extention, ".png");
    string _imgRoute = imgRoute;
    _imgRoute.append(extention);
    
    ofImage b;
    if(b.loadImage(_imgRoute)) { b_img.push_back(b); }
    else {
        ofLog(OF_LOG_ERROR, "couldn't load image");
        return false;
    }
    
    string _togglImgRoute = imgRoute.append(1,'_');
    _togglImgRoute.append(extention);
    
    if(b.loadImage(_imgRoute)){ b_img.push_back(b); }
    
    _togglImgRoute.clear();
    _imgRoute.clear();
    delete [] extention;
    
    if (b_img.size() > 0 && !bAppear) {
        setAppear(true);
        
        float w = b_img[0].getWidth();
        float h = b_img[0].getHeight();
        b_rect.set(x, y, w, h);
        
        if (ofGetTargetPlatform() == OF_TARGET_IOS) {
            if (useEvent) { ofAddListener(ofEvents().touchDown, this, &ofxSimpleButton::touchDown); }
            ofAddListener(ofEvents().touchMoved, this, &ofxSimpleButton::touchMoved);
            ofAddListener(ofEvents().touchDoubleTap, this, &ofxSimpleButton::touchDoubleTap);
            ofAddListener(ofEvents().touchUp, this, &ofxSimpleButton::touchUp);
        }else{
            if (useEvent) { ofAddListener(ofEvents().mousePressed , this, &ofxSimpleButton::mousePressed); }
            ofAddListener(ofEvents().mouseReleased, this, &ofxSimpleButton::mouseReleased);
            ofAddListener(ofEvents().mouseMoved, this, &ofxSimpleButton::mouseMoved);
            ofAddListener(ofEvents().mouseDragged, this, &ofxSimpleButton::mouseDragged);
        }
        
        if (!manualRender) {
            setRender(true);
            ofAddListener(ofEvents().draw, this, &ofxSimpleButton::render);
        }
        
        return bAppear;
    }
    
    ofLog(OF_LOG_ERROR, "Button couldn't setup.");
    return bAppear;
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::setAppear(bool show)
{
    bAppear = show;
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::setRender(bool magic)
{
    bRender = magic;
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::setType(TYPE_BUTTONS type)
{
    b_type = type;
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::setShape(BUTTON_SHAPES shape)
{
    b_shape = shape;
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::setColor(const ofColor &c)
{
    b_c = c;
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::setToggleColor(const ofColor &c)
{
    b_t_c = c;
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::setBackColor(const ofColor &c)
{
    b_b_c = c;
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::setPos(const ofPoint &p)
{
    setPos(p.x, p.y);
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::setPos(float x, float y){
    b_rect.x = x;
    b_rect.y = y;
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::setName(string n, float n_x, float n_y){
    if (!bAppear) {
        ofLog(OF_LOG_ERROR, "Button is not initialized. First you need to setup.");
        return;
    }
    b_info_text = n;
    useName = true;
    n_pos.set(n_x, n_y);
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::setValue(string v, float v_x, float v_y){
    if (!bAppear) {
        ofLog(OF_LOG_ERROR, "Button is not initialized. First you need to setup.");
        return;
    }
    b_val_text = v;
    useValue = true;
    v_pos.set(v_x, v_y);
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::setFixPos(bool fix)
{
    fixPos = fix;
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::resetToggle()
{
    bToggle = false;
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::render(){
    
    if (bRender) {
        
        ofPushMatrix();
        ofTranslate(b_rect.x, b_rect.y);
        
        if (b_img.size() > 0 && b_shape == BUTTON_IMAGE) {
            ofEnableAlphaBlending();
            ofSetColor(255, 255);
            if (b_img.size() == 2) {
                if (!bToggle) { b_img[0].draw(0, 0); }
                else { b_img[1].draw(0, 0); }
            }else{
                b_img[0].draw(0, 0);
            }
            ofDisableAlphaBlending();
        }else {
            ofPushStyle();
            ofSetColor(b_b_c, 255);
            if (b_shape == BUTTON_CIRCLE) {
                ofEllipse(b_rect.width/2, b_rect.height/2, b_rect.width, b_rect.height);
            }else if (b_shape == BUTTON_RECT){
                ofRect(0, 0, b_rect.width, b_rect.height);
            }else if (b_shape == BUTTON_CUSTOM){
                //using vertex?
            }
            updateButtonColor();
            if (b_shape == BUTTON_CIRCLE) {
                ofEllipse(b_rect.width/2, b_rect.height/2, b_rect.width, b_rect.height);
            }else if (b_shape == BUTTON_RECT){
                ofRect(0, 0, b_rect.width, b_rect.height);
            }else if (b_shape == BUTTON_CUSTOM){
                //using vertex?
            }
            ofPopStyle();
        }
        
        if (useName) {
            ofPushStyle();
            ofSetColor(b_c);
            ofDrawBitmapString(b_info_text, n_pos);
            ofPopStyle();
        }
        
        if (useValue) {
            ofPushStyle();
            ofSetColor(b_c);
            ofDrawBitmapString(b_val_text, v_pos);
            ofPopStyle();
        }
        ofPopMatrix();
    }
    
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::mousePressed(float x, float y)
{
    if (isInside(x, y)) {
        buttonAction(true);
    }
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::toggleShow(){
    bAppear = !bAppear;
    bRender = !bRender;
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::hide()
{
    bAppear = bRender = false;
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::show()
{
    bAppear = bRender = true;
}

//--------------------------------------------------------------
/*protected */void ofxSimpleButton::render(ofEventArgs &event)
{
    render();
}

//--------------------------------------------------------------
/*protected */void ofxSimpleButton::touchDown(ofTouchEventArgs &touch)
{
    if (touch.id == 0 && isInside(touch.x, touch.y)) {
        buttonAction(true);
    }
    
}

//--------------------------------------------------------------
/*protected */void ofxSimpleButton::touchUp(ofTouchEventArgs &touch)
{
    if (b_type == TYPE_BUTTON) {
        bSelect = bToggle = false;
    }else if (b_type == TYPE_TOGGLE) {
        bSelect = false;
    }
}

//--------------------------------------------------------------
/*protected */void ofxSimpleButton::touchMoved(ofTouchEventArgs &touch){
    if (!fixPos && bSelect) {
        setPos(touch.x, touch.y);
    }
}

//--------------------------------------------------------------
/*protected */void ofxSimpleButton::touchDoubleTap(ofTouchEventArgs &touch){
    if (isInside(touch.x, touch.y)) { bDoubleTab = !bDoubleTab; }
}

//--------------------------------------------------------------
/*protected */void ofxSimpleButton::mousePressed(ofMouseEventArgs &mouse)
{
    mousePressed(mouse.x, mouse.y);
}

//--------------------------------------------------------------
/*protected */void ofxSimpleButton::mouseReleased(ofMouseEventArgs &mouse)
{
    if (b_type == TYPE_BUTTON) { bSelect = bToggle = false; }
    else if (b_type == TYPE_TOGGLE) { bSelect = false; }
}

//--------------------------------------------------------------
/*protected */void ofxSimpleButton::mouseMoved(ofMouseEventArgs &mouse){
    if (!fixPos && bSelect) {
        setPos(mouse.x, mouse.y);
    }
}

//--------------------------------------------------------------
/*protected */void ofxSimpleButton::mouseDragged(ofMouseEventArgs &mouse){
    if (!fixPos && bSelect) {
        setPos(mouse.x, mouse.y);
    }
}

//--------------------------------------------------------------
/*protected */void ofxSimpleButton::updateButtonColor(){
    if (bToggle) {
        ofFill();
        ofSetLineWidth(1);
        ofSetColor(b_t_c, 255);
    }else {
        ofNoFill();
        ofSetLineWidth(2);
        ofSetColor(b_c, 255);
    }
}

//--------------------------------------------------------------
/*protected */void ofxSimpleButton::buttonAction(bool b){
    
    if (b_type == TYPE_BUTTON) {
        bToggle = true;
    }else if (b_type == TYPE_TOGGLE) {
        bToggle = !bToggle;
    }
}

//--------------------------------------------------------------
/*protected */bool ofxSimpleButton::isInside(float x, float y)
{
    if (!bAppear) return false;
    return  bSelect = x>= b_rect.x && x <= b_rect.x + b_rect.width && y >= b_rect.y && y <= b_rect.y + b_rect.height ;
}