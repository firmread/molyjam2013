//
//  basePage.h
//  UI
//
//  Created by Firm Read on 7/6/13.
//
//

#ifndef UI_basePage_h
#define UI_basePage_h
#include "ofMain.h"

class basePage{
public:
    virtual void setup(){}
    virtual void update(){}
    virtual void draw(){}
    virtual void reset(){}
    
    virtual void touchDown(ofTouchEventArgs & touch){}
    virtual void touchMoved(ofTouchEventArgs & touch){}
    virtual void touchUp(ofTouchEventArgs & touch){}
    virtual void touchDoubleTap(ofTouchEventArgs & touch){}
    virtual void touchCancelled(ofTouchEventArgs & touch){}
};


#endif
