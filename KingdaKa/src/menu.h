//
//  menu.h
//  KingdaKa
//
//  Created by Firm Read on 7/6/13.
//
//

#ifndef __KingdaKa__menu__
#define __KingdaKa__menu__

#include <iostream>
#include "ofMain.h"
#include "basePage.h"

class menu : public basePage {
    void setup();
    void update();
    
    void draw();
    void reset();
    
    void touchDown(ofTouchEventArgs & touch);
    void touchMoved(ofTouchEventArgs & touch);
    void touchUp(ofTouchEventArgs & touch);
    void touchDoubleTap(ofTouchEventArgs & touch);
    void touchCancelled(ofTouchEventArgs & touch);
    
    ofPoint mode1, mode2, mode3, tutorial, credit;
    

};


#endif /* defined(__KingdaKa__menu__) */
