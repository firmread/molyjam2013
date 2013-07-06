//
//  menu.cpp
//  UI
//
//  Created by Firm Read on 7/6/13.
//
//

#include "menu.h"
#include "testApp.h"
void menu::setup(){
    
    blue.set(86, 217, 205);
    
    int spacing = ofGetHeight()/6;
    for (int i =0; i<5; i++) {
        menuDots[i].set(ofGetWidth()/2, (i+1)*spacing);
    }
    
    ofBackground(255);
    splash = true;
    
    
    
}

void menu::draw(){
    
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


void menu::touchDown(ofTouchEventArgs & touch){
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