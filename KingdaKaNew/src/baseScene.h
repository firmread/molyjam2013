//
//  baseScene.h
//  Kingda_Ka_New
//
//  Created by PengCheng on 7/10/13.
//
//

#ifndef __Kingda_Ka_New__baseScene__
#define __Kingda_Ka_New__baseScene__

class baseScene{
    
public:
    
    virtual void setup(){};
    virtual void update(){};
    virtual void draw(){};
    
    virtual void touchDown(int x, int y, int touchID){};
    virtual void touchMove(int x, int y, int touchID){};
    virtual void touchUp(int x, int y, int touchID){};
};

#endif /* defined(__Kingda_Ka_New__baseScene__) */
