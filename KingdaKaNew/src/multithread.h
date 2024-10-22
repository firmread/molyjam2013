//
//  multithread.h
//  KingdaKaNew
//
//  Created by PengCheng on 7/12/13.
//
//

#ifndef __KingdaKaNew__multithread__
#define __KingdaKaNew__multithread__

#include "ofMain.h"
#include "baseScene.h"
#include "particle.h"
#include "finger.h"
class smallShape{
public:

    ofPoint org;
    ofPoint pos;
    ofPoint toPos;
    ofColor color;
    float pct;
    bool bFinish;
};


class multithread : public baseScene{
    
public:
    void setup();
    void update();
    void draw();
    
    void content(int num);
    
    void checkWhoIsWinning();
    void determineGesture();
    void crash();
    void carshEffectSetup(ofPoint pos, int num);
    void carshEffect();
    void reset();
    
    void chooseScore();
    void scoreSetup(int num);
    void scoreReset();
    void score();
    
    void gameEnd();
    
    void touchDown(int x, int y, int touchID);
    void touchMove(int x, int y, int touchID);
    void touchUp(int x, int y, int touchID);
    
    float speed[3];

    vector<particle> rPos;
    vector<particle> yPos;
    vector<ofRectangle> rLane;
    vector<ofRectangle> yLane;
    int amount;
    
    //images
    ofImage *rHand[3];
    ofImage *yHand[3];
    
    vector<int> rNum;
    vector<int> yNum;
    
    //winStatus
    string winStatus[3];
    
    //crash
    ofPoint focus;
    float pct;
    bool bCrash[3];
    bool bEffect;
    int crashStep[3];
    bool bCrashEffect;
    ofPoint rSize[3];
    ofPoint ySize[3];
    vector<smallShape> smallShapes;
    //control
    vector<finger> rfinger_0;
    vector<finger> rfinger_1;
    vector<finger> rfinger_2;
    vector<finger> yfinger_0;
    vector<finger> yfinger_1;
    vector<finger> yfinger_2;
    string rCommand[3];
    string yCommand[3];
    
    //score
    vector<ofRectangle>rScore;
    vector<ofRectangle>yScore;
    vector<bool>bRedScore;
    vector<bool>bYellowScore;
    int winScore;
    int rScoreNum;
    int yScoreNum;
    int rCounter;
    int yCounter;
    ofTrueTypeFont *font, *fontBig;
    int timer;
    int whichWin;
};

#endif /* defined(__KingdaKaNew__multithread__) */
