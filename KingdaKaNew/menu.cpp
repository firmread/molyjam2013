//
//  menu.cpp
//  KingdaKaNew
//
//  Created by PengCheng on 7/10/13.
//
//

#include "menu.h"
//--------------------------------------------------------------------------------
void menu::setup(){
    
    condition = MAIN_MENU;
    start = START_EMPTY;
    setupMainMenu();
    setupPauseGame();
    setupInGame();
    setupCrashMenu();
    rouns = 0;
    
   
}
//--------------------------------------------------------------------------------
void menu::setupMainMenu(){
    for (int i =0; i<MAIN_MENU_ITEMS; i++) {
        menuDots[i].set(ofGetWidth()/2, (i+1)*ofGetHeight()/(MAIN_MENU_ITEMS+1));
    }

}

//--------------------------------------------------------------------------------
void menu::setupPauseGame(){
    for (int i = 0 ; i<PAUSE_MENU_ITEMS; i++) {
        pauseMenu[i].set(ofGetWidth()/2, (i+1)*ofGetHeight()/(PAUSE_MENU_ITEMS+1));
    }
}

//--------------------------------------------------------------------------------
void menu::setupInGame(){
    menuButton[0].set(0, ofGetHeight()/2);
    menuButton[1].set(ofGetWidth(), ofGetHeight()/2);
    menuButtonSize = 150;
}

//--------------------------------------------------------------------------------
void menu::setupCrashMenu(){
    crashMenuSize = 50;
    for (int i= 0; i<CRASH_MODE_MENU; i++) {
        crashMenu[i].set(ofGetWidth()/2, (i+1)*ofGetHeight()/(CRASH_MODE_MENU+1));
    }
}

//--------------------------------------------------------------------------------
void menu::draw(){
    
    switch (condition) {
            
        case MAIN_MENU:{
            ofBackground(255);
            for (int i = 0 ; i<MAIN_MENU_ITEMS; i++) {
                if (i==1||i==2) ofSetColor(150,200);
                else ofSetColor(0,200);
                
                ofCircle(menuDots[i], 50);
            }
            
            ofSetColor(255);
            string sOne = "Crash\nMode";
            font->drawString(sOne,
                                menuDots[0].x-(int)font->stringWidth(sOne)/2,
                                menuDots[0].y); // coz have two lines
            
            string sTwo = "Mode 2";
            font->drawString(sTwo,
                                menuDots[1].x-(int)font->stringWidth(sTwo)/2,
                                menuDots[1].y+(int)font->stringHeight(sTwo)/2);
            
            string sThree = "Mode 3";
            font->drawString(sThree,
                                menuDots[2].x-(int)font->stringWidth(sThree)/2,
                                menuDots[2].y+(int)font->stringHeight(sThree)/2);
            
            string sFour = "Tutorial";
            font->drawString(sFour,
                                menuDots[3].x-(int)font->stringWidth(sFour)/2,
                                menuDots[3].y+(int)font->stringHeight(sFour)/2);
            
            string sFive = "Credits";
            font->drawString(sFive,
                                menuDots[4].x-(int)font->stringWidth(sFive)/2,
                                menuDots[4].y+(int)font->stringHeight(sFive)/2);
        
        }
            break;
            
        case CRASH_MODE:{

            for (int i=0; i<CRASH_MODE_MENU; i++) {
                ofSetColor(0,200);
                ofCircle(crashMenu[i], crashMenuSize);
            }
            
            ofSetColor(255);
            string sOne = "3";
            font->drawString(sOne,
                             crashMenu[0].x-(int)font->stringWidth(sOne)/2,
                             crashMenu[0].y+(int)font->stringHeight(sOne)/2);
            
            string sTwo = "5";
            font->drawString(sTwo,
                             crashMenu[1].x-(int)font->stringWidth(sTwo)/2,
                             crashMenu[1].y+(int)font->stringHeight(sTwo)/2);
            
            string sThree = "10";
            font->drawString(sThree,
                             crashMenu[2].x-(int)font->stringWidth(sThree)/2,
                             crashMenu[2].y+(int)font->stringHeight(sThree)/2);
            

            
        }break;
            
        case IN_GAME:{
           
            ofPushStyle();
            ofNoFill();
            ofSetLineWidth(3);
            ofSetColor(80,100);
            ofCircle(menuButton[0], menuButtonSize);
            ofCircle(menuButton[1], menuButtonSize);
            ofLine(menuButton[0].x, menuButton[0].y, menuButtonSize, ofGetHeight()/2);
            
            ofCircle(ofGetWidth()-70, ofGetHeight()/2, 65);
            ofPopStyle();
            
            ofSetColor(80,100);
            ofSetRectMode(OF_RECTMODE_CENTER);
            ofRect( ofGetWidth()-55, ofGetHeight()/2, 20, 60);
            ofRect( ofGetWidth()-85, ofGetHeight()/2, 20, 60);
            ofSetRectMode(OF_RECTMODE_CORNER);
            
        }break;
            
        case PAUSE_GAME:{

            for (int i=0; i<CRASH_MODE_MENU; i++) {
                ofSetColor(0,200);
                ofCircle(pauseMenu[i], crashMenuSize);
            }

            ofSetColor(255);
            string sOne = "Resume";
            font->drawString(sOne,
                             pauseMenu[0].x-(int)font->stringWidth(sOne)/2,
                             pauseMenu[0].y+(int)font->stringHeight(sOne)/2); // coz have two lines
            
            string sTwo = "Main Menu";
            font->drawString(sTwo,
                             pauseMenu[1].x-(int)font->stringWidth(sTwo)/2,
                             pauseMenu[1].y+(int)font->stringHeight(sTwo)/2);
            

        }break;
    }
   
}

//-------------------------------------------------------------------------------
void menu::touchDown(int x, int y){
    
   ofPoint touchPoint(x, y);
    
    switch (condition) {
        case MAIN_MENU:{
            
            if (menuDots[0].distance(touchPoint) < 50) {
                condition = CRASH_MODE;
            }
        }break;
            
        case CRASH_MODE:{
            
            if (ofDist(crashMenu[0].x, crashMenu[0].y, x, y)<crashMenuSize) {
            
                condition = IN_GAME;
                start = START_CRASH_MODE;
                rouns = 3;
                
            }else if(ofDist(crashMenu[1].x, crashMenu[1].y, x, y)<crashMenuSize){
               
                condition = IN_GAME;
                start = START_CRASH_MODE;
                rouns = 5;
                
            }else if(ofDist(crashMenu[2].x, crashMenu[2].y, x, y)<crashMenuSize){
            
                condition = IN_GAME;
                start = START_CRASH_MODE;
                rouns = 10;
            }
            
            
        }break;

        case IN_GAME:{
            if (menuButton[1].distance(touchPoint) < menuButtonSize) {
                condition = PAUSE_GAME;
            }
            
        }break;
        case PAUSE_GAME:{
            if (pauseMenu[0].distance(touchPoint) < crashMenuSize) {
                condition = IN_GAME;
            }else if (pauseMenu[1].distance(touchPoint) < crashMenuSize) {
                condition = MAIN_MENU;
            }
            
        }break;
    }
            
   
}

//-------------------------------------------------------------------------------
void menu::touchMove(int x, int y){}
void menu::touchUp(int x, int y){}
























