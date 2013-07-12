//
//  crashMode.cpp
//  KingdaKaNew
//
//  Created by PengCheng on 7/10/13.
//
//

#include "crashMode.h"

void crashMode::setup(){
    
    
    rect_up.set(0, 0, 768, 512);
    rect_down.set(0, 512, 768, 512);

    reset();
    
   
}
//-------------------------------------------------------
void crashMode::scoreReset(){
    scoreNum1 = scoreNum2 = 0;
    scoreTop.clear();
    scoreBot.clear();
    bScoreTop.clear();
    bScoreBot.clear();
}

//-------------------------------------------------------
void crashMode::scoreSetup(int num){
    winScore = num;
    for (int i =0 ; i< winScore; i++) {
        ofRectangle temp;
        temp.set(30, 30+i*40, 10, 10);
        scoreTop.push_back(temp);
        temp.set(30, 1024-30-i*40, 10, 10);
        scoreBot.push_back(temp);
        
        bool bTemp = false;
        bScoreTop.push_back(bTemp);
        bScoreBot.push_back(bTemp);
    }
}

//-------------------------------------------------------
void crashMode::score(){
    
    for (int i =0; i<scoreNum1; i++) {
        bScoreTop[i] = true;
    }
    
    for (int i =0 ; i< scoreTop.size(); i++) {
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofSetColor(127);
        ofRect(scoreTop[i].position,12,12);
        bScoreTop[i]?  ofSetColor(30, 30, 30): ofSetColor(200, 200, 200);
        ofRect(scoreTop[i]);
        ofSetRectMode(OF_RECTMODE_CORNER);
    }
    
    for (int i =0; i<scoreNum2; i++) {
        bScoreBot[i] = true;
    }
    
    for (int i =0 ; i< scoreBot.size(); i++) {
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofSetColor(127);
        ofRect(scoreBot[i].position,12,12);
        bScoreBot[i]?  ofSetColor(30, 30, 30): ofSetColor(200, 200, 200);
        ofRect(scoreBot[i]);
        ofSetRectMode(OF_RECTMODE_CORNER);
    }
    
    ofSetColor(255,0,0);
    string scoreTop = ofToString(scoreNum1);
   
  
    
    ofPushMatrix();
    ofTranslate(50, ofGetHeight()/2-100);
    ofRotate(180, 0, 0, 1);
    fontBig->drawString(scoreTop,-(int)fontBig->stringWidth(scoreTop)/2,-(int)fontBig->stringHeight(scoreTop)/2);
    ofPopMatrix();
   
    
    ofSetColor(251, 175, 24);
    string scoreBot = ofToString(scoreNum2);
    fontBig->drawString(scoreBot,
                        50-(int)fontBig->stringWidth(scoreBot)/2,
                        ofGetHeight()/2+50+(int)fontBig->stringHeight(scoreTop)/2);
}
//-------------------------------------------------------
void crashMode::reset(){
    situation = EMPTY_WIN;
    contentNum = 0;
    
    particleSpeed = ofRandom(0.2,0.8);
    
    particles[0].setInitialCondition(ofGetWidth()/2, 0, 0, 5);
    particles[1].setInitialCondition(ofGetWidth()/2, ofGetHeight(), 0, -5);
    
    string myString[3];
    myString[0] = "rock";
    myString[1] = "paper";
    myString[2] = "scissors";
    command_up = myString[(int)ofRandom(0 , 2)];
    command_down = myString[(int)ofRandom(0, 2)];
    
    zoom = 0;
    zPct = 0;
    zSpeed = 0.05f;
    size1 = 150;
    size2 = 150;
    bZoomIn = true;

    cX=0;
    cY=0;
    
    
}

//-------------------------------------------------------
void crashMode::update(){
  
    switch (situation) {
            
        case EMPTY_WIN:{
            
            determineGesture();
            
            for (int i =0; i<2; i++) {
                particles[i].resetForce();
            }
            
            particles[0].addAttractionForce(particles[1], 1024, particleSpeed);
            particles[1].addAttractionForce(particles[0], 1024, particleSpeed);
            
            for (int i =0; i<2; i++) {
                particles[i].addDampingForce();
                particles[i].update();
            }
            
            checkWhoIsWinning();
            
        }break;
    
            
    }
    
   
    
    
    
}

