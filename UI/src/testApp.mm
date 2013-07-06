#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	// initialize the accelerometer
	ofxAccelerometer.setup();
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
    
    ofSetCircleResolution(60);
	
	//If you want a landscape oreintation 
	//iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
	
    font.loadFont("impact.ttf", 14);
    fontBig.loadFont("impact.ttf", 72);
    
    whichPage = 0;
    
    pages.push_back(new menu());          //0
    
    for (int i =0 ; i<pages.size(); i++) {
        pages[i]->setup();
    }
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    pages[whichPage]->update();
   
    
}

//--------------------------------------------------------------
void testApp::draw(){
    pages[whichPage]->draw();


}
//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){

    pages[whichPage]->touchDown(touch);
    
    
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
    
    pages[whichPage]->touchMoved(touch);
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){

    pages[whichPage]->touchUp(touch);
    
    
}

//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs & touch){
    pages[whichPage]->touchDoubleTap(touch);
}

//--------------------------------------------------------------
void testApp::touchCancelled(ofTouchEventArgs & touch){
    pages[whichPage]->touchCancelled(touch);
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

