//
//  menu.h
//  KingdaKaNew
//
//  Created by PengCheng on 7/10/13.
//
//

#ifndef __KingdaKaNew__menu__
#define __KingdaKaNew__menu__


#include "ofMain.h"

#define MAIN_MENU_ITEMS 5
#define PAUSE_MENU_ITEMS 2
#define END_MENU_ITEMS 3
#define CRASH_MODE_MENU 3

enum menu_condition {
    MAIN_MENU,
    CRASH_MODE,
    IN_GAME,
    PAUSE_GAME,
    GAME_OVER,
    TUTORIAL,
    CREDITS,
};

enum menu_start {
    START_EMPTY,
    START_CRASH_MODE,
    START_TUTORIAL,
    START_CREDITS,
};

class menu{

public:
    void setup();
    void setupMainMenu();
    void setupCrashMenu();
    void setupPauseGame();
    void setupInGame();

    void draw();
    void touchDown(int x, int y);
    void touchMove(int x, int y);
    void touchUp(int x, int y);
    
    menu_condition condition;
    
    ofPoint menuDots[MAIN_MENU_ITEMS];
    ofTrueTypeFont *font, *fontBig;
    
    ofPoint menuButton[2];
    int menuButtonSize;
    
    bool bPause;
    ofPoint pauseMenu[PAUSE_MENU_ITEMS];
    
    menu_start start;
    int rouns;
    //crash menu
    float crashMenuSize;
    ofPoint crashMenu[CRASH_MODE_MENU];
};

#endif /* defined(__KingdaKaNew__menu__) */















