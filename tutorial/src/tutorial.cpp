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
    myLayout = & layout;
    

    rect[0].set(241, 815, 104, 104);
    rect[1].set(425, 715, 104, 104);
    
    width[0] =102;
    width[1] = 72;
    width[2] = 42;
    
    bColor[0]= false;
    bColor[1] =false;
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
            if (dis < 500) {
                condition = STEP_1;
                startTime = ofGetElapsedTimeMillis();
            }
            
        }
            break;
        case STEP_1:{
            
            for (int i =0; i<2; i++) {
                particles[i].resetForce();
            }
            
                       
            if (ofGetElapsedTimeMillis()-startTime>1300) {
                if (num < 2) {
                   num ++; 
                }
                startTime = ofGetElapsedTimeMillis();
            }
            
            if (bColor[0]) {
                color[0].set(255, 255, 0,200);
            }else{
                color[0].set(200, 200, 200,100);
            }
            if (bColor[1]) {
                color[1].set(255, 255, 0,200);
            }else{
                color[1].set(200, 200, 200,100);
            }
        
           
            
            cout<<num<<endl;
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
        
            ofSetColor(247, 255, 236);
            particles[0].particleStance = 1;
            particles[0].draw();
            
            ofSetColor(100);
            particles[1].particleStance = 1;
            particles[1].draw();
            
            
           
            string sOne;
            if (num ==0) {
                ofSetColor(30, 30, 30);
                ofSetLineWidth(3);
                ofLine(particles[1].pos.x,  particles[1].pos.y, particles[1].pos.x-150,  particles[1].pos.y-100);
                ofSetRectMode(OF_RECTMODE_CENTER);
                ofRect(particles[1].pos.x-150, particles[1].pos.y-100, 200, 100);
                ofSetColor(255);
                sOne = "This is your fist";
                font.drawString(sOne,
                                particles[1].pos.x-150-(int)font.stringWidth(sOne)/2,
                                particles[1].pos.y-100+(int)font.stringHeight(sOne)/2);

            }
            else if(num == 1){
                ofSetColor(30, 30, 30);
                ofSetLineWidth(3);
                ofLine(particles[1].pos.x,  particles[1].pos.y, particles[1].pos.x-150,  particles[1].pos.y-100);
                ofSetRectMode(OF_RECTMODE_CENTER);
                ofRect(particles[1].pos.x-150, particles[1].pos.y-100, 250, 100);
                ofSetColor(255);
                sOne = "Now let's make scissors";
                font.drawString(sOne,
                                particles[1].pos.x-150-(int)font.stringWidth(sOne)/2,
                                particles[1].pos.y-100+(int)font.stringHeight(sOne)/2);
                ofSetRectMode(OF_RECTMODE_CORNER);

                }
            else if (num == 2){
                
                width[0]--;
                width[1]--;
                width[2]--;
                if (width[0]<0) {
                    width[0] = 102;
                }
                
                if (width[1]<0) {
                    width[1] = 102;
                }
                
                if (width[2]<0) {
                    width[2] = 102;
                }
                
                ofSetRectMode(OF_RECTMODE_CENTER);
                ofSetColor( color[0]);
                ofRect(rect[0].getCenter(),width[0],width[0]);
                ofSetColor( color[1]);
                ofRect(rect[1].getCenter(),width[0],width[0]);
                ofSetColor( color[0]);
                ofRect(rect[0].getCenter(),width[1],width[1]);
                ofSetColor( color[1]);
                ofRect(rect[1].getCenter(),width[1],width[1]);
                ofSetColor( color[0]);
                ofRect(rect[0].getCenter(),width[2],width[2]);
                ofSetColor( color[1]);
                ofRect(rect[1].getCenter(),width[2],width[2]);
                ofSetRectMode(OF_RECTMODE_CORNER);
                ofSetColor(255);
                myLayout->draw(rect[0]);
                myLayout->draw(rect[1]);
            
                ofSetColor(30, 30, 30);
                ofSetRectMode(OF_RECTMODE_CENTER);
                ofRect(particles[1].pos.x-150, particles[1].pos.y-100, 300, 100);
                
                ofSetColor(255);
                sOne = "Try to tap two boxes together";
                font.drawString(sOne,
                                particles[1].pos.x-150-(int)font.stringWidth(sOne)/2,
                                particles[1].pos.y-100+(int)font.stringHeight(sOne)/2);
                
                if (bColor[0]&&bColor[1]) {
                    num = 3;
                    startTime = ofGetElapsedTimeMillis();
                    width[0] = 102;
                    width[1] = 72;
                    width[2] = 42;
                }
            }
            else if (num == 3){
                ofSetColor(30, 30, 30);
                ofSetRectMode(OF_RECTMODE_CENTER);
                ofRect(particles[1].pos.x-150, particles[1].pos.y-100, 330, 100);
                
                ofSetColor(255);
                sOne = "Great,  let's make a paper";
                font.drawString(sOne,
                                particles[1].pos.x-150-(int)font.stringWidth(sOne)/2,
                                particles[1].pos.y-100+(int)font.stringHeight(sOne)/2);
               
                
                width[0]--;
                width[1]--;
                width[2]--;
                if (width[0]<0) {
                    width[0] = 102;
                }
                
                if (width[1]<0) {
                    width[1] = 102;
                }
                
                if (width[2]<0) {
                    width[2] = 102;
                }
                ofSetRectMode(OF_RECTMODE_CENTER);
                ofSetColor( color[0]);
                ofRect(rect[0].getCenter(),width[0],width[0]);
                ofSetColor( color[1]);
                ofRect(rect[1].getCenter(),width[0],width[0]);
                ofSetColor( color[0]);
                ofRect(rect[0].getCenter(),width[1],width[1]);
                ofSetColor( color[1]);
                ofRect(rect[1].getCenter(),width[1],width[1]);
                ofSetColor( color[0]);
                ofRect(rect[0].getCenter(),width[2],width[2]);
                ofSetColor( color[1]);
                ofRect(rect[1].getCenter(),width[2],width[2]);
                ofSetRectMode(OF_RECTMODE_CORNER);
                ofSetColor(255);
                myLayout->draw(rect[0]);
                myLayout->draw(rect[1]);
                
                ofSetColor(255,100);
                myLayout->draw(220, 875,rect[0].width,rect[0].height);
                myLayout->draw(485, 655,rect[1].width,rect[1].height);
                
            }
            else if(num == 4){
            
                ofSetColor(30, 30, 30);
                ofSetRectMode(OF_RECTMODE_CENTER);
                ofRect(particles[1].pos.x-150, particles[1].pos.y-100, 300, 100);
                
                ofSetColor(255);
                sOne = "Awesome,last try, make a rock";
                font.drawString(sOne,
                                particles[1].pos.x-150-(int)font.stringWidth(sOne)/2,
                                particles[1].pos.y-100+(int)font.stringHeight(sOne)/2);
                
                width[0]--;
                width[1]--;
                width[2]--;
                if (width[0]<0) {
                    width[0] = 102;
                }
                
                if (width[1]<0) {
                    width[1] = 102;
                }
                
                if (width[2]<0) {
                    width[2] = 102;
                }
                ofSetRectMode(OF_RECTMODE_CENTER);
                ofSetColor( color[0]);
                ofRect(rect[0].getCenter(),width[0],width[0]);
                ofSetColor( color[1]);
                ofRect(rect[1].getCenter(),width[0],width[0]);
                ofSetColor( color[0]);
                ofRect(rect[0].getCenter(),width[1],width[1]);
                ofSetColor( color[1]);
                ofRect(rect[1].getCenter(),width[1],width[1]);
                ofSetColor( color[0]);
                ofRect(rect[0].getCenter(),width[2],width[2]);
                ofSetColor( color[1]);
                ofRect(rect[1].getCenter(),width[2],width[2]);
                ofSetRectMode(OF_RECTMODE_CORNER);
                ofSetColor(255);
                myLayout->draw(rect[0]);
                myLayout->draw(rect[1]);
                
                ofSetColor(255,100);
                myLayout->draw(290, 805,rect[0].width,rect[0].height);
                myLayout->draw(415, 735,rect[1].width,rect[1].height);
                
            }
           
        }
                           
            break;
        case STEP_2:
            
            break;
    }
}

