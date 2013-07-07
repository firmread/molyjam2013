#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	// initialize the accelerometer
	ofxAccelerometer.setup();
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
    ofEnableSmoothing();
	
    ofSetCircleResolution(120);
	//If you want a landscape oreintation 
	//iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
	
    
    particles[0].setInitialCondition(384, 24, 0, 5);
    particles[1].setInitialCondition(384, 1000, 0, -5);
    
    particles[0].angle = 180;
    
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
    
    for (int i =0; i<MAIN_MENU_ITEMS; i++) {
        menuDots[i].set(ofGetWidth()/2, (i+1)*ofGetHeight()/(MAIN_MENU_ITEMS+1));
    }
    
    bSplash = true;
    bPause = false;
    bEndGame = false;
    
    menuButton[0].set(0, ofGetHeight()/2);
    menuButton[1].set(ofGetWidth(), ofGetHeight()/2);
    menuButtonSize = 150;
    
    for (int i = 0 ; i<PAUSE_MENU_ITEMS; i++) {
        pauseMenu[i].set(ofGetWidth()/2, (i+1)*ofGetHeight()/(PAUSE_MENU_ITEMS+1));
    }
    
    for (int i = 0 ; i<END_MENU_ITEMS; i++) {
        endGameMenu[i].set(ofGetWidth()/2, (i+1)*ofGetHeight()/(END_MENU_ITEMS+1));
    }
    
    particleSpeed = ofRandom(0.08, 0.8);

    
}

//--------------------------------------------------------------

void testApp::reset(){
    
    
    particles[0].setInitialCondition(384, 24, 0, 5);
    particles[1].setInitialCondition(384, 1000, 0, -5);
    
    bPause = false;
    bEndGame = false;
    
    particleSpeed = ofRandom(0.08,0.8);
}


void testApp::resetScore(){
    
}

//--------------------------------------------------------------
void testApp::update(){

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
                
                float dis = particles[0].pos.distance(particles[1].pos);
//                cout<< dis <<endl;
                if (dis < 10) {
                    bEndGame = true;
                    endCountDownStart = ofGetSeconds();
                    endCountDown = 3;
                }
            }
            if (bEndGame) {
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
    }
        
}

//--------------------------------------------------------------
void testApp::draw(){
    
    switch (condition) {
        //------------------
        case MAIN_MENU:
        {
            ofBackground(255);
            ofSetColor(blue);
            for (int i = 0 ; i<MAIN_MENU_ITEMS; i++) {
                ofCircle(menuDots[i], 50);
            }
            
            ofSetColor(255);
            string sOne = "Mode 1";
            font.drawString(sOne,
                            menuDots[0].x-(int)font.stringWidth(sOne)/2,
                            menuDots[0].y+(int)font.stringHeight(sOne)/2);
            
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
                ofSetColor(blue);
                ofRect(0, 0, ofGetWidth(), ofGetHeight());
                
                ofSetColor(255);
                string sTitle = "Kingda\nKa";
                fontBig.drawString(sTitle,
                                   245,
                                   menuDots[1].y+(int)fontBig.stringHeight(sTitle)/2);
                
                
                string sTagline = "\" \nThe touch,\nthe grab,\nthe stroke,\nall of those things\nwe\'re going to be obsessed about.\n\"";
                font.drawString(sTagline,
                                   245,
                                   menuDots[2].y+(int)font.stringHeight(sTagline)/2);
            }
            
        }
        break;
        //------------------
        case GAME_PLAY:
        {
            
            ofBackground(86, 217, 205);
            ofSetColor(247, 255, 236);
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
            
            ofSetColor(100);
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
            
            //menu
            ofPushStyle();
            ofNoFill();
            ofSetLineWidth(2);
            ofSetColor(255,100);
            ofCircle(menuButton[0], menuButtonSize);
            ofCircle(menuButton[1], menuButtonSize);
            ofLine(menuButton[0].x, menuButton[0].y, menuButtonSize, ofGetHeight()/2);
            ofPopStyle();
            

            ofSetColor(255,200);
            ofSetRectMode(OF_RECTMODE_CENTER);
            ofRect( ofGetWidth()-70, ofGetHeight()/2-15, 80, 20);
            ofRect( ofGetWidth()-70, ofGetHeight()/2+15, 80, 20);
            ofSetRectMode(OF_RECTMODE_CORNER);
            
            if (bPause) {
                ofSetColor(255,200);
                ofRect(0, 0, ofGetWidth(), ofGetHeight());
                ofSetColor(blue);
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
                ofSetColor(255,200);
                ofRect(0, 0, ofGetWidth(), ofGetHeight());
                ofSetColor(blue);
                for (int i =0; i<END_MENU_ITEMS; i++) {
                    ofCircle(endGameMenu[i], 50);
                }
                
                ofSetColor(255);
                
                string sCountDown = ofToString(endCountDown);
                fontBig.drawString(sCountDown,
                                   endGameMenu[0].x-(int)fontBig.stringWidth(sCountDown)/2-3,
                                   endGameMenu[0].y+(int)fontBig.stringHeight(sCountDown)/2);

                string sEnd1 = "Continue";
                font.drawString(sEnd1,
                                endGameMenu[1].x-(int)font.stringWidth(sEnd1)/2,
                                endGameMenu[1].y+(int)font.stringHeight(sEnd1)/2);
                
                string sEnd2 = "Main Menu";
                font.drawString(sEnd2,
                                endGameMenu[2].x-(int)font.stringWidth(sEnd2)/2,
                                endGameMenu[2].y+(int)font.stringHeight(sEnd2)/2);
                
            }
        }
        break;
        //------------------
    }
    
        
}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
    
    ofPoint touchPoint(touch.x, touch.y);
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
                }
            }
        }
        break;
        //------------------
        case GAME_PLAY:
        {
            if (!bPause && !bEndGame) {
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
                if (endGameMenu[1].distance(touchPoint) < 50) {
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
                        }else if(diff < -10){
                            command_up = "paper";
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
                        }else if(diff < -10){
                            command_down = "paper";
                        }
                        
                    }
                }
            }
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

