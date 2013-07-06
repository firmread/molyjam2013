#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	// initialize the accelerometer
	ofxAccelerometer.setup();
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	
	//If you want a landscape oreintation 
	//iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
    
    pages.push_back(new menu);          //0
    pages.push_back(new gameplay1);     //1
    
    
    for (int i = 0; i < pages.size(); i++){
        pages[i]->setup();
        pages[i]->allocateFbo();
    }
	
}

//--------------------------------------------------------------
void testApp::changePage (int newPage){
    
    whichPage = newPage;
    
    if (prevWhichPage != whichPage){
        
        prevPage = pages[prevWhichPage];
        pageChangeTime = ofGetElapsedTimef();
        bInPageChange = true;
        
        pages[whichPage]->reset();
    }
    
    prevWhichPage = whichPage;
}
//--------------------------------------------------------------
void testApp::update(){
    
    pages[whichPage]->update();
    
    prevWhichPage = whichPage;
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    
    if (bInPageChange == true){
        
        float elapsedTime = ofGetElapsedTimef() - pageChangeTime;
        if (elapsedTime > 0.5){
            bInPageChange = false;
        }
        
        float pct = elapsedTime / 0.5;
        if (pct  > 1) pct = 1;
        
        pct = powf(pct, 0.8);
        
        
        pages[whichPage]->drawFboStart();
        pages[whichPage]->draw();
        pages[whichPage]->drawFboEnd();
        
            
        ofSetColor(255,255,255,255 * (pct));
//        ofSetColor(255,255,255,255);
        pages[whichPage]->drawFboDraw();
        
        
        prevPage->drawFboStart();
        prevPage->draw();
        prevPage->drawFboEnd();
        ofSetColor(255,255,255,255 * (1-pct));
        prevPage->drawFboDraw();
        
        
    } else {
        
        
        pages[whichPage]->drawFboStart();
        pages[whichPage]->draw();
        pages[whichPage]->drawFboEnd();
        ofSetColor(255,255,255,255);
        pages[whichPage]->drawFboDraw();
        
    }
    

    
}



//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
    

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

