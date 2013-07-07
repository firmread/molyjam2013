#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	// initialize the accelerometer
	ofxAccelerometer.setup();
	ofSetVerticalSync(true);
    
	ofSetFrameRate(60);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
	
    ofSetCircleResolution(120);
	//If you want a landscape oreintation 
	//iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
    
    bSplash = true;
    particles[0].angle = 180;
    particles[0].playerNo = 0;
    particles[1].playerNo = 1;
    
    rect_up.set(0, 0, 768, 512);
    rect_down.set(0, 512, 768, 512);
    touch_num_up = 0;
    
    string myString[3];
    myString[0] = "rock";
    myString[1] = "paper";
    myString[2] = "scissors";

    command_up = myString[int(ofRandom(0, 2))];
    command_down = myString[int(ofRandom(0, 2))];
    
    condition = MAIN_MENU;
    
    font.loadFont("impact.ttf", 14);
    fontBig.loadFont("impact.ttf", 72);
    
    blue.set(86, 217, 205);
    red.set(255, 0, 0);
    yellow.set(251, 175, 24);
    
    for (int i =0; i<MAIN_MENU_ITEMS; i++) {
        menuDots[i].set(ofGetWidth()/2, (i+1)*ofGetHeight()/(MAIN_MENU_ITEMS+1));
    }
    
    
    menuButton[0].set(0, ofGetHeight()/2);
    menuButton[1].set(ofGetWidth(), ofGetHeight()/2);
    menuButtonSize = 150;
    
    for (int i = 0 ; i<PAUSE_MENU_ITEMS; i++) {
        pauseMenu[i].set(ofGetWidth()/2, (i+1)*ofGetHeight()/(PAUSE_MENU_ITEMS+1));
    }
    
    for (int i = 0 ; i<END_MENU_ITEMS; i++) {
        endGameMenu[i].set(ofGetWidth()/2, (i+1)*ofGetHeight()/(END_MENU_ITEMS+1));
    }
    
    particles[0].setupImage(0);
    particles[1].setupImage(1);
    
    rScore = yScore = 0;

    hand[0].loadImage("tutorial/Pinch.png");
    hand[1].loadImage("tutorial/Spread.png");
    hand[2].loadImage("tutorial/2x_Tap.png");
    
    //*********effect**************************
    bEffect = false;
    frameRate = 60;
    zoom = 0;
    zoomSpeed = 0.4f;
    zoomPct = 0;
    
    //*********sound**************************
    sound[0].loadSound("sound/gameStart.wav");
    sound[1].loadSound("sound/gameOver.wav");
    sound[2].loadSound("sound/touch04.wav");
    sound[3].loadSound("sound/touch04.wav");
    sound[4].loadSound("sound/touch04.wav");
    sound[5].loadSound("sound/drawGame.wav");

    sound[0].setMultiPlay(false);
    sound[1].setMultiPlay(false);
    sound[2].setMultiPlay(true);
    sound[3].setMultiPlay(true);
    sound[4].setMultiPlay(true);
    sound[5].setMultiPlay(false);

    //*********background Animation*************************
    bgAnime.setup(384,512);
}

//--------------------------------------------------------------
void testApp::reset(){
    
    
    particles[0].setInitialCondition(384, 24, 0, 5);
    particles[1].setInitialCondition(384, 1000, 0, -5);
    particles[0].size = 150;
    particles[1].size = 150;
    particles[0].faceNum = 0;
    particles[1].faceNum = 0;
//    particles[0].setInitialCondition(0, -500, 0, 5);
//    particles[1].setInitialCondition(0, 500, 0, -5);
    bPause = false;
    bEndGame = false;
    particleSpeed = ofRandom(0.2,0.8);
    bDidYouEvenPlayingMan = false;
    bRedWin = bYellowWin = bDrawGame = false;

    for (int i=0; i<6; i++) {
         sound[i].stop();
    }

    sound[0].play();
}

//--------------------------------------------------------------
void testApp::resetScore(){
    rScore = yScore = 0;
}

