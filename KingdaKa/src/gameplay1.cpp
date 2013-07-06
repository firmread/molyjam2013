//
//  gameplay1.cpp
//  KingdaKa
//
//  Created by Firm Read on 7/6/13.
//
//

#include "gameplay1.h"

void gameplay1::setup(){
    
    ofBackground(86, 217, 205);
    
    particles[0].setInitialCondition(384, 24, 0, 5);
    particles[1].setInitialCondition(384, 1000, 0, -5);
    
    rect_up.set(0, 0, 768, 512);
    rect_down.set(0, 512, 768, 512);
    
    touch_num_up = 0;
}

void gameplay1::update(){
    
    for (int i =0; i<2; i++) {
        particles[i].resetForce();
    }
    
    particles[0].addAttractionForce(particles[1], 1024, 0.05);
    particles[1].addAttractionForce(particles[0], 1024, 0.05);
    
    for (int i =0; i<2; i++) {
        particles[i].addDampingForce();
        particles[i].update();
    }
    
    cout<<"touch_num_up:  "<<touch_num_up<<"  fingers Number:  "<<fingers.size()<<endl;
}

void gameplay1::draw(){
    
    ofSetColor(247, 255, 236);
    ofCircle(particles[0].pos.x,particles[0].pos.y, 10);
    ofCircle(particles[1].pos.x,particles[1].pos.y, 10);
    
}

void gameplay1::touchDown(ofTouchEventArgs & touch){
    if (rect_up.inside(touch.x, touch.y)) {
        finger temp;
        temp.ID = touch.id;
        temp.district = 0;
        temp.pos.set(touch.x, touch.y);
        temp.prePos.set(touch.x, touch.y);
        fingers.push_back(temp);
        
        touch_num_up ++;
    }
    
}

void gameplay1::touchMoved(ofTouchEventArgs & touch){
    for (int i =0; i<fingers.size(); i++) {
        if (touch_num_up) {
            
        }
    }
}

void gameplay1::touchUp(ofTouchEventArgs & touch){
    
    for (int i =0; i<fingers.size(); i++) {
        
        if (fingers[i].district == 0 && touch.id == fingers[i].ID) {
            
            fingers.erase(fingers.begin()+i);
            touch_num_up --;
        }
        
    }

}

void gameplay1::touchDoubleTap(ofTouchEventArgs & touch){
    
}

void gameplay1::touchCancelled(ofTouchEventArgs & touch){
    
}