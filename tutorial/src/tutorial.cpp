//
//  tutorial.cpp
//  KingdaKa
//
//  Created by PengCheng on 7/6/13.
//
//

#include "tutorial.h"


//--------------------------------------------
void tutorial::setup(){
    condition = STEP_0;
    
    particles[0].setInitialCondition(384, 24, 0, 5);
    particles[1].setInitialCondition(384, 1000, 0, -5);
    font.loadFont("impact.ttf", 14);
    fontBig.loadFont("impact.ttf", 72);
    
    num = 0;
    layout.loadImage("image/layout.png");

}

//--------------------------------------------
void tutorial::update(){

    switch (condition) {
        case STEP_0:{
            
            
            for (int i =0; i<2; i++) {
                particles[i].resetForce();
               
            }
            
            particles[0].addForce(0, 0.3);
            particles[1].addForce(0, -0.3);

            particles[0].addAttractionForce(particles[1], 1024, 0.08);
            particles[1].addAttractionForce(particles[0], 1024, 0.08);
            
            for (int i =0; i<2; i++) {
                particles[i].addDampingForce();
                particles[i].update();
            }
            
            float dis = particles[0].pos.distance(particles[1].pos);
            if (dis < 600) {
                condition = STEP_1;
                startTime = ofGetElapsedTimeMillis();
            }
            
        }
            break;
        case STEP_1:{
            
            for (int i =0; i<2; i++) {
                particles[i].resetForce();
            }
            
            if (ofGetElapsedTimeMillis()-startTime>2000) {
                if (num < 3) {
                   num ++; 
                }
                startTime = ofGetElapsedTimeMillis();
            }
            
            
            
        }
            break;
        case STEP_2:
            
            break;
    }
}

//--------------------------------------------
void tutorial::draw(){
    ofBackground(86, 217, 205);
    switch (condition) {
        case STEP_0:{
            
            ofSetColor(247, 255, 236);
            particles[0].particleStance = 1;
            particles[0].draw();
            
            ofSetColor(100);
            particles[1].particleStance = 1;
            particles[1].draw();
            
        }
            break;
        case STEP_1:{
            
            if (num == 0) {
              
            ofSetColor(247, 255, 236);
            particles[0].particleStance = 1;
            particles[0].draw();
            
            ofSetColor(100);
            particles[1].particleStance = 1;
            particles[1].draw();
            
            ofSetColor(30, 30, 30);
            ofSetLineWidth(3);
            ofLine(particles[1].pos.x,  particles[1].pos.y, particles[1].pos.x+150,  particles[1].pos.y-100);
            ofSetRectMode(OF_RECTMODE_CENTER);
            ofRect(particles[1].pos.x+150, particles[1].pos.y-100, 200, 100);
            ofSetColor(255);
            string sOne;
            if (num ==0) {
                sOne = "This is your fist";
                font.drawString(sOne,
                                particles[1].pos.x+150-(int)font.stringWidth(sOne)/2,
                                particles[1].pos.y-100+(int)font.stringHeight(sOne)/2);

            }
            else if(num == 1){
                sOne = "Now let's make scissors";
                font.drawString(sOne,
                                particles[1].pos.x+150-(int)font.stringWidth(sOne)/2,
                                particles[1].pos.y-100+(int)font.stringHeight(sOne)/2);

                }
            else if (num == 2){
                
                
            }
                
            }
        
        }
                           
            break;
        case STEP_2:
            
            break;
    }
}

//--------------------------------------------
void tutorial::touchDown(int x, int y, int touchNum){
    switch (condition) {
        case STEP_0:{
            
        }
        break;
            
        case STEP_1:{
            
        }
            break;
            
        case STEP_2:{
            
            
            
        }
            break;
    
    }
    
}

//--------------------------------------------
void tutorial::touchMove(int x, int y, int touchNum){
    switch (condition) {
        case STEP_0:{
            
            
            
        }
            break;
            
        case STEP_1:{
            
            
        }
            break;
            
        case STEP_2:{
            
            
            
        }
            break;
            
    }

}

//--------------------------------------------
void tutorial::touchUp(int x, int y, int touchNum){
    switch (condition) {
        case STEP_0:{
            
            
            
        }
            break;
            
        case STEP_1:{
            
            
        }
            break;
            
        case STEP_2:{
            
            
            
        }
            break;
            
    }
}