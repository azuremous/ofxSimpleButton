//
//  ofxSimpleButton.h
//
//  Created by kim jung un a.k.a azuremous on 4/15/12.
//  Copyright (c) 2012~ azuremous.net All rights reserved.
//

#pragma once

#include "ofMain.h"

typedef enum {
    TYPE_BUTTON = 0,
    TYPE_TOGGLE = 1,
    
}TYPE_BUTTONS;

typedef enum { 
    BUTTON_RECT = 1,
    BUTTON_CIRCLE = 2,
    BUTTON_CUSTOM = 3,
    BUTTON_IMAGE = 4
}BUTTON_SHAPES;

class ofxSimpleButton {
private:
    ofRectangle b_rect;
    ofPoint n_pos;
    ofPoint v_pos;
    
    ofColor b_c;
    ofColor b_b_c;
    ofColor b_t_c;
    
    vector<ofFbo> b_img_fbo;
    ofFbo a_img_fbo;
    
    TYPE_BUTTONS b_type;
    BUTTON_SHAPES b_shape;
    
    string b_info_text;
    string b_val_text;
    string b_img_route;
    
    bool useName;
    bool useValue;
    
    bool bRender;
    bool bAppear;
    bool fixPos;
    
    bool bSelect;
    bool bToggle;
    bool bDoubleTab;
    bool bAnimation;
    
    bool bang;
    bool startAni;
    
    int aniTime;
    int changeTime;
    
protected:
    void resetAniTime(bool start);
    
    void update(ofEventArgs &event);
    void render(ofEventArgs &event);
    
    void touchDown(ofTouchEventArgs &touch);
    void touchUp(ofTouchEventArgs &touch);
    void touchMoved(ofTouchEventArgs &touch);
    void touchDoubleTap(ofTouchEventArgs & touch);
    
    void mousePressed(ofMouseEventArgs &mouse);
    void mouseReleased(ofMouseEventArgs &mouse);
    void mouseMoved(ofMouseEventArgs &mouse);
    void mouseDragged(ofMouseEventArgs &mouse);
    
    void updateButtonColor();
    
    void buttonAction(bool b);
    bool isInside(float x, float y);
public:
    explicit ofxSimpleButton();
    virtual~ofxSimpleButton();
    
    bool setup(float x, float y, float w = 50, float h = 50);
    bool setup(float x, float y, float w, float h, bool useEvent, bool manualRender, TYPE_BUTTONS type = TYPE_BUTTON, BUTTON_SHAPES shape = BUTTON_RECT, const ofColor &c = ofColor::white);
    bool setup(float x, float y, string imgRoute, bool useEvent = true, bool manualRender = false, TYPE_BUTTONS type = TYPE_BUTTON);
    
    void setAppear(bool show);
    void setRender(bool magic);
    void setType(TYPE_BUTTONS type);
    void setShape(BUTTON_SHAPES shape);
    void setColor(const ofColor &c);
    void setToggleColor(const ofColor &c);
    void setBackColor(const ofColor &c);
    void setPos(const ofPoint & p);
    void setPos(float x, float y);
    void setName(string n, float n_x = 0, float n_y = -10);
    void setValue(string v, float v_x = 0, float v_y = -10);
    void setFixPos(bool fix);
    void setAsAnimationButton(int time = 500);
    void resetToggle();
    void toggleShow();
    void hide();
    void show();
    
    void render();
    
    void touchDown(float x, float y);
    void mousePressed(float x, float y);
    
    bool getIsAppear() const { return bAppear; }
    bool getIsRender() const { return bRender; }
    bool getIsSelect() const { return bSelect; }
    bool getIsToggl() const { return bToggle; }
    bool getIsDoubleTab() const { return bDoubleTab; }
    
    float getX() const { return b_rect.x; }
    float getY() const { return b_rect.y; }
    float getWidht() const { return b_rect.width; }
    float getHeight() const {return b_rect.height; }
    
};

