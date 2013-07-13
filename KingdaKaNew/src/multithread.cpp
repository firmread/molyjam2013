//
//  multithread.cpp
//  KingdaKaNew
//
//  Created by PengCheng on 7/12/13.
//
//

#include "multithread.h"

//-------------------------------------------------------
void multithread::setup(){
    amount = 3;
    reset();
    //setup background lanes
    for (int i =0; i<amount; i++) {
        ofRectangle rect;
        rect.setFromCenter((ofGetWidth()/amount)*i+(ofGetWidth()/amount/2), ofGetHeight()/4,
                           ofGetWidth()/amount, ofGetHeight()/2);
        rLane.push_back(rect);
        rect.setFromCenter((ofGetWidth()/amount)*i+(ofGetWidth()/amount/2), ofGetHeight()/4*3,
                           ofGetWidth()/amount, ofGetHeight()/2);
        yLane.push_back(rect);
        
    }
};

//-------------------------------------------------------
void multithread::update(){
    
    determineGesture();
    
    if (!bEffect) {
       
        
        for (int i = 0; i<amount; i++) {
            
            rPos[i].resetForce();
            yPos[i].resetForce();
            rPos[i].addForce(0, 0.1);
            yPos[i].addForce(0, -0.1);
        }
        
        for (int i = 0; i<amount; i++) {
            
            rPos[i].addAttractionForce(yPos[i], 1024, speed[i]);
            yPos[i].addAttractionForce(rPos[i], 1024, speed[i]);
        }
        
        for (int i = 0; i<amount; i++) {
            
            if (bCrash[i]) {
                rPos[i].addDampingForce();
                rPos[i].update();
                
                yPos[i].addDampingForce();
                yPos[i].update();
            }
           
        }

    }
        
    checkWhoIsWinning();
    crash();
};

//-------------------------------------------------------
void multithread::draw(){
  
    ofPushMatrix();
    ofTranslate(focus);
    content(0);
    ofPopMatrix();
    
};

//-------------------------------------------------------
void multithread::reset(){
    rPos.clear();
    yPos.clear();
    rNum.clear();
    yNum.clear();
    
    //setup particles
    for (int i =0; i<amount; i++) {
        particle temp;
        temp.setInitialCondition((ofGetWidth()/amount)*i+(ofGetWidth()/amount/2), 0, 0, 2);
        rPos.push_back(temp);
        temp.setInitialCondition((ofGetWidth()/amount)*i+(ofGetWidth()/amount/2), ofGetHeight(), 0, -2);
        yPos.push_back(temp);
    }
    
    for (int i =0; i<amount; i++) {
        int num;
        num = (int)ofRandom(0,2);
        rNum.push_back(num);
        num = (int)ofRandom(0,2);
        yNum.push_back(num);
    }
    
    for (int i =0; i<amount; i++) {
        float tempSpeed;
        tempSpeed = ofRandom(0.1,0.4);
        speed[i] = tempSpeed;
    }
    
    for (int i =0; i<amount; i++) {
        winStatus[i] = "noWinner";
    }
    
    for (int i =0; i<amount; i++) {
        bCrash[i] = true;
        rSize[i].set(80,80);
        ySize[i].set(80,80);
        crashStep[i] = 0;
    }
    
    focus.set(0, 0, 0);
    bEffect = false;
    
}

//-------------------------------------------------------
void multithread::content(int num){

    if (num == 0) {
        for (int i =0; i<amount; i++) {
            ofSetColor(255, 0, 0, 50+i*30);
            ofRect(rLane[i]);
            ofSetColor(251, 175, 24, 50+i*30);
            ofRect(yLane[i]);
        }
        
        for (int i =0; i<amount; i++) {
            ofSetColor(255);
            ofPushMatrix();
            ofTranslate(rPos[i].pos.x,rPos[i].pos.y);
            ofRotateZ(180);
            ofSetRectMode(OF_RECTMODE_CENTER);
            rHand[rNum[i]]->draw(0,0,rSize[i].x,rSize[i].y);
            ofSetRectMode(OF_RECTMODE_CORNER);
            ofPopMatrix();
            
            ofPushMatrix();
            ofTranslate(yPos[i].pos.x,yPos[i].pos.y);
            ofSetRectMode(OF_RECTMODE_CENTER);
            yHand[yNum[i]]->draw(0,0,ySize[i].x,ySize[i].y);
            ofSetRectMode(OF_RECTMODE_CORNER);
            ofPopMatrix();
        }
        
        if (bCrashEffect) {
            carshEffect();
        }
    }

}

