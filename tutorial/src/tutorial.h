//
//  tutorial.h
//  KingdaKa
//
//  Created by PengCheng on 7/6/13.
//
//

#ifndef __KingdaKa__tutorial__
#define __KingdaKa__tutorial__

#include "ofMain.h"
#include "particle.h"
#include "finger.h"

enum tutorial_condition {
    STEP_0,
    STEP_1,
    STEP_2,
};

class tutorial{
public:
    void setup();
    void update();
    void draw();
    void touchDown(int x, int y, int ID);
    void touchUp(int x, int y, int ID);
    void touchMove(int x, int y, int ID);

    tutorial_condition condition;
    particle particles[2];
    string command_up,command_down;
    ofTrueTypeFont font, fontBig;
    
    float startTime;
    int num;
    ofImage layout;
    ofImage *myLayout;
    ofRectangle rect[2];
    int width[3];
    ofColor color[2];
    bool bColor[2];
    
    finger mfinger[2];
   
};

#endif /* defined(__KingdaKa__tutorial__) */




















