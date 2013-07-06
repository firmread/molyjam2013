//
//  menu.h
//  UI
//
//  Created by Firm Read on 7/6/13.
//
//

#ifndef __UI__menu__
#define __UI__menu__

#include <iostream>
#include "ofMain.h"
#include "basePage.h"

class menu: public basePage{
    
    void setup();
    void update();
    void draw();
    void reset();
    
    void touchDown(ofTouchEventArgs & touch);
    void touchMoved(ofTouchEventArgs & touch);
    void touchUp(ofTouchEventArgs & touch);
    void touchDoubleTap(ofTouchEventArgs & touch);
    void touchCancelled(ofTouchEventArgs & touch);
    
    ofPoint menuDots[5];
    bool bMenu[5];
    ofColor blue;
    
//    ofTrueTypeFont *font, *fontBig;
    
    bool splash;
    
};
#endif /* defined(__UI__menu__) */
