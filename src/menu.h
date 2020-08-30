#ifndef _Menu_Class_
#define _Menu_Class_

// Global Includes
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// Local Includes
#include"common.h"
#include"functions.h"

// Menu Cursor movement Positions
#define         CURSOR_NONE     -1
#define         CURSOR_UP       0
#define         CURSOR_DOWN     1
#define         CURSOR_LEFT     2
#define         CURSOR_RIGHT    3

// Menu States
#define         MENU_COUNT      1
#define         MENU_MAIN       0

class Menu {
private:
    int Menu_State;
    int Menu_Cursor;
    int Menu_Position;
    int Menu_PanelMode;
    bool Menu_PanelMoving;
    bool Menu_Quit;
    vitaRect Menu_DefaultRect;
    vitaRect Menu_CurrentRect;
    vitaRect Menu_LeftRect;
    vitaRect Menu_RightRect;
    vitaRect Menu_DummyRect;
    // FIXME: Possibly remove the need for these, or limit to less.
    // I'd just rather be more memory hungry than spam CPU calculations..
    // - Moto
    bool Menu_XMoveDone;
    bool Menu_YMoveDone;
    bool Menu_HMoveDone;

    /*  vitaRect menuRect;
    vitaRect battery;
    int r,g,b;
    int status;
    int target, fade, barFade;
    bool leaveMenu;
    bool crossNeedsReset;
    int menuPos;
    bool moveUp, moveDown;
    bool quit;
    bool credits;
    bool controls;*/
public:
    void Init();
    void Main(bool Buttons[15]);
    void MenuMain();
    void SetUpPanelSizes();
    void DrawPanels();
    void PanelLeft();
    void PanelRight();
    //void start();
    /*void doStuff(bool keys[15], bool showBattery);
    void menuPartial();
    int getStatus();
    void setStatus(int status);
    bool getQuit();
    void showCredits();
    void showControls();*/
};

#endif