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
,bAnimation(false)
,bang(false)
,startAni(false)
,aniTime(0)
,changeTime(500)
,b_c(ofColor::white)
,b_t_c(ofColor::yellow)
{}

//--------------------------------------------------------------
/*public */ofxSimpleButton::~ofxSimpleButton(){}

//--------------------------------------------------------------
/*public */bool ofxSimpleButton::setup(float x, float y, float w, float h, bool useEvent){
    
    setType(TYPE_BUTTON); //default type is button
    setShape(BUTTON_RECT); //defalut shape is rectangle
    
    b_rect.set(x, y, w, h); //set rectangle position and size
    
    if (w > 0 && h > 0 && !bAppear) {
        setAppear(true);
        setRender(true);
        if (useEvent) {
            if (ofGetTargetPlatform() == OF_TARGET_IOS || ofGetTargetPlatform() == OF_TARGET_ANDROID) {
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
        }
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
        if (useEvent) {
            if (ofGetTargetPlatform() == OF_TARGET_IOS || ofGetTargetPlatform() == OF_TARGET_ANDROID) {
                ofAddListener(ofEvents().touchDown, this, &ofxSimpleButton::touchDown);
                ofAddListener(ofEvents().touchMoved, this, &ofxSimpleButton::touchMoved);
                ofAddListener(ofEvents().touchDoubleTap, this, &ofxSimpleButton::touchDoubleTap);
                ofAddListener(ofEvents().touchUp, this, &ofxSimpleButton::touchUp);
            }else{
                ofAddListener(ofEvents().mousePressed , this, &ofxSimpleButton::mousePressed);
                ofAddListener(ofEvents().mouseReleased, this, &ofxSimpleButton::mouseReleased);
                ofAddListener(ofEvents().mouseMoved, this, &ofxSimpleButton::mouseMoved);
                ofAddListener(ofEvents().mouseDragged, this, &ofxSimpleButton::mouseDragged);
            }
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
    b_img_route = imgRoute;
    //load image and add to vector
    b_img_fbo.clear();
    
    ofImage b;
    if(b.loadImage(b_img_route+".png")) {
        
        ofFbo img_fbo;
        img_fbo.allocate(b.getWidth(), b.getHeight());
        img_fbo.begin();
        ofClear(255,0);
        img_fbo.end();
        
        img_fbo.begin();
        b.draw(0, 0);
        img_fbo.end();
        
        b_img_fbo.push_back(img_fbo);
    }else {
        ofLog(OF_LOG_ERROR, "couldn't load image");
        return false;
    }
    
    if(b.loadImage(b_img_route+"_.png")){
        
        ofFbo img_fbo;
        img_fbo.allocate(b.getWidth(), b.getHeight());
        img_fbo.begin();
        ofClear(255,0);
        img_fbo.end();
        
        img_fbo.begin();
        b.draw(0, 0);
        img_fbo.end();
        
        b_img_fbo.push_back(img_fbo);
    }
    
    if (b_img_fbo.size() > 0 && !bAppear) {
        setAppear(true);
        
        float w = b_img_fbo[0].getWidth();
        float h = b_img_fbo[0].getHeight();
        b_rect.set(x, y, w, h);
        
        if (useEvent) {
            if (ofGetTargetPlatform() == OF_TARGET_IOS || ofGetTargetPlatform() == OF_TARGET_ANDROID) {
                ofAddListener(ofEvents().touchDown, this, &ofxSimpleButton::touchDown);
                ofAddListener(ofEvents().touchMoved, this, &ofxSimpleButton::touchMoved);
                ofAddListener(ofEvents().touchDoubleTap, this, &ofxSimpleButton::touchDoubleTap);
                ofAddListener(ofEvents().touchUp, this, &ofxSimpleButton::touchUp);
            }else{
                ofAddListener(ofEvents().mousePressed , this, &ofxSimpleButton::mousePressed);
                ofAddListener(ofEvents().mouseReleased, this, &ofxSimpleButton::mouseReleased);
                ofAddListener(ofEvents().mouseMoved, this, &ofxSimpleButton::mouseMoved);
                ofAddListener(ofEvents().mouseDragged, this, &ofxSimpleButton::mouseDragged);
            }
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
/*public */void ofxSimpleButton::setAsAnimationButton(int time){
    
    ofImage a;
    if(!a.loadImage(b_img_route+"__.png")) return;
    
    a_img_fbo.allocate(a.getWidth(), a.getHeight());
    
    a_img_fbo.begin();
    ofClear(255, 0);
    a_img_fbo.end();
    
    a_img_fbo.begin();
    a.draw(0, 0);
    a_img_fbo.end();
    
    bAnimation = true;
    ofAddListener(ofEvents().update, this, &ofxSimpleButton::update);
    
    aniTime = ofGetElapsedTimeMillis();
    changeTime = time;
    
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
        
        if (b_img_fbo.size() > 0 && b_shape == BUTTON_IMAGE) {
            ofEnableAlphaBlending();
            ofSetColor(255, 255);
           
            if (b_img_fbo.size() == 2 && bToggle) { b_img_fbo[1].draw(0, 0); }
            else if (bAnimation && bang) { a_img_fbo.draw(0, 0); }
            else{ b_img_fbo[0].draw(0, 0); }
        
            ofDisableAlphaBlending();
        }else {
            ofPushStyle();
            ofFill();
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
/*public */void ofxSimpleButton::touchDown(float x, float y)
{
    if (isInside(x, y)) {
        buttonAction(true);
    }
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::touchUp(){
    if (b_type == TYPE_BUTTON) {
        bSelect = bToggle = false;
    }else if (b_type == TYPE_TOGGLE) {
        bSelect = false;
    }
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::touchMoved(float x, float y){
    if (!fixPos && bSelect) {
        setPos(x - b_rect.width/2, y - b_rect.height/2);
    }
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::touchDoubleTap(float x, float y){
    if (isInside(x, y)) { bDoubleTab = !bDoubleTab; }
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::mousePressed(float x, float y)
{
    if (isInside(x, y)) {
        buttonAction(true);
    }
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::mouseReleased(){
    if (b_type == TYPE_BUTTON) { bSelect = bToggle = false; }
    else if (b_type == TYPE_TOGGLE) { bSelect = false; }

}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::mouseMoved(float x, float y){
    if (!fixPos && bSelect) {
        setPos(x, y);
    }
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::mouseDragged(float x, float y){
    if (!fixPos && bSelect) {
        setPos(x, y);
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
    if (bAnimation) { resetAniTime(bAppear); }
}

//--------------------------------------------------------------
/*public */void ofxSimpleButton::show()
{
    bAppear = bRender = true;
    if (bAnimation) { resetAniTime(bAppear); }
}

//--------------------------------------------------------------
/*protected */void ofxSimpleButton::resetAniTime(bool start){
    startAni = start;
    bang = false;
    aniTime = ofGetElapsedTimeMillis();
}

//--------------------------------------------------------------
/*protected */void ofxSimpleButton::update(ofEventArgs &event){
    if (startAni) {
        if (ofGetElapsedTimeMillis() - aniTime >= changeTime) {
            bang =! bang;
            aniTime = ofGetElapsedTimeMillis();
        }
    }
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
        setPos(touch.x - b_rect.width/2, touch.y - b_rect.height/2);
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

    if (bToggle) { ofSetColor(b_t_c, 255); }
    else { ofSetColor(b_c, 255); }
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