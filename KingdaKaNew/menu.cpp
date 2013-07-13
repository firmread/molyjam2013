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
    setupGameEnd();
    setupMultithreadMenu();
    rouns = 0;
    whoIsWinner = -1;
}

//--------------------------------------------------------------------------------
void menu::setupMainMenu(){
    for (int i =0; i<MAIN_MENU_ITEMS; i++) {
        menuDots[i].set(ofGetWidth()/2, (i+1)*ofGetHeight()/(MAIN_MENU_ITEMS+1));
    }

}

//--------------------------------------------------------------------------------
void menu::setupPauseGame(){
    pauseMenuSize = 50;
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
void menu::setupGameEnd(){
    gameEndMenuSize = 50;
    for (int i = 0 ; i<GAME_END_MENU; i++) {
        gameEndMenu[i].set(ofGetWidth()/2, (i+1)*ofGetHeight()/(GAME_END_MENU+1));
    }
}

//--------------------------------------------------------------------------------
void menu::setupCrashMenu(){
    crashMenuSize = 50;
    for (int i= 0; i<CRASH_MODE_MENU; i++) {
        crashMenu[i].set(ofGetWidth()/2, (i+1)*ofGetHeight()/(CRASH_MODE_MENU+1));
    }
}
//--------------------------------------------------------------------------------
void menu::setupMultithreadMenu(){

    MultithreadMenuSize = 50;
    for (int i= 0; i<MULTITHREAD_MODE_MENU; i++) {
        MultithreadMenu[i].set(ofGetWidth()/2, (i+1)*ofGetHeight()/(MULTITHREAD_MODE_MENU+1));
    }
}
//--------------------------------------------------------------------------------
void menu::draw(){
    
    switch (condition) {
            
        case MAIN_MENU:{
            ofBackground(255);
            for (int i = 0 ; i<MAIN_MENU_ITEMS; i++) {
                if (i==2) ofSetColor(150,200);
                else ofSetColor(0,200);
                
                ofCircle(menuDots[i], 50);
            }
            
            ofSetColor(255);
            string sOne = "Crash\nMode";
            font->drawString(sOne,
                                menuDots[0].x-(int)font->stringWidth(sOne)/2,
                                menuDots[0].y); // coz have two lines
            
            string sTwo = "Multi-\nthread";
            font->drawString(sTwo,
                                menuDots[1].x-(int)font->stringWidth(sTwo)/2,
                                menuDots[1].y);
            
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
            
        case MULTITHREAD_MODE:{
            
            for (int i=0; i<MULTITHREAD_MODE_MENU; i++) {
                ofSetColor(0,200);
                ofCircle(MultithreadMenu[i], MultithreadMenuSize);
            }
            
            ofSetColor(255);
            string sOne = "3";
            font->drawString(sOne,
                             MultithreadMenu[0].x-(int)font->stringWidth(sOne)/2,
                             MultithreadMenu[0].y+(int)font->stringHeight(sOne)/2);
            
            string sTwo = "5";
            font->drawString(sTwo,
                             MultithreadMenu[1].x-(int)font->stringWidth(sTwo)/2,
                             MultithreadMenu[1].y+(int)font->stringHeight(sTwo)/2);
            
            string sThree = "10";
            font->drawString(sThree,
                             MultithreadMenu[2].x-(int)font->stringWidth(sThree)/2,
                             MultithreadMenu[2].y+(int)font->stringHeight(sThree)/2);
            
            
            
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
                ofCircle(pauseMenu[i], pauseMenuSize);
            }

            ofSetColor(255);
            string sOne = "Resume";
            font->drawString(sOne,
                             pauseMenu[0].x-(int)font->stringWidth(sOne)/2,
                             pauseMenu[0].y+(int)font->stringHeight(sOne)/2);
            
            string sTwo = "Main\nMenu";
            font->drawString(sTwo,
                             pauseMenu[1].x-(int)font->stringWidth(sTwo)/2,
                             pauseMenu[1].y);
            

        }break;
            
        case GAME_END:{
            
            if(whoIsWinner == 0){
                ofSetColor(255,0,0);
                ofRect(0, 0, ofGetWidth(), ofGetHeight());
               
            }else if(whoIsWinner == 1){
                ofSetColor(251, 175, 24);
                ofRect(0, 0, ofGetWidth(), ofGetHeight());
               
            }
            
            for (int i=0; i<GAME_END_MENU; i++) {
                if (i == 1) {
                    ofSetColor(0,50);
                }else{
                    ofSetColor(0,200);
                }
                ofCircle(gameEndMenu[i], gameEndMenuSize);
            }
            
            ofSetColor(255);
            string sOne = "Play\nAgain";
            font->drawString(sOne,
                             gameEndMenu[0].x-(int)font->stringWidth(sOne)/2,
                             gameEndMenu[0].y);
            
            ofSetColor(255);
            string winner;
            if (whoIsWinner == 0) {
                winner = "Red win";
            }else if(whoIsWinner == 1) {
                winner = "Yellow win";
            }
            font->drawString(winner,
                             gameEndMenu[1].x-(int)font->stringWidth(winner)/2,
                             gameEndMenu[1].y+(int)font->stringHeight(winner)/2);
            
            string sTwo = "Main\nMenu";
            font->drawString(sTwo,
                             gameEndMenu[2].x-(int)font->stringWidth(sTwo)/2,
                             gameEndMenu[2].y);
            
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
            }else if (menuDots[1].distance(touchPoint) < 50) {
                condition = MULTITHREAD_MODE;
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

            
        case MULTITHREAD_MODE:{
            
            if (ofDist(crashMenu[0].x, crashMenu[0].y, x, y)<crashMenuSize) {
                condition = IN_GAME;
                start = START_MULITHREAD_MODE;
                rouns = 3;
                
            }else if(ofDist(crashMenu[1].x, crashMenu[1].y, x, y)<crashMenuSize){
                
                condition = IN_GAME;
                start = START_MULITHREAD_MODE;
                rouns = 5;
                
            }else if(ofDist(crashMenu[2].x, crashMenu[2].y, x, y)<crashMenuSize){
                
                condition = IN_GAME;
                start = START_MULITHREAD_MODE;
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
            
        case GAME_END:{
            if (gameEndMenu[0].distance(touchPoint) < crashMenuSize) {
                condition = CRASH_MODE;
            }else if (gameEndMenu[2].distance(touchPoint) < crashMenuSize) {
                condition = MAIN_MENU;
            }
        }break;
    }
            
   
}

//-------------------------------------------------------------------------------
void menu::touchMove(int x, int y){}
void menu::touchUp(int x, int y){}
























