#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    mSetup.setup();
    
    font.loadFont("assets/fonts/impact.ttf", 14);
    fontBig.loadFont("assets/fonts/impact.ttf", 48);
    
    mMenu.setup();
    mMenu.font = &font;
    
    charTop[0].loadImage("assets/images/gamePlay/rHamm.png");
    charTop[1].loadImage("assets/images/gamePlay/rSciss.png");
    charTop[2].loadImage("assets/images/gamePlay/rPaper.png");

    charBot[0].loadImage("assets/images/gamePlay/yHamm.png");
    charBot[1].loadImage("assets/images/gamePlay/ySciss.png");
    charBot[2].loadImage("assets/images/gamePlay/yPaper.png");
    
    currentScene = 0;
    
    //-+++++++--crash mode------++++++++++++-----------
    scenes[0] = new crashMode();
    scenes[0]->setup();
    ((crashMode*)scenes[0])->font = &font;
    ((crashMode*)scenes[0])->fontBig = &fontBig;
    for (int i = 0; i<3; i++) {
        ((crashMode*)scenes[0])->charTop[i] = &charTop[i];
        ((crashMode*)scenes[0])->charBot[i] = &charBot[i];
    }
    
}

//--------------------------------------------------------------
void testApp::reset(){

    if (mMenu.start == START_CRASH_MODE) {
        currentScene = 0;
        ((crashMode*)scenes[0])->reset();
        ((crashMode*)scenes[0])->scoreReset();
        ((crashMode*)scenes[0])->scoreSetup(mMenu.rouns);
        mMenu.start = START_EMPTY;
    }
}

//--------------------------------------------------------------
void testApp::update(){
    
    reset();
    if (mMenu.condition == IN_GAME) {
        scenes[currentScene]->update();
        if( ((crashMode*)scenes[0])->situation == GAME_END){
            mMenu.condition = GAME_OVER;
        }
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    
    if (mMenu.condition == IN_GAME) {
        scenes[currentScene]->draw();
    }
    mMenu.draw();
}



//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
    
    mMenu.touchDown(touch.x, touch.y);
    if (mMenu.condition == IN_GAME) {
        scenes[currentScene]->touchDown(touch.x, touch.y, touch.id);
    }
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
    if (mMenu.condition == IN_GAME) {
        scenes[currentScene]->touchMove(touch.x, touch.y, touch.id);
    }
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
    if (mMenu.condition == IN_GAME) {
        scenes[currentScene]->touchUp(touch.x, touch.y, touch.id);
    }
}

//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs & touch){}
void testApp::touchCancelled(ofTouchEventArgs & touch){}
void testApp::lostFocus(){}
void testApp::gotFocus(){}
void testApp::gotMemoryWarning(){}
void testApp::deviceOrientationChanged(int newOrientation){}
void testApp::exit(){}