//--------------------------------------------------------------
void testApp::checkWhoIsWinning(){
    
    if      (particles[0].particleStance == 1){//r
        // r vs r = draw
        if      (particles[1].particleStance == 1) bDrawGame = true; //bRedWin = bYellowWin = false;
        // r vs p = lose
        else if (particles[1].particleStance == 2) bYellowWin = true; //bRedWin = false;}
        // r vs s = win
        else if (particles[1].particleStance == 3) bRedWin = true; //bYellowWin = false;}
    }
    else if (particles[0].particleStance == 2){//p
        if      (particles[1].particleStance == 1) bRedWin = true; //bYellowWin = false;}
        else if (particles[1].particleStance == 2) bDrawGame = true; //bRedWin = bYellowWin = false;
        else if (particles[1].particleStance == 3) bYellowWin = true; //bRedWin = false;}
    }
    else if (particles[0].particleStance == 3){//s
        if      (particles[1].particleStance == 1 ) bYellowWin = true; //bRedWin = false;}
        else if (particles[1].particleStance == 2 ) bRedWin = true; //bYellowWin = false;}
        else if (particles[1].particleStance == 3 ) bDrawGame = true; //bRedWin = bYellowWin = false;
    }
    
    
    if (bDrawGame) {
        if (!sound[5].getIsPlaying()) {
            sound[5].play();
        }
    }
    else if (bRedWin || bYellowWin) {
        if (!sound[1].getIsPlaying()) {
           sound[1].play(); 
        }
    }
    
}

