#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	// initialize the accelerometer
	ofxAccelerometer.setup();
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	
	//If you want a landscape oreintation 
	//iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
	
    ofBackground(86, 217, 205);
    
    particles[0].setInitialCondition(384, 24, 0, 5);
    particles[1].setInitialCondition(384, 1000, 0, -5);
    
    rect_up.set(0, 0, 768, 512);
    rect_down.set(0, 512, 768, 512);
    button_1.setFromCenter(384, 700, 300, 70);
    button_2.setFromCenter(384, 800, 300, 70);
    touch_num_up = 0;
    
    string myString[3];
    myString[0] = "rock";
    myString[1] = "paper";
    myString[2] = "scissors";

    command_up = myString[int(ofRandom(0, 2))];
    command_down = myString[int(ofRandom(0, 2))];
    
    condition = MAIN_MEUN;
}

//--------------------------------------------------------------
void testApp::update(){

    switch (condition) {
        case MAIN_MEUN:
            
            
        
            
            break;
            
        case GAME_PLAY:{
            
            for (int i =0; i<2; i++) {
                particles[i].resetForce();
            }
            particles[0].addAttractionForce(particles[1], 1024, 0.08);
            particles[1].addAttractionForce(particles[0], 1024, 0.08);
    
            for (int i =0; i<2; i++) {
                particles[i].addDampingForce();
                particles[i].update();
            }
            
            float dis = particles[0].pos.distance(particles[1].pos);
            cout<<dis<<endl;
            if (dis < 10) {
                cout<<"game over"<<endl;
            }
        }
            
            break;
    }
        
}

//--------------------------------------------------------------
void testApp::draw(){
    
    switch (condition) {
        case MAIN_MEUN:
            ofSetColor(255, 255, 255);
            ofRect(button_1);
            ofRect(button_2);
            break;
            
        case GAME_PLAY:{
            ofSetColor(247, 255, 236);
            if (command_up == "rock") {
                ofCircle(particles[0].pos.x,particles[0].pos.y, 30);
            }
            else if(command_up == "paper"){
                ofSetRectMode(OF_RECTMODE_CENTER);
                ofRect(particles[0].pos.x, particles[0].pos.y, 60, 60);
            }
            else if(command_up == "scissors"){
                ofTriangle(particles[0].pos.x-60, particles[0].pos.y, particles[0].pos.x+60, particles[0].pos.y, particles[0].pos.x, particles[0].pos.y+60);
            }
            
            if (command_down == "rock") {
                ofCircle(particles[1].pos.x,particles[1].pos.y, 30);
            }
            else if(command_down == "paper"){
                ofSetRectMode(OF_RECTMODE_CENTER);
                ofRect(particles[1].pos.x, particles[1].pos.y, 60, 60);
            }
            else if(command_down == "scissors"){
                ofTriangle(particles[1].pos.x-60, particles[1].pos.y, particles[1].pos.x+60, particles[1].pos.y, particles[1].pos.x, particles[1].pos.y-60);
            }

        }
            
            break;
    }
    
        
}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
    
    switch (condition) {
        case MAIN_MEUN:
            
            break;
            
        case GAME_PLAY:{
            
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
            
            break;
    }
   
    
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
    switch (condition) {
        case MAIN_MEUN:
            
            break;
            
        case GAME_PLAY:{
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
    }
       
    
    
    
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
    
    switch (condition) {
        case MAIN_MEUN:
            
            if (touch.numTouches == 0) {
                if (button_1.inside(touch.x, touch.y)) {
                    condition = GAME_PLAY;
                }
            }
            break;
            
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

