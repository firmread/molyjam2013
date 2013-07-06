//
//  basePage.h
//  KingdaKa
//
//  Created by Firm Read on 7/6/13.
//
//

#ifndef KingdaKa_basePage_h
#define KingdaKa_basePage_h

#include "ofMain.h"

class basePage{
public:
    
    
    virtual void allocateFbo(){
        myPageAsFbo.allocate(1024,768, GL_RGBA, 4);
    }
    
    virtual void setup(){};
    virtual void update(){}
    
    virtual void drawFboStart(){
        myPageAsFbo.begin();
        ofClear(255,255,255,255);
    }
    
    virtual void drawFboEnd(){
        myPageAsFbo.end();
    }
    
    virtual void drawFboDraw(){
        myPageAsFbo.draw(0,0);
    }
    
    virtual void draw(){}
    virtual void reset(){}
    
    virtual void touchDown(ofTouchEventArgs & touch);
    virtual void touchMoved(ofTouchEventArgs & touch);
    virtual void touchUp(ofTouchEventArgs & touch);
    virtual void touchDoubleTap(ofTouchEventArgs & touch);
    virtual void touchCancelled(ofTouchEventArgs & touch);
    
    ofFbo myPageAsFbo;
    
    ofTrueTypeFont * font;
    

    
};


#endif
