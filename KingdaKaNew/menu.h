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
#define MULTITHREAD_MODE_MENU 3
#define GAME_END_MENU 3
enum menu_condition {
    MAIN_MENU,
    CRASH_MODE,
    MULTITHREAD_MODE,
    IN_GAME,
    PAUSE_GAME,
    GAME_END,
    TUTORIAL,
    CREDITS,
};


enum menu_start {
    START_EMPTY,
    START_CRASH_MODE,
    START_MULITHREAD_MODE,
    START_TUTORIAL,
    START_CREDITS,
};

class menu{

public:
    void setup();
    void setupMainMenu();
    void setupCrashMenu();
    void setupPauseGame();
    void setupMultithreadMenu();
    void setupInGame();
    void setupGameEnd();
    void draw();
    void touchDown(int x, int y);
    void touchMove(int x, int y);
    void touchUp(int x, int y);
    
    menu_condition condition;
    menu_start start;
    ofTrueTypeFont *font, *fontBig;

    //++++++++Main menu buttons+++++++++++++++++++
    int menuButtonSize;
    ofPoint menuDots[MAIN_MENU_ITEMS];
    
    //++++++++In game buttons+++++++++++++++++++
    ofPoint menuButton[2];
   
    //++++++++Pause menu buttons+++++++++++++++++++
    bool bPause;
    float pauseMenuSize;
    ofPoint pauseMenu[PAUSE_MENU_ITEMS];
    
    //++++++++Crash Mode select menu+++++++++++++++++++
    int rouns;
    float crashMenuSize;
    ofPoint crashMenu[CRASH_MODE_MENU];
    
    //++++++++Multithread Mode select menu+++++++++++++++++++
    float MultithreadMenuSize;
    ofPoint MultithreadMenu[MULTITHREAD_MODE_MENU];

    //++++++++Game end menu+++++++++++++++++++
    float gameEndMenuSize;
    ofPoint gameEndMenu[GAME_END_MENU];
    int whoIsWinner;
};

#endif /* defined(__KingdaKaNew__menu__) */















