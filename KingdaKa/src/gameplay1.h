//
//  gameplay1.h
//  KingdaKa
//
//  Created by Firm Read on 7/6/13.
//
//

#ifndef __KingdaKa__gameplay1__
#define __KingdaKa__gameplay1__

#include <iostream>
#include "ofMain.h"
#include "basePage.h"
#include "particle.h"
#include "finger.h"

class gameplay1 : public basePage {
    void setup();
    void update();
    
    void draw();
    void reset();
    
    void touchDown(ofTouchEventArgs & touch);
    void touchMoved(ofTouchEventArgs & touch);
    void touchUp(ofTouchEventArgs & touch);
    void touchDoubleTap(ofTouchEventArgs & touch);
    void touchCancelled(ofTouchEventArgs & touch);
    
    
    
    
    particle particles[2];
    ofRectangle rect_up, rect_down;
    
    vector<finger> fingers;
    
    
    int touch_num_up,touch_num_down;
    ofPolyline area;

};

#endif /* defined(__KingdaKa__gameplay1__) */