//-------------------------------------------------------
void crashMode::draw(){
    
    content(contentNum);
    score();
}
//-------------------------------------------------------
void crashMode::gameEnd(){
    if (scoreNum1 == winScore) {
        situation = GAME_END_TOP_WIN;
    }else if (scoreNum2 == winScore){
        situation = GAME_END_BOT_WIN;
    }else{
        reset();
    }
}

//-------------------------------------------------------
void crashMode::checkWhoIsWinning(){
    float dis;
    dis = particles[0].pos.distance(particles[1].pos);
    
    if (dis > 10 && dis < 80 && situation == EMPTY_WIN) {
        
        contentNum = 1;
        
        if (N1 == 0) {
            if (N2 == 0) {
                situation = DRAW_WIN; 
            }else if (N2 == 1) {
                situation = TOP_WIN;
                scoreNum1 ++;
            }else if (N2 == 2) {
                situation = BOT_WIN;
                scoreNum2 ++;
            }
        }else if(N1 == 1){
            if (N2 == 0) {
                situation = BOT_WIN;
            }else if (N2 == 1) {
                situation = DRAW_WIN; 
            }else if (N2 == 2) {
                situation = TOP_WIN; 
                scoreNum1 ++;
            }
        }else if(N1 == 2){
            if (N2 == 0) {
                situation = TOP_WIN; 
                scoreNum1 ++;
            }else if (N2 == 1) {
                situation = BOT_WIN; 
                scoreNum2 ++;
            }else if (N2 == 2) {
                situation = DRAW_WIN; 
            }
        }
    }
    
    
    
}

//-------------------------------------------------------
void crashMode::content(int num){
    ofBackground(255);
    
    if (num == 0) {
        ofSetColor(255);
        ofPushMatrix();
        ofTranslate(particles[0].pos.x,particles[0].pos.y);
        ofRotateZ(180);
        ofSetRectMode(OF_RECTMODE_CENTER);
        charTop[N1]->draw(0,0, size1, size1);
        ofSetRectMode(OF_RECTMODE_CORNER);
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(particles[1].pos.x,particles[1].pos.y);
        ofSetRectMode(OF_RECTMODE_CENTER);
        charBot[N2]->draw(0,0, size2, size2);
        ofSetRectMode(OF_RECTMODE_CORNER);
        ofPopMatrix();
    }
    
    if (num == 1) {
        ofSetColor(255);
        
        crash();
        
        ofPushMatrix();
            ofTranslate(cX, cY,zoom);
            ofPushMatrix();
            ofTranslate(particles[0].pos.x,particles[0].pos.y);
            ofRotateZ(180);
            ofSetRectMode(OF_RECTMODE_CENTER);
            charTop[N1]->draw(0,0, size1, size1);
            ofSetRectMode(OF_RECTMODE_CORNER);
            ofPopMatrix();
            
            ofPushMatrix();
            ofTranslate(particles[1].pos.x,particles[1].pos.y);
            ofSetRectMode(OF_RECTMODE_CENTER);
            charBot[N2]->draw(0,0, size2, size2);
            ofSetRectMode(OF_RECTMODE_CORNER);
            ofPopMatrix();
        ofPopMatrix();

    }
    
    if (num == 2) {
    
        
    
    }

}

//-------------------------------------------------------
void crashMode::crash(){

   
    if(bZoomIn){
        zPct += zSpeed;
        cX = (int)ofRandom(-5,5);
        cY = (int)ofRandom(-10,10);
        ofBackground(int(ofRandom(0,70)));
    }else{
        zoom = 0;
        ofBackground(255);
        gameEnd();
    }
    
    if (zPct > 1) {
        zPct = 1;
        bZoomIn = false;
    }
    
    
    if (bZoomIn) {
        zoom = (1-zPct)*zoom + zPct*600;
    }
    
    
    if (situation == TOP_WIN) {
        size2 -= 5;
        if (size2 < 0) {
            size2 = 0;
        }
    }else if(situation == BOT_WIN){
        size1 -= 5;
        if (size1 < 0) {
            size1 = 0;
        }
    }else if(situation == DRAW_WIN){
        size1 -= 1;
        size2 -= 1;
        if (size1 < 0) {
            size1 = 0;
        }
        if (size2 < 0) {
            size2 = 0;
        }
    }
    
    

}