//--------------------------------------------
void tutorial::touchDown(int x, int y, int ID){
    switch (condition) {
        case STEP_0:{
            
        }
        break;
            
        case STEP_1:{
           
            if (rect[0].inside(x, y)) {
                mfinger[0].pos.set(x, y);
                mfinger[0].prePos.set(x, y);
                mfinger[0].ID = ID;
                bColor[0] = true;
                if (num >2) {
                    rect[0].setFromCenter(mfinger[0].pos.x, mfinger[0].pos.y, 104, 104);                    
                }
            }
            
            if (rect[1].inside(x, y)) {
                mfinger[1].pos.set(x, y);
                mfinger[1].prePos.set(x, y);
                mfinger[1].ID = ID;
                bColor[1] = true;
                if (num >2) {
                    rect[1].setFromCenter(mfinger[1].pos.x, mfinger[1].pos.y, 104, 104);
                }
            }

        }
        break;
            
        case STEP_2:{
            
            
            
            
        }
        break;
    
    }
    
}

//--------------------------------------------
void tutorial::touchMove(int x, int y, int ID){
    switch (condition) {
        case STEP_0:{
            
            
            
        }
            break;
            
        case STEP_1:{
            
          
            
            
            if (ID == mfinger[0].ID) {
                mfinger[0].pos.set(x, y);
                if (!rect[0].inside(x, y)) {
                    bColor[0] = false;
                }else{
                    bColor[0] = true;
                    if (num > 2) {
                        rect[0].setFromCenter(mfinger[0].pos.x, mfinger[0].pos.y, 104, 104);
                    }
                }
                
            }
            
            if (ID == mfinger[1].ID) {
                mfinger[1].pos.set(x, y);
                if (!rect[1].inside(x, y)) {
                    bColor[1] = false;
                }else{
                    bColor[1] = true;
                    if (num > 2) {
                        rect[1].setFromCenter(mfinger[1].pos.x, mfinger[1].pos.y, 104, 104);
                    }
                }
            }
            
            if (num == 3) {
                float dis = mfinger[0].pos.distance(mfinger[1].pos);
                float preDis = mfinger[0].prePos.distance(mfinger[1].prePos);
                float diff = dis -preDis;
                if (diff > 100) {
                    num = 4;
                    mfinger[0].prePos = mfinger[0].pos;
                    mfinger[1].prePos = mfinger[1].pos;
                }
            }
            
            if (num == 4) {
                float dis = mfinger[0].pos.distance(mfinger[1].pos);
                float preDis = mfinger[0].prePos.distance(mfinger[1].prePos);
                float diff = dis -preDis;
                if (diff < 100) {
                    
                    mfinger[0].prePos = mfinger[0].pos;
                    mfinger[1].prePos = mfinger[1].pos;
                }
            }
            
        }
            break;
            
        case STEP_2:{
            
            
            
        }
            break;
            
    }

}

//--------------------------------------------
void tutorial::touchUp(int x, int y, int ID){
    switch (condition) {
        case STEP_0:{
            
            
            
        }
            break;
            
        case STEP_1:{
            if (ID == mfinger[0].ID) {
                
                    bColor[0] = false;
                
            }
            
            if (ID == mfinger[1].ID) {
                
                    bColor[1] = false;
               
            }
        }
            break;
            
        case STEP_2:{
            
            
            
        }
            break;
            
    }
}