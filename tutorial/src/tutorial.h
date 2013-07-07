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
    void touchDown(int x, int y, int touchNum);
    void touchUp(int x, int y, int touchNum);
    void touchMove(int x, int y, int touchNum);

    tutorial_condition condition;
    particle particles[2];
    string command_up,command_down;
    ofTrueTypeFont font, fontBig;
    
    float startTime;
    int num;
    ofImage layout;
    ofImage *;
};

#endif /* defined(__KingdaKa__tutorial__) */




