//-------------------------------------------------------
void multithread::checkWhoIsWinning(){
    
    for (int i=0; i<amount; i++) {
        if (rPos[i].pos.distance(yPos[i].pos)<50 && bCrash[i]) {
            bCrash[i] = false;
            bEffect = true;
            if (rNum[i]==0) {
                
                if(yNum[i]==1){
                    winStatus[i] = "redWin";
                }else if(yNum[i]==2){
                    winStatus[i] = "yellowWin";
                }else{
                    winStatus[i] = "draw";
                }
            }else if (rNum[i]==1) {
                
                if (yNum[i]==0) {
                    winStatus[i] = "yellowWin";
                }else if(yNum[i]==2){
                    winStatus[i] = "redWin";
                }else{
                    winStatus[i] = "draw";
                }
                
            }else if (rNum[i]==2) {
                
                if (yNum[i]==0) {
                    winStatus[i] = "redWin";
                }else if(yNum[i]==1){
                    winStatus[i] = "yellowWin";
                }else{
                    winStatus[i] = "draw";
                }
            }
            
        }
    }
    

}

//-------------------------------------------------------
void multithread::crash(){

    float speed = 0.12f;
    
    if (bEffect) {
        focus.x = ofRandom(10);
        focus.y = ofRandom(10);
    }else{
        focus.x = 0;
        focus.y = 0;
    }
    
    for (int i =0; i<amount; i++) {
        if (!bCrash[i]) {
            if (winStatus[i] == "redWin") {
                if (crashStep[i] == 0) {
                    pct+=speed;
                    if (pct>1) {
                        pct =1;
                        crashStep[i] = 1;
                        carshEffectSetup(yPos[i].pos, 1);
                        bCrashEffect = true;
                    }
                    rSize[i].x = pct*120;
                    rSize[i].y = pct*120;
                    ySize[i].x = pct*120;
                    ySize[i].y = pct*120;
                    
                }else if(crashStep[i] == 1){
                    
                    pct-=speed;
                    if (pct<0) {
                        pct =0;
                        crashStep[i] = 2;
                    }
                    
                    ySize[i].x = pct*120;
                    ySize[i].y = pct*120;
                }
               
            }
            else if(winStatus[i] == "yellowWin"){
                if (crashStep[i] == 0) {
                    pct+=speed;
                    if (pct>1) {
                        pct =1;
                        crashStep[i] = 1;
                        carshEffectSetup(rPos[i].pos, 0);
                        bCrashEffect = true;
                    }
                    rSize[i].x = pct*120;
                    rSize[i].y = pct*120;
                    ySize[i].x = pct*120;
                    ySize[i].y = pct*120;
                    
                }else if(crashStep[i] == 1){
                    
                    pct-=speed;
                    if (pct<0) {
                        pct =0;
                        crashStep[i] = 2;
                    }
                    
                    rSize[i].x = pct*120;
                    rSize[i].y = pct*120;
                }
            }else if(winStatus[i] == "draw"){
                if (crashStep[i] == 0) {
                    pct+=speed;
                    if (pct>1) {
                        pct =1;
                        crashStep[i] = 1;
                    }
                    rSize[i].x = pct*120;
                    rSize[i].y = pct*120;
                    ySize[i].x = pct*120;
                    ySize[i].y = pct*120;
                    
                }else if(crashStep[i] == 1){
                    
                    pct-=speed;
                    if (pct<0) {
                        pct =0;
                        bEffect = false;
                        crashStep[i] = 2;
                    }
                    
                    rSize[i].x = pct*120;
                    rSize[i].y = pct*120;
                    ySize[i].x = pct*120;
                    ySize[i].y = pct*120;

                }
            }
        }
    }
    
}

//-------------------------------------------------------
void multithread::carshEffectSetup(ofPoint pos, int num){
    
    for (int i=0; i<30; i++) {
        smallShape shape;
        shape.pct = 0;
        shape.org.set(pos);
        shape.pos.set(pos);
        
        float radius = ofRandom(200);
        float angle = ofRandom(360);
        float x = pos.x + radius * cos(angle*DEG_TO_RAD);
        float y = pos.y + radius * -sin(angle*DEG_TO_RAD);
        shape.toPos.set(x, y);
        
        if (num == 0) shape.color.set(255, 0, 0);
        else if(num == 1) shape.color.set(251, 175, 24);

        shape.bFinish = false;
        
        smallShapes.push_back(shape);
    }
    
}

//-------------------------------------------------------
void multithread::carshEffect(){
    
    
    for (int i=0; i<30; i++) {
        float speed = 0.1f;
        smallShapes[i].pct +=speed;
        if (smallShapes[i].pct>1) {
            smallShapes[i].pct=1;
            smallShapes[i].bFinish  = true;
        }
        smallShapes[i].pos = (1-pct)*smallShapes[i].org + pct*smallShapes[i].toPos;
        
        ofSetColor(smallShapes[i].color);
        ofNoFill();
        ofCircle(smallShapes[i].pos, 10);
        ofCircle(smallShapes[i].pos, 5);
        ofFill();
    }
    
    int counter =0;
    for (int i=0; i<30; i++) {
        if (smallShapes[i].bFinish  == true) {
            counter ++;
        }
    }
    
    if (counter == 30) {
        bCrashEffect = false;
        bEffect = false;
        smallShapes.clear();
    }
    
    
}
    
//-------------------------------------------------------
void multithread::determineGesture(){
    for (int i=0; i<amount; i++) {
        if (rCommand[i] == "rock") {
            rNum[i] = 0;
        }else if(rCommand[i] == "scissors"){
            rNum[i] = 1;
        }else if(rCommand[i] == "paper"){
            rNum[i] = 2;
        }
        
        if (yCommand[i] == "rock") {
            yNum[i] = 0;
        }else if(yCommand[i] == "scissors"){
            yNum[i] = 1;
        }else if(yCommand[i] == "paper"){
            yNum[i] = 2;
        }
    }
    
}

//-------------------------------------------------------
void multithread::touchDown(int x, int y, int touchID){
    for (int i =0; i<amount; i++) {
        finger temp;
        temp.ID = touchID;
        temp.pos.set(x, y);
        temp.prePos.set(x, y);
        
        if (i==0 && bCrash[i]) {
            if (rLane[i].inside(x, y)) {
                rfinger_0.push_back(temp);
            }
            
            if (yLane[i].inside(x, y)) {
                yfinger_0.push_back(temp);
            }
        }
        
       else if (i==1 && bCrash[i]) {
            if (rLane[i].inside(x, y)) {
                rfinger_1.push_back(temp);
            }
            
            if (yLane[i].inside(x, y)) {
                yfinger_1.push_back(temp);
            }
        }
        
        else if (i==2 && bCrash[i]) {
            if (rLane[i].inside(x, y)) {
                rfinger_2.push_back(temp);
            }
            
            if (yLane[i].inside(x, y)) {
                yfinger_2.push_back(temp);
            }
        }
    }
        
    
};

//-------------------------------------------------------
void multithread::touchMove(int x, int y, int touchID){
    
    for (int i =0; i<amount; i++) {
        if (i==0 && bCrash[i]) {
            
            if (rfinger_0.size()>1){
                for (int i =0; i<rfinger_0.size(); i++){
                    if (touchID == rfinger_0[i].ID) {
                        rfinger_0[i].pos.set(x, y);
                        float dis =  rfinger_0.back().pos.distance(rfinger_0[rfinger_0.size()-2].pos);
                        float preDis =  rfinger_0.back().prePos.distance(rfinger_0[rfinger_0.size()-2].prePos);
                        float diff = preDis - dis;
                        if (diff > 10) {
                            rCommand[0] = "rock";
                        }else if(diff < -10){
                            rCommand[0] = "paper";
                        }
                    }
                }
            }
            else if (yfinger_0.size()>1){
                for (int i =0; i<yfinger_0.size(); i++){
                    if (touchID == yfinger_0[i].ID) {
                        yfinger_0[i].pos.set(x, y);
                        float dis =  yfinger_0.back().pos.distance(yfinger_0[yfinger_0.size()-2].pos);
                        float preDis =  yfinger_0.back().prePos.distance(yfinger_0[yfinger_0.size()-2].prePos);
                        float diff = preDis - dis;
                        if (diff > 10) {
                            yCommand[0] = "rock";
                        }else if(diff < -10){
                            yCommand[0] = "paper";
                        }
                    }
                }
            }
        }
        else if (i==1 && bCrash[i]) {
            
            if (rfinger_1.size()>1){
                for (int i =0; i<rfinger_1.size(); i++){
                    if (touchID == rfinger_1[i].ID) {
                        rfinger_1[i].pos.set(x, y);
                        float dis =  rfinger_1.back().pos.distance(rfinger_1[rfinger_1.size()-2].pos);
                        float preDis =  rfinger_1.back().prePos.distance(rfinger_1[rfinger_1.size()-2].prePos);
                        float diff = preDis - dis;
                        if (diff > 10) {
                            rCommand[1] = "rock";
                        }else if(diff < -10){
                            rCommand[1] = "paper";
                        }
                    }
                }
            }
            else if (yfinger_1.size()>1){
                for (int i =0; i<yfinger_1.size(); i++){
                    if (touchID == yfinger_1[i].ID) {
                        yfinger_1[i].pos.set(x, y);
                        float dis =  yfinger_1.back().pos.distance(yfinger_1[yfinger_1.size()-2].pos);
                        float preDis =  yfinger_1.back().prePos.distance(yfinger_1[yfinger_1.size()-2].prePos);
                        float diff = preDis - dis;
                        if (diff > 10) {
                            yCommand[1] = "rock";
                        }else if(diff < -10){
                            yCommand[1] = "paper";
                        }
                    }
                }
            }
        }
        else if (i==2 && bCrash[i]) {
            
            if (rfinger_2.size()>1){
                for (int i =0; i<rfinger_2.size(); i++){
                    if (touchID == rfinger_2[i].ID) {
                        rfinger_2[i].pos.set(x, y);
                        float dis =  rfinger_2.back().pos.distance(rfinger_2[rfinger_2.size()-2].pos);
                        float preDis =  rfinger_2.back().prePos.distance(rfinger_2[rfinger_2.size()-2].prePos);
                        float diff = preDis - dis;
                        if (diff > 10) {
                            rCommand[2] = "rock";
                        }else if(diff < -10){
                            rCommand[2] = "paper";
                        }
                    }
                }
            }
            else if (yfinger_2.size()>1){
                for (int i =0; i<yfinger_2.size(); i++){
                    if (touchID == yfinger_2[i].ID) {
                        yfinger_2[i].pos.set(x, y);
                        float dis =  yfinger_2.back().pos.distance(yfinger_2[yfinger_2.size()-2].pos);
                        float preDis =  yfinger_2.back().prePos.distance(yfinger_2[yfinger_2.size()-2].prePos);
                        float diff = preDis - dis;
                        if (diff > 10) {
                            yCommand[2] = "rock";
                        }else if(diff < -10){
                            yCommand[2] = "paper";
                        }
                    }
                }
            }
        }
       
        
        
        
    }
    
    
    
};

