#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "baseScene.h"
#include "baseSetup.h"
#include "menu.h"
#include "crashMode.h"
#include "multithread.h"

class testApp : public ofxiPhoneApp{
	
    public:
        void setup();
        void update();
        void draw();
        void exit();
	
        void touchDown(ofTouchEventArgs & touch);
        void touchMoved(ofTouchEventArgs & touch);
        void touchUp(ofTouchEventArgs & touch);
        void touchDoubleTap(ofTouchEventArgs & touch);
        void touchCancelled(ofTouchEventArgs & touch);

        void lostFocus();
        void gotFocus();
        void gotMemoryWarning();
        void deviceOrientationChanged(int newOrientation);
    
        void reset();
        baseSetup mSetup;
        ofTrueTypeFont font, fontBig;
        menu mMenu;
    
        baseScene * scenes[5];
        int currentScene;
    
        ofImage charTop[3];
        ofImage charBot[3];
    
     
    
};


