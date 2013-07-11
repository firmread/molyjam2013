//
//  baseSetup.h
//  KingdaKaNew
//
//  Created by PengCheng on 7/10/13.
//
//

#ifndef KingdaKaNew_baseSetup_h
#define KingdaKaNew_baseSetup_h

#include "ofMain.h"

class baseSetup{
public:
    void setup(){
        ofSetVerticalSync(true);
        ofSetFrameRate(60);
        ofBackground(255);
        ofSetCircleResolution(120);
        ofEnableSmoothing();
        ofEnableAlphaBlending();
        //	ofxAccelerometer.setup();
    }
};

#endif
