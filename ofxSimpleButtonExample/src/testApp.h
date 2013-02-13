#pragma once

#include "ofMain.h"
#include "ofxSimpleButton.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofxSimpleButton rectButton[2];
    ofxSimpleButton circleButton[2];
    ofxSimpleButton imageButton;
    ofxSimpleButton dummyButton;
    ofImage image[2];
    bool numImg;
    bool a_s;
		
};
