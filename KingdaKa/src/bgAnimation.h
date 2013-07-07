//
//  bgAnimation.h
//  KingdaKa
//
//  Created by PengCheng on 7/7/13.
//
//

#ifndef __KingdaKa__bgAnimation__
#define __KingdaKa__bgAnimation__

#include "ofMain.h"
class bgAnimation{
public:
    void setup(int x, int y);
    void draw();
    
    float num_elements;
    float distance;
    float rotation;
    float rotation_speed;
	float mx,my;
	float rectsize;

};

#endif /* defined(__KingdaKa__bgAnimation__) */
