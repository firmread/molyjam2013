//
//  menu.cpp
//  KingdaKa
//
//  Created by Firm Read on 7/6/13.
//
//

#include "menu.h"
#include "testApp.h"

void menu::setup(){
    mode1.set(ofGetWidth()/2, 100);
    mode2.set(ofGetWidth()/2, 200);
    mode3.set(ofGetWidth()/2, 300);
    tutorial.set(ofGetWidth()/2, 400);
    credit.set(ofGetWidth()/2, 500);
}

void menu::update(){
    
}

void menu::draw(){
    ofBackgroundGradient(ofColor::white, ofColor::whiteSmoke);
    ofSetColor(100, 0, 0);
    ofCircle(mode1, 50);
    ofSetColor(0, 100, 0);
    ofCircle(mode2, 50);
    ofCircle(mode3, 50);
    ofCircle(tutorial, 50);
    ofCircle(credit, 50);
    
}

void menu::reset(){
    
}

void menu::touchDown(ofTouchEventArgs & touch){
    
    if (mode1.distance(touch)<50) {
        ((testApp*)ofGetAppPtr())->changePage( 1 );
    }
    
}

void menu::touchMoved(ofTouchEventArgs & touch){
    
}

void menu::touchUp(ofTouchEventArgs & touch){
    
}

void menu::touchDoubleTap(ofTouchEventArgs & touch){
    
}

void menu::touchCancelled(ofTouchEventArgs & touch){
    
}