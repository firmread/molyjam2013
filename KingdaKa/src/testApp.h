#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "particle.h"
#include "finger.h"


#define MAIN_MENU_ITEMS 5
#define PAUSE_MENU_ITEMS 2
#define END_MENU_ITEMS 3

enum game_condition {
    MAIN_MENU,
    GAME_PLAY,
    CREDITS
};

class testApp : public ofxiPhoneApp{

public:
    void setup();
    void update();
    void draw();
    void camera();
    void exit();

    void touchDown(ofTouchEventArgs & touch);
    void touchMoved(ofTouchEventArgs & touch);
    void touchUp(ofTouchEventArgs & touch);
    void touchDoubleTap(ofTouchEventArgs & touch);
    void touchCancelled(ofTouchEventArgs & touch);

    void reset();
    void resetScore();
    void checkWhoIsWinning();

    void lostFocus();
    void gotFocus();
    void gotMemoryWarning();
    void deviceOrientationChanged(int newOrientation);

    game_condition condition;

    
    
    //MAIN_MENU
    ofPoint menuDots[MAIN_MENU_ITEMS];
    ofColor blue, red, yellow;
    
    ofTrueTypeFont font, fontBig;
    
    bool bSplash;
    
    //GAME_PLAY
    particle particles[2];
    ofRectangle rect_up, rect_down;
    vector<finger> mfinger_up;
    vector<finger> mfinger_down;
    float particleSpeed;

    int touch_num_up,touch_num_down;
    string command_up,command_down;
    //
    ofPoint menuButton[2];
    int menuButtonSize;
    //
    bool bPause;
    ofPoint pauseMenu[PAUSE_MENU_ITEMS];
    //
    bool bEndGame;
    ofPoint endGameMenu[END_MENU_ITEMS];
    
    int endCountDown, endCountDownStart;
    bool bDidYouEvenPlayingMan;
    bool bRedWin, bYellowWin, bDrawGame;
    
    int rScore, yScore;
    
    float dis;
    
    //crash effect
    bool bEffect;
    int frameRate;
    float zoom, zoomSpeed, zoomPct;

};