//--------------------------------------------------------------
void testApp::update(){

    ofSoundUpdate();
    ofSetFrameRate(frameRate);
    
    switch (condition) {
        //------------------
        case MAIN_MENU:
        
            
        break;
        //------------------
        case GAME_PLAY:
        {
            if (!bPause && !bEndGame){
                for (int i =0; i<2; i++) {
                    particles[i].resetForce();
                }
                particles[0].addAttractionForce(particles[1], 1024, particleSpeed);
                particles[1].addAttractionForce(particles[0], 1024, particleSpeed);
        
                for (int i =0; i<2; i++) {
                    particles[i].addDampingForce();
                    particles[i].update();
                }
                
                dis = particles[0].pos.distance(particles[1].pos);
//              cout<< dis <<endl;
                
//              float disToSize = ofMap(dis, 0, 1000, 250, 100);
//              particles[0].size = disToSize;
//              particles[1].size = disToSize;
                
                //********crashing effect*****************************************
                if (dis < 80 && dis > 10) {
                    bEffect = true;
                    frameRate = 10;
                    particles[0].vel.y = 3;
                    particles[1].vel.y = -3;
                    checkWhoIsWinning();
                    particleSpeed = 0.08;
                    
                }
                else if (dis < 10) {
                    frameRate = 60;
                    bEndGame = true;
                    bEffect = false;
                    endCountDownStart = ofGetSeconds();
                    endCountDown = 3;
                    if (bYellowWin && bDidYouEvenPlayingMan) yScore++;
                    if (bRedWin && bDidYouEvenPlayingMan) rScore++;
                }
            }
            if (bEndGame && bDidYouEvenPlayingMan) {
                if (endCountDownStart != ofGetSeconds()) {
                    endCountDown--;
                    endCountDownStart = ofGetSeconds();
                }
                if (endCountDown<0) {
                    reset();
                }

            }
        }
        break;
        //------------------
        case TUTORIAL:
        {
            
        }
        break;
        //------------------
        case CREDITS:
        {
            
        }
        break;
        //------------------

    }
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(255);
    bgAnime.draw();
    ofPushMatrix();
    float x=0;
    float y=0;
    if (bEffect) {
        zoomPct+= zoomSpeed;
        if (zoomPct > 1) {
            zoomPct = 1;
        }else{
            x = (int)ofRandom(-10,10);
            y = (int)ofRandom(-30,30);
            ofBackground(int(ofRandom(0,70)));
        }
        
        zoom = (1-zoomPct)*zoom + zoomPct*400;
       
        if (bYellowWin) {
            particles[0].size-=10;
            particles[0].faceNum = 1;
        }else if(bRedWin){
            particles[1].size-=10;
            particles[1].faceNum = 1;
        }
        
        if (particles[1].size < 0) {
            particles[1].size = 0;
        }
        
        if (particles[0].size < 0) {
            particles[0].size = 0;
        }
        
    }else{
        zoom = 0;
        zoomPct = 0;
    }
    ofTranslate(x, y,zoom);
    camera();
    ofPopMatrix();
    
}
//--------------------------------------------------------------
void testApp::camera(){
    switch (condition) {
            //------------------
        case MAIN_MENU:
        {
            ofBackground(255);
            for (int i = 0 ; i<MAIN_MENU_ITEMS; i++) {
                if (i==1||i==2) ofSetColor(150,200);
                else ofSetColor(0,200);
                
                ofCircle(menuDots[i], 50);
            }
            
            ofSetColor(255);
            string sOne = "Crash\nMode";
            font.drawString(sOne,
                            menuDots[0].x-(int)font.stringWidth(sOne)/2,
                            menuDots[0].y); // coz have two lines
            
            string sTwo = "Mode 2";
            font.drawString(sTwo,
                            menuDots[1].x-(int)font.stringWidth(sTwo)/2,
                            menuDots[1].y+(int)font.stringHeight(sTwo)/2);
            
            string sThree = "Mode 3";
            font.drawString(sThree,
                            menuDots[2].x-(int)font.stringWidth(sThree)/2,
                            menuDots[2].y+(int)font.stringHeight(sThree)/2);
            
            string sFour = "Tutorial";
            font.drawString(sFour,
                            menuDots[3].x-(int)font.stringWidth(sFour)/2,
                            menuDots[3].y+(int)font.stringHeight(sFour)/2);
            
            string sFive = "Credits";
            font.drawString(sFive,
                            menuDots[4].x-(int)font.stringWidth(sFive)/2,
                            menuDots[4].y+(int)font.stringHeight(sFive)/2);
            
            
            if (bSplash) {
                ofSetColor(50);
                ofRect(0, 0, ofGetWidth(), ofGetHeight());
                
                ofSetColor(255);
                string sTitle = "Kingda\nKa";
                fontBig.drawString(sTitle,
                                   245,
                                   menuDots[1].y+(int)fontBig.stringHeight(sTitle)/2);
                
                
                string sTagline = "\" \nThe touch,\nthe grab,\nthe stroke,\nall of those things\nwe\'re going to be obsessed about.\n\"\n                - Peter Molydeux\n\nTap to start";
                font.drawString(sTagline,
                                245,
                                590);
                
            }
        }
            break;
            //------------------
        case GAME_PLAY:
        {
            
            //            ofPushMatrix();
            //            ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
            //            float scale = ofMap(dis, 0, 1000, 2.0, 0.5);
            //            ofScale(scale, scale);
            
            
            ofSetColor(255,255);
            //          ofSetColor(red);
            

            if (command_up == "rock") {
                particles[0].particleStance = 1;
                particles[0].draw();
              
            }
            else if(command_up == "paper"){
                particles[0].particleStance = 2;
                particles[0].draw();
            }
            else if(command_up == "scissors"){
                
                particles[0].particleStance = 3;
                particles[0].draw();
            }
            
            //            ofSetColor(yellow);
            if (command_down == "rock") {
                
                particles[1].particleStance = 1;
                particles[1].draw();
            }
            else if(command_down == "paper"){
                particles[1].particleStance = 2;
                particles[1].draw();
            }
            else if(command_down == "scissors"){
                particles[1].particleStance = 3;
                particles[1].draw();
            }
            
            
            
            //          ofPopMatrix();
            
            //menu
            ofPushStyle();
            ofNoFill();
            ofSetLineWidth(3);
            ofSetColor(80,100);
            ofCircle(menuButton[0], menuButtonSize);
            ofCircle(menuButton[1], menuButtonSize);
            ofLine(menuButton[0].x, menuButton[0].y, menuButtonSize, ofGetHeight()/2);
            
            ofCircle(ofGetWidth()-70, ofGetHeight()/2, 65);
            ofPopStyle();
            
            //score
            ofSetColor(red);
            string sRScore = ofToString(rScore);
            fontBig.drawString(sRScore,
                               30-(int)font.stringWidth(sRScore)/2,
                               ofGetHeight()/2-25-(int)font.stringHeight(sRScore)/2);
            
            
            ofSetColor(yellow);
            string sYScore = ofToString(yScore);
            fontBig.drawString(sYScore,
                               30-(int)font.stringWidth(sYScore)/2,
                               ofGetHeight()/2+80+(int)font.stringHeight(sYScore));
            
            //pauseButton
            ofSetColor(80,100);
            ofSetRectMode(OF_RECTMODE_CENTER);
            ofRect( ofGetWidth()-55, ofGetHeight()/2, 20, 60);
            ofRect( ofGetWidth()-85, ofGetHeight()/2, 20, 60);
            ofSetRectMode(OF_RECTMODE_CORNER);
            
            
            if (bPause) {
                ofSetColor(255,200);
                ofRect(0, 0, ofGetWidth(), ofGetHeight());
                ofSetColor(0, 200);
                for (int i =0 ; i<PAUSE_MENU_ITEMS; i++) {
                    ofCircle(pauseMenu[i], 50);
                }
                ofSetColor(255);
                string sPause1 = "Resume";
                font.drawString(sPause1,
                                pauseMenu[0].x-(int)font.stringWidth(sPause1)/2,
                                pauseMenu[0].y+(int)font.stringHeight(sPause1)/2);
                
                string sPause2 = "Main Menu";
                font.drawString(sPause2,
                                pauseMenu[1].x-(int)font.stringWidth(sPause2)/2,
                                pauseMenu[1].y+(int)font.stringHeight(sPause2)/2);
            }
            
            else if (bEndGame) {
                if (!bDidYouEvenPlayingMan) ofSetColor(0,200);
                else if (bRedWin)       ofSetColor(red);
                else if (bYellowWin)    ofSetColor(yellow);
                else if (bDrawGame)     ofSetColor(0, 200);
                else ofSetColor(ofColor::salmon);
                ofRect(0, 0, ofGetWidth(), ofGetHeight());
                
                for (int i =0; i<END_MENU_ITEMS; i++) {
                    ofPushStyle();
                    if (i ==1) ofSetColor(255);
                    else ofSetColor(0,200);
                    ofCircle(endGameMenu[i], 50);
                    ofPopStyle();
                }
                
                string sCountDown = ofToString(endCountDown);
                if (bDidYouEvenPlayingMan == false) sCountDown = "";
                fontBig.drawString(sCountDown,
                                   endGameMenu[1].x-(int)fontBig.stringWidth(sCountDown)/2-3,
                                   endGameMenu[1].y+(int)fontBig.stringHeight(sCountDown)/2);
                
                ofSetColor(255);
                string sWhoWin = "";
                if (!bDidYouEvenPlayingMan) sWhoWin = "No Session";
                else if (bYellowWin) sWhoWin = "Yellow Win";
                else if (bRedWin) sWhoWin = "Red Win";
                else if (bDrawGame) sWhoWin = "Draw Game";
                
                font.drawString(sWhoWin, 20, ofGetHeight() - 24);
                
                
                string sEnd1 = "Continue";
                font.drawString(sEnd1,
                                endGameMenu[0].x-(int)font.stringWidth(sEnd1)/2,
                                endGameMenu[0].y+(int)font.stringHeight(sEnd1)/2);
                
                string sEnd2 = "Main Menu";
                font.drawString(sEnd2,
                                endGameMenu[2].x-(int)font.stringWidth(sEnd2)/2,
                                endGameMenu[2].y+(int)font.stringHeight(sEnd2)/2);
                
            }
        }
        break;
        //------------------
        case TUTORIAL:
        {
            int handSize = 150;
            ofBackground(blue);
            ofSetColor(255);
            for (int i =0; i<3; i++) {
                ofPushMatrix();
                ofTranslate(ofGetWidth()/2, (ofGetHeight()*(i+1)/4)-40);
                
                int h = handSize* hand[i].width/hand[i].height;
                hand[i].draw( -handSize/2 , -h/2, handSize, h);
            }
            
            ofSetColor(0,200);
            string descript1 = "Rock\nPinch two fingers";
            font.drawString(descript1,
                            ofGetWidth()/2-(int)font.stringWidth(descript1)/2,
                            ofGetHeight()*(1)/4+(int)font.stringHeight(descript1)/2 +40);
            
            string descript2 = "Paper\nSpread two fingers";
            font.drawString(descript2,
                            ofGetWidth()/2-(int)font.stringWidth(descript2)/2,
                            ofGetHeight()*(2)/4+(int)font.stringHeight(descript2)/2 +40);
            
            string descript3 = "Scissors\nTap with two fingers";
            font.drawString(descript3,
                            ofGetWidth()/2-(int)font.stringWidth(descript3)/2,
                            ofGetHeight()*(3)/4+(int)font.stringHeight(descript3)/2 +40);
            
        }
        break;

        //------------------
        case CREDITS:
        {
            ofBackground(50);
            ofSetColor(255);
            fontBig.drawString("Kingda\nKa", 245, menuDots[0].y);
            font.drawString("A game by\n\nPaul Cheng\nFirm Read Tothong\nClovis Akira", 245, menuDots[1].y);
            font.drawString("Part of MolyJam 2013 Game Jam\n\n\" \nThe touch,\nthe grab,\nthe stroke,\nall of those things\nwe\'re going to be obsessed about.\n\"\n                - Peter Molydeux", 245, menuDots[3].y);
            
        }
        break;
        //------------------
            
    }

}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
    
    ofPoint touchPoint(touch.x, touch.y);
    bDidYouEvenPlayingMan = true;
    switch (condition)
    {
            
        //------------------
        case MAIN_MENU:
        {
            ofPoint touchPoint(touch.x, touch.y);
            
            if (bSplash){
                bSplash = false;
            }
            
            else{
                
                if (menuDots[0].distance(touchPoint) < 50) {
                    reset();
                    condition = GAME_PLAY;
                    sound[0].play();
                }
                else if (menuDots[3].distance(touchPoint) < 50){
                    condition = TUTORIAL;
                }
                else if (menuDots[4].distance(touchPoint) < 50){
                    condition = CREDITS;
                }
            }
        }
        break;
        //------------------
        case GAME_PLAY:
        {
            if (!bPause && !bEndGame && !bEffect) {
                if (rect_up.inside(touch.x, touch.y)) {
                    finger temp;
                    temp.ID = touch.id;
                    temp.district = 0;
                    temp.pos.set(touch.x, touch.y);
                    temp.prePos.set(touch.x, touch.y);
                    mfinger_up.push_back(temp);
                }
                
                if (rect_down.inside(touch.x, touch.y)) {
                    finger temp;
                    temp.ID = touch.id;
                    temp.district = 0;
                    temp.pos.set(touch.x, touch.y);
                    temp.prePos.set(touch.x, touch.y);
                    mfinger_down.push_back(temp);
                }
                

            }
            
            if (menuButton[1].distance(touchPoint)<menuButtonSize) {
                bPause = true;
            }
            
            if (bPause == true){
                if (pauseMenu[0].distance(touchPoint)<50) {
                    bPause = false;
                }
                else if (pauseMenu[1].distance(touchPoint)<50) {
                    condition = MAIN_MENU;
                    resetScore();
                }
            }
            
            if (bEndGame == true) {
                if (endGameMenu[0].distance(touchPoint) < 50) {
                    reset();
                }
                if (endGameMenu[2].distance(touchPoint) < 50) {
                    condition = MAIN_MENU;
                    resetScore();
                }
            }
        }
        break;
        //------------------
        case TUTORIAL:
        {
            condition = MAIN_MENU;
        }
        break;

        //------------------
        case CREDITS:
        {
            condition = MAIN_MENU;
        }
        break;
        //------------------

    }
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
    switch (condition) {
            
        //------------------
        case MAIN_MENU:
            
        break;
        //------------------
        case GAME_PLAY:
        {
            if (mfinger_up.size()>1){
                for (int i =0; i<mfinger_up.size(); i++){
                    if (touch.id == mfinger_up[i].ID) {
                        mfinger_up[i].pos.set(touch.x, touch.y);
                        float dis =  mfinger_up.back().pos.distance(mfinger_up[mfinger_up.size()-2].pos);
                        float preDis =  mfinger_up.back().prePos.distance(mfinger_up[mfinger_up.size()-2].prePos);
                        float diff = preDis - dis;
                        if (diff > 10) {
                            command_up = "rock";
                            sound[2].play();
                        }else if(diff < -10){
                            command_up = "paper";
                            sound[3].play();
                        }
                        
                    }
                }
            }
            
            
            if (mfinger_down.size()>1){
                for (int i =0; i<mfinger_down.size(); i++){
                    if (touch.id == mfinger_down[i].ID) {
                        mfinger_down[i].pos.set(touch.x, touch.y);
                        float dis =  mfinger_down.back().pos.distance(mfinger_down[mfinger_down.size()-2].pos);
                        float preDis =  mfinger_down.back().prePos.distance(mfinger_down[mfinger_down.size()-2].prePos);
                        float diff = preDis - dis;
                        if (diff > 10) {
                            command_down = "rock";
                            sound[2].play();
                        }else if(diff < -10){
                            command_down = "paper";
                            sound[3].play();
                        }
                        
                    }
                }
            }
        }
        break;
        //------------------
        case TUTORIAL:
        {
            
        }
        break;

        //------------------
        case CREDITS:
        {
            
        }
        break;
        //------------------

    }
       
    
    
    
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
    
    switch (condition) {
            
        //------------------
        case MAIN_MENU:
            
        break;
        //------------------
        case GAME_PLAY:{
            
            
            if (mfinger_up.size()>1) {
                for (int i =0; i<mfinger_up.size(); i++){
                    if (touch.id == mfinger_up[i].ID) {
                        mfinger_up[i].pos.set(touch.x, touch.y);
                        float dis =  mfinger_up.back().pos.distance(mfinger_up[mfinger_up.size()-2].pos);
                        float preDis =  mfinger_up.back().prePos.distance(mfinger_up[mfinger_up.size()-2].prePos);
                        float diff = preDis - dis;
                        if (diff < 30 && diff > -30) {
                            command_up = "scissors";
                            sound[4].play();
                        }
                    }
                }
            }
            
            if (mfinger_down.size()>1) {
                for (int i =0; i<mfinger_down.size(); i++){
                    if (touch.id == mfinger_down[i].ID) {
                        mfinger_down[i].pos.set(touch.x, touch.y);
                        float dis =  mfinger_down.back().pos.distance(mfinger_down[mfinger_down.size()-2].pos);
                        float preDis =  mfinger_down.back().prePos.distance(mfinger_down[mfinger_down.size()-2].prePos);
                        float diff = preDis - dis;
                        if (diff < 30 && diff > -30) {
                            command_down = "scissors";
                            sound[4].play();
                        }
                    }
                }
            }
            
            
            
            for (int i =0; i<mfinger_up.size(); i++) {
                if (touch.id == mfinger_up[i].ID) {
                    mfinger_up.erase(mfinger_up.begin()+i);
                }
            }
            
            for (int i =0; i<mfinger_down.size(); i++) {
                if (touch.id == mfinger_down[i].ID) {
                    mfinger_down.erase(mfinger_down.begin()+i);
                }
            }
        }
            
        break;
        //------------------
        case TUTORIAL:
        {
            
        }
        break;

        //------------------
        case CREDITS:
        {
            
        }
        break;
        //------------------

    }
    
    
    
    
}

//--------------------------------------------------------------
//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs & touch){}
void testApp::touchCancelled(ofTouchEventArgs & touch){}
void testApp::lostFocus(){}
void testApp::gotFocus(){}
void testApp::gotMemoryWarning(){}
void testApp::deviceOrientationChanged(int newOrientation){}
void testApp::exit(){}

