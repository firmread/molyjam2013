#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "particle.h"
#include "finger.h"

enum game_condition {
    MAIN_MEUN,
    GAME_PLAY,
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
    
        void menuPage();
        void gamePlay();
    
        void lostFocus();
        void gotFocus();
        void gotMemoryWarning();
        void deviceOrientationChanged(int newOrientation);

    
        game_condition condition;
    
        particle particles[2];
        ofRectangle rect_up, rect_down;
        ofRectangle button_1, button_2;
        vector<finger> mfinger_up;
        vector<finger> mfinger_down;


        int touch_num_up,touch_num_down;
        string command_up,command_down;
    
    

};