//-------------------------------------------------------
void multithread::touchUp(int x, int y, int touchID){
    
    
    for (int i=0; i<amount; i++) {
        
        if (i==0 && bCrash[i]) {
            if (rfinger_0.size()>1) {
                for (int i =0; i<rfinger_0.size(); i++){
                    if (touchID == rfinger_0[i].ID) {
                        rfinger_0[i].pos.set(x, y);
                        float dis =  rfinger_0.back().pos.distance(rfinger_0[rfinger_0.size()-2].pos);
                        float preDis =  rfinger_0.back().prePos.distance(rfinger_0[rfinger_0.size()-2].prePos);
                        float diff = preDis - dis;
                        if (diff < 30 && diff > -30) {
                            rCommand[0] = "scissors";
                        }
                    }
                }
            }
            
            if (yfinger_0.size()>1) {
                for (int i =0; i<yfinger_0.size(); i++){
                    if (touchID == yfinger_0[i].ID) {
                        yfinger_0[i].pos.set(x, y);
                        float dis =  yfinger_0.back().pos.distance(yfinger_0[yfinger_0.size()-2].pos);
                        float preDis =  yfinger_0.back().prePos.distance(yfinger_0[yfinger_0.size()-2].prePos);
                        float diff = preDis - dis;
                        if (diff < 30 && diff > -30) {
                            yCommand[0] = "scissors";
                        }
                    }
                }
            }
            
            for (int i =0; i<rfinger_0.size(); i++) {
                if (touchID == rfinger_0[i].ID) {
                    rfinger_0.erase(rfinger_0.begin()+i);
                }
            }
            
            for (int i =0; i<yfinger_0.size(); i++) {
                if (touchID == yfinger_0[i].ID) {
                    yfinger_0.erase(yfinger_0.begin()+i);
                }
            }
            
        }
        
        else if (i==1 && bCrash[i]) {
            if (rfinger_1.size()>1) {
                for (int i =0; i<rfinger_1.size(); i++){
                    if (touchID == rfinger_1[i].ID) {
                        rfinger_1[i].pos.set(x, y);
                        float dis =  rfinger_1.back().pos.distance(rfinger_1[rfinger_1.size()-2].pos);
                        float preDis =  rfinger_1.back().prePos.distance(rfinger_1[rfinger_1.size()-2].prePos);
                        float diff = preDis - dis;
                        if (diff < 30 && diff > -30) {
                            rCommand[1] = "scissors";
                        }
                    }
                }
            }
            
            if (yfinger_1.size()>1) {
                for (int i =0; i<yfinger_1.size(); i++){
                    if (touchID == yfinger_1[i].ID) {
                        yfinger_1[i].pos.set(x, y);
                        float dis =  yfinger_1.back().pos.distance(yfinger_1[yfinger_1.size()-2].pos);
                        float preDis =  yfinger_1.back().prePos.distance(yfinger_1[yfinger_1.size()-2].prePos);
                        float diff = preDis - dis;
                        if (diff < 30 && diff > -30) {
                            yCommand[1] = "scissors";
                        }
                    }
                }
            }
            
            for (int i =0; i<rfinger_1.size(); i++) {
                if (touchID == rfinger_1[i].ID) {
                    rfinger_1.erase(rfinger_1.begin()+i);
                }
            }
            
            for (int i =0; i<yfinger_1.size(); i++) {
                if (touchID == yfinger_1[i].ID) {
                    yfinger_1.erase(yfinger_1.begin()+i);
                }
            }
            
        }
        
        else if (i==2 && bCrash[i]) {
            if (rfinger_2.size()>1) {
                for (int i =0; i<rfinger_2.size(); i++){
                    if (touchID == rfinger_2[i].ID) {
                        rfinger_2[i].pos.set(x, y);
                        float dis =  rfinger_2.back().pos.distance(rfinger_2[rfinger_2.size()-2].pos);
                        float preDis =  rfinger_2.back().prePos.distance(rfinger_2[rfinger_2.size()-2].prePos);
                        float diff = preDis - dis;
                        if (diff < 30 && diff > -30) {
                            rCommand[2] = "scissors";
                        }
                    }
                }
            }
            
            if (yfinger_2.size()>1) {
                for (int i =0; i<yfinger_2.size(); i++){
                    if (touchID == yfinger_2[i].ID) {
                        yfinger_2[i].pos.set(x, y);
                        float dis =  yfinger_2.back().pos.distance(yfinger_2[yfinger_2.size()-2].pos);
                        float preDis =  yfinger_2.back().prePos.distance(yfinger_2[yfinger_2.size()-2].prePos);
                        float diff = preDis - dis;
                        if (diff < 30 && diff > -30) {
                            yCommand[2] = "scissors";
                        }
                    }
                }
            }
            
            for (int i =0; i<rfinger_2.size(); i++) {
                if (touchID == rfinger_2[i].ID) {
                    rfinger_2.erase(rfinger_2.begin()+i);
                }
            }
            
            for (int i =0; i<yfinger_2.size(); i++) {
                if (touchID == yfinger_2[i].ID) {
                    yfinger_2.erase(yfinger_2.begin()+i);
                }
            }
        }
    }
            
};






