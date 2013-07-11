//
//  crashMode.h
//  KingdaKaNew
//
//  Created by PengCheng on 7/10/13.
//
//

#ifndef __KingdaKaNew__crashMode__
#define __KingdaKaNew__crashMode__

#include "ofMain.h"
#include "baseScene.h"
#include "finger.h"
#include "particle.h"

#define SCORE_MENU 3

enum winn_situation {
    CHOOSE_SCORE,
    EMPTY_WIN,
    TOP_WIN,
    BOT_WIN,
    DRAW_WIN,
    GAME_END,
};

class crashMode: public baseScene{
public:
     void setup();
     void update();
     void draw();
     void chooseScore();
     void content(int num);
     void checkWhoIsWinning();
     void determineGesture();
     void crash();
     void reset();
     void scoreSetup(int num);
     void scoreReset();
     void score();
     void gameEnd();
     void touchDown(int x, int y, int touchID);
     void touchMove(int x, int y, int touchID);
     void touchUp(int x, int y, int touchID);
     
    winn_situation situation;
    
    //touch detect
    particle particles[2];
    ofRectangle rect_up, rect_down;
    vector<finger> mfinger_up;
    vector<finger> mfinger_down;
    float particleSpeed;
    string command_up,command_down;

    //images
    ofImage *charTop[3];
    ofImage *charBot[3];
    int N1,N2;
    
    //score
    ofPoint scoreMenu[SCORE_MENU];
    vector<ofRectangle> scoreTop;
    vector<ofRectangle> scoreBot;
    vector<bool> bScoreTop;
    vector<bool> bScoreBot;
    int scoreNum1,scoreNum2;
    float scoreMenuSize;
    int winScore;
    //comtent
    int contentNum;
    
    
    //effect
    float zoom;
    float zPct;
    float zSpeed;
    bool bZoomIn;
    float size1,size2;
    float cX,cY;
    
    //font
    ofTrueTypeFont *font, *fontBig;
    
};

#endif /* defined(__KingdaKaNew__crashMode__) */
