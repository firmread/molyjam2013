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
    
    touch_num_up = 0;
}

//--------------------------------------------------------------
void testApp::update(){

    for (int i =0; i<2; i++) {
        particles[i].resetForce();
    }
    
   
    particles[0].addAttractionForce(particles[1], 1024, 0.05);
    particles[1].addAttractionForce(particles[0], 1024, 0.05);

    
    for (int i =0; i<2; i++) {
        particles[i].addDampingForce();
        particles[i].update();
    }
    
    
   
    
//cout<<"touch_num_up:  "<<touch_num_up<<"  fingers Number:  "<<mfinger_up.size()<<endl;
}

//--------------------------------------------------------------
void testApp::draw(){
    
    
    ofSetColor(247, 255, 236);
    ofCircle(particles[0].pos.x,particles[0].pos.y, 10);
    ofCircle(particles[1].pos.x,particles[1].pos.y, 10);
    
}



//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
    
    
    if (rect_up.inside(touch.x, touch.y)) {
        finger temp;
        temp.ID = touch.id;
        temp.district = 0;
        temp.pos.set(touch.x, touch.y);
        temp.prePos.set(touch.x, touch.y);
        mfinger_up.push_back(temp);
    
    }
    
    
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
    
    for (int i =0; i<mfinger_up.size(); i++){
        if (touch.id == mfinger_up[i].ID) {
            mfinger_up[i].pos.set(touch.x, touch.y);
        }
    }
   
    if (mfinger_up.size()>1) {
            float dis =  mfinger_up.back().pos.distance(mfinger_up[mfinger_up.size()-2].pos);
            float preDis =  mfinger_up.back().prePos.distance(mfinger_up[mfinger_up.size()-2].prePos);
            float diff = preDis - dis;
            if (diff > 10) {
                 cout<<"rock_up"<<endl;
            }
    }
  
    for (int i =0; i<mfinger_up.size(); i++){
        if (touch.id == mfinger_up[i].ID) {
            mfinger_up[i].prePos.set(touch.x, touch.y);
        }
    }
    
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){

    
    for (int i =0; i<mfinger_up.size(); i++) {
        if (mfinger_up[i].district == 0 && touch.id == mfinger_up[i].ID) {
                mfinger_up.erase(mfinger_up.begin()+i);
        }
    }

    
    
}

//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void testApp::touchCancelled(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void testApp::lostFocus(){

}

//--------------------------------------------------------------
void testApp::gotFocus(){

}

//--------------------------------------------------------------
void testApp::gotMemoryWarning(){

}

//--------------------------------------------------------------
void testApp::deviceOrientationChanged(int newOrientation){

}

//--------------------------------------------------------------
void testApp::exit(){
    
}

