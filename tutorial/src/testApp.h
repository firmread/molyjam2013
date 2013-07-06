#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "particle.h"
#include "finger.h"

enum game_condition {
    MAIN_MENU,
    GAME_PLAY
};

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
    
        void reset();
    
        void lostFocus();
        void gotFocus();
        void gotMemoryWarning();
        void deviceOrientationChanged(int newOrientation);
    
        game_condition condition;
    
    
    
    //MENU
    ofPoint menuDots[5];
    ofColor blue;
    
    ofTrueTypeFont font, fontBig;
    
    bool bSplash;
    
        //GAMEPLAY
        particle particles[2];
        ofRectangle rect_up, rect_down;
        vector<finger> mfinger_up;
        vector<finger> mfinger_down;


        int touch_num_up,touch_num_down;
        string command_up,command_down;
    
    ofPoint menuButton[2];
    int menuButtonSize;
    
    bool bPause;
    ofPoint pauseMenu[2];
    
    bool bEndGame;

};