//-------------------------------------------------------
void crashMode::determineGesture(){
    if (command_up == "rock") {
        N1 = 0;
    }else if(command_up == "scissors"){
        N1 = 1;
    }else if(command_up == "paper"){
        N1 = 2;
    }
    
    if (command_down == "rock") {
        N2 = 0;
    }else if(command_down == "scissors"){
        N2 = 1;
    }else if(command_down == "paper"){
        N2 = 2;
    }
    
}

//-------------------------------------------------------
void crashMode::touchDown(int x, int y, int touchID){
    switch (situation) {
                    
        case EMPTY_WIN:{
            if (rect_up.inside(x, y)) {
                finger temp;
                temp.ID = touchID;
                temp.pos.set(x, y);
                temp.prePos.set(x, y);
                mfinger_up.push_back(temp);
            }
            
            if (rect_down.inside(x, y)) {
                finger temp;
                temp.ID = touchID;
                temp.pos.set(x, y);
                temp.prePos.set(x, y);
                mfinger_down.push_back(temp);
            }

        }break;
    }
    
}

//-------------------------------------------------------
void crashMode::touchMove(int x, int y, int touchID){
    
    switch (situation) {
            
        case EMPTY_WIN:{
            
            if (mfinger_up.size()>1){
                for (int i =0; i<mfinger_up.size(); i++){
                    if (touchID == mfinger_up[i].ID) {
                        mfinger_up[i].pos.set(x, y);
                        float dis =  mfinger_up.back().pos.distance(mfinger_up[mfinger_up.size()-2].pos);
                        float preDis =  mfinger_up.back().prePos.distance(mfinger_up[mfinger_up.size()-2].prePos);
                        float diff = preDis - dis;
                        if (diff > 10) {
                            command_up = "rock";
                        }else if(diff < -10){
                            command_up = "paper";
                        }
                    }
                }
            }
            
            
            if (mfinger_down.size()>1){
                for (int i =0; i<mfinger_down.size(); i++){
                    if (touchID == mfinger_down[i].ID) {
                        mfinger_down[i].pos.set(x, y);
                        float dis =  mfinger_down.back().pos.distance(mfinger_down[mfinger_down.size()-2].pos);
                        float preDis =  mfinger_down.back().prePos.distance(mfinger_down[mfinger_down.size()-2].prePos);
                        float diff = preDis - dis;
                        if (diff > 10) {
                            command_down = "rock";
                        }else if(diff < -10){
                            command_down = "paper";
                        }
                    }
                }
            }
        }break;
    }
        
}

//-------------------------------------------------------
void crashMode::touchUp(int x, int y, int touchID){
    switch (situation) {
        
        case EMPTY_WIN:{
            
            if (mfinger_up.size()>1) {
                for (int i =0; i<mfinger_up.size(); i++){
                    if (touchID == mfinger_up[i].ID) {
                        mfinger_up[i].pos.set(x, y);
                        float dis =  mfinger_up.back().pos.distance(mfinger_up[mfinger_up.size()-2].pos);
                        float preDis =  mfinger_up.back().prePos.distance(mfinger_up[mfinger_up.size()-2].prePos);
                        float diff = preDis - dis;
                        if (diff < 30 && diff > -30) {
                            command_up = "scissors";
                        }
                    }
                }
            }
            
            if (mfinger_down.size()>1) {
                for (int i =0; i<mfinger_down.size(); i++){
                    if (touchID == mfinger_down[i].ID) {
                        mfinger_down[i].pos.set(x, y);
                        float dis =  mfinger_down.back().pos.distance(mfinger_down[mfinger_down.size()-2].pos);
                        float preDis =  mfinger_down.back().prePos.distance(mfinger_down[mfinger_down.size()-2].prePos);
                        float diff = preDis - dis;
                        if (diff < 30 && diff > -30) {
                            command_down = "scissors";
                        }
                    }
                }
            }
            
            for (int i =0; i<mfinger_up.size(); i++) {
                if (touchID == mfinger_up[i].ID) {
                    mfinger_up.erase(mfinger_up.begin()+i);
                }
            }
            
            for (int i =0; i<mfinger_down.size(); i++) {
                if (touchID == mfinger_down[i].ID) {
                    mfinger_down.erase(mfinger_down.begin()+i);
                }
            }
         
        }break;
    }

}
















