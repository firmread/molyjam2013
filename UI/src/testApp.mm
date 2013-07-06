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
    
    blue.set(86, 217, 205);
    
    int spacing = ofGetHeight()/6;
    for (int i =0; i<5; i++) {
        menuDots[i].set(ofGetWidth()/2, (i+1)*spacing);
    }
    
    ofBackground(255);
    splash = true;
}

//--------------------------------------------------------------
void testApp::update(){
    
    
   
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofSetColor(blue);
    for (int i = 0 ; i<5; i++) {
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
    
    
    if (splash) {
        ofSetColor(blue);
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
        
        ofSetColor(255);
        string sTitle = "Kingda Ka";
        fontBig.drawString(sTitle,
                        menuDots[2].x-(int)fontBig.stringWidth(sTitle)/2,
                        menuDots[2].y+(int)fontBig.stringHeight(sTitle)/2);
    }


}
//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
    ofPoint touchPoint(touch.x, touch.y);
    
    if (splash){
        splash = false;
    }
    
    else{
        for (int i = 0 ; i<5; i++) {
            if (menuDots[i].distance(touchPoint) < 50) {
                bMenu[i] = true;
                cout << "touch on " + ofToString(i) << endl;
            }
            else {
                bMenu[i] = false;
            }
        }
    }
    
    
    
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
    
    
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){


    
    
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

