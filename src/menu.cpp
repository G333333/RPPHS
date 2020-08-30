#include "menu.h"

//
// Menu::Init()
// Initialization of Menu-based variables
//
void Menu::Init()
{
    // Menu Options
    Menu_State = MENU_MAIN;
    Menu_Cursor = CURSOR_NONE;
    Menu_Position = 0;
    Menu_PanelMode = 0;
    Menu_PanelMoving = false;
    Menu_Quit = false;

    // Set Panel Sizes
    Menu::SetUpPanelSizes();

    // We aren't moving..
    Menu_XMoveDone = Menu_YMoveDone = Menu_HMoveDone = true;
}

//
// Menu::SetUpPanelSizes()
// (Re-)Establishes Panel Size
//
void Menu::SetUpPanelSizes()
{
    // Default Rectangle
    // 186, 102 -> 777, 495 (4px)
    Menu_DefaultRect.x = 186;
    Menu_DefaultRect.y = 102;
    Menu_DefaultRect.w = 591;
    Menu_DefaultRect.h = 393;

    // Set Current Rect to the Default
    Menu_CurrentRect = Menu_DefaultRect;

    // Right Rect
    Menu_RightRect.x = 919;
    Menu_RightRect.y = 130;
    Menu_RightRect.w = 591;
    Menu_RightRect.h = 340;

    // Left Rect
    Menu_LeftRect.x = -552;
    Menu_LeftRect.y = 130;
    Menu_LeftRect.w = 591;
    Menu_LeftRect.h = 340;
}

//
// Menu::Main()
// Contains the main Menu switch and Panel drawing
//
void Menu::Main(bool Buttons[15]) 
{
    // Black Background
    vita2d_draw_rectangle(0, 0, 960, 544, RGBA8(0, 0, 0, 255));

    // Menu-Specific Drawing
    switch (Menu_State) {
        case MENU_MAIN:
            Menu::MenuMain();
            break;
        default:
            break;
    }

    // Draw Panels
    Menu::DrawPanels();

    // Left/Right Triggers: Change Panels
    if ((Buttons[13] && !Menu_PanelMoving) || Menu_PanelMode == 2) {
        Menu::PanelRight();
    } else if ((Buttons[14] && !Menu_PanelMoving) || Menu_PanelMode == 1) {
        Menu::PanelLeft();
    }

    // 'debug' Text
    vita2d_font_draw_text(font, 20, 25, RGBA8(255, 0, 0, 255), 20.0f, "super epic rpphs 2.0 menu concept (w.i.p.)");
    vita2d_font_draw_text(font, 20, 40, RGBA8(255, 0, 0, 255), 20.0f, "haha lol");
}

//
// Menu::DrawPanels()
// Draws the Left, Current, and Right Panels
//
void Menu::DrawPanels()
{
    // Current Panel
    // top
    vita2d_draw_rectangle(Menu_CurrentRect.x, Menu_CurrentRect.y, Menu_CurrentRect.w, 4, RGBA8(0, 255, 0, 255));
    // bottom
    vita2d_draw_rectangle(Menu_CurrentRect.x, Menu_CurrentRect.h + Menu_CurrentRect.y, Menu_CurrentRect.w, 4, RGBA8(0, 255, 0, 255));
    // left
    vita2d_draw_rectangle(Menu_CurrentRect.x, Menu_CurrentRect.y, 4, Menu_CurrentRect.h, RGBA8(0, 255, 0, 255));
    // right
    vita2d_draw_rectangle(Menu_CurrentRect.w + Menu_CurrentRect.x, Menu_CurrentRect.y, 4, Menu_CurrentRect.h + 4, RGBA8(0, 255, 0, 255));

    // Right Panel
    // top
    vita2d_draw_rectangle(Menu_RightRect.x, Menu_RightRect.y, Menu_RightRect.w, 4, RGBA8(0, 255, 0, 255));
    // bottom
    vita2d_draw_rectangle(Menu_RightRect.x, Menu_RightRect.h + Menu_RightRect.y, Menu_RightRect.w, 4, RGBA8(0, 255, 0, 255));
    // left
    vita2d_draw_rectangle(Menu_RightRect.x, Menu_RightRect.y, 4, Menu_RightRect.h, RGBA8(0, 255, 0, 255));
    // right
    vita2d_draw_rectangle(Menu_RightRect.w + Menu_RightRect.x, Menu_RightRect.y, 4, Menu_RightRect.h + 4, RGBA8(0, 255, 0, 255));

    // Left Panel
    // top
    vita2d_draw_rectangle(Menu_LeftRect.x, Menu_LeftRect.y, Menu_LeftRect.w, 4, RGBA8(0, 255, 0, 255));
    // bottom
    vita2d_draw_rectangle(Menu_LeftRect.x, Menu_LeftRect.h + Menu_LeftRect.y, Menu_LeftRect.w, 4, RGBA8(0, 255, 0, 255));
    // left
    vita2d_draw_rectangle(Menu_LeftRect.x, Menu_LeftRect.y, 4, Menu_LeftRect.h, RGBA8(0, 255, 0, 255));
    // right
    vita2d_draw_rectangle(Menu_LeftRect.w + Menu_LeftRect.x, Menu_LeftRect.y, 4, Menu_LeftRect.h + 4, RGBA8(0, 255, 0, 255));

    // Dummy Panel
    if (Menu_PanelMode != 0) {
        // top
        vita2d_draw_rectangle(Menu_DummyRect.x, Menu_DummyRect.y, Menu_DummyRect.w, 4, RGBA8(0, 255, 0, 255));
        // bottom
        vita2d_draw_rectangle(Menu_DummyRect.x, Menu_DummyRect.h + Menu_DummyRect.y, Menu_DummyRect.w, 4, RGBA8(0, 255, 0, 255));
        // left
        vita2d_draw_rectangle(Menu_DummyRect.x, Menu_DummyRect.y, 4, Menu_DummyRect.h, RGBA8(0, 255, 0, 255));
        // right
        vita2d_draw_rectangle(Menu_DummyRect.w + Menu_DummyRect.x, Menu_DummyRect.y, 4, Menu_DummyRect.h + 4, RGBA8(0, 255, 0, 255));
    }
}

//
// Menu::MenuMain()
// The Main Menu
//
void Menu::MenuMain()
{
    vita2d_font_draw_text(font, 300, 200, RGBA8(0, 0, 255, 255), 20.0f, "lol this is the main menu (or is it owo)");
}

//
// Menu::PanelLeft
// Move the current Panel to the Left
//
void Menu::PanelLeft()
{
    // Initialize Panel Move
    if (Menu_PanelMode != 1) {
        // Move Mode
        Menu_PanelMoving = true;
        Menu_PanelMode = 1;
        Menu_XMoveDone = Menu_YMoveDone = Menu_HMoveDone = false;

        // Set up DummyRect
        Menu_DummyRect = Menu_LeftRect;
        Menu_DummyRect.x = 1657;
    }

    // Shrink Current Rect
    Menu_CurrentRect.x -= 40;
    Menu_CurrentRect.y += 2;
    Menu_CurrentRect.h -= 4;

    // Expand Right Rect
    Menu_RightRect.x -= 40;
    Menu_RightRect.y -= 2;
    Menu_RightRect.h += 4;

    Menu_LeftRect.x -= 40;
    Menu_DummyRect.x -= 40;

    // Force Size
    if (Menu_CurrentRect.x < -552) {
        Menu_CurrentRect.x = -552;
        Menu_RightRect.x = 186;
        Menu_DummyRect.x = 919;
        Menu_XMoveDone = true;
    }

    if (Menu_CurrentRect.y > 130) {
        Menu_CurrentRect.y = 130;
        Menu_RightRect.y = 102;
        Menu_YMoveDone = true;
    }

    if (Menu_CurrentRect.h < 340) {
        Menu_CurrentRect.h = 340;
        Menu_RightRect.h = 393;
        Menu_HMoveDone = true;
    }

    // If we're done, get outta here
    if (Menu_XMoveDone == true && Menu_YMoveDone == true && Menu_HMoveDone == true) {
        Menu_PanelMoving = false;
        Menu_PanelMode = 0;

        // Re-define Panels
        Menu::SetUpPanelSizes();
    }
}

//
// Menu::PanelRight
// Move the current Panel to the Right
//
void Menu::PanelRight()
{
    // Initialize Panel Move
    if (Menu_PanelMode != 2) {
        // Move Mode
        Menu_PanelMoving = true;
        Menu_PanelMode = 2;
        Menu_XMoveDone = Menu_YMoveDone = Menu_HMoveDone = false;

        // Set up DummyRect
        Menu_DummyRect = Menu_LeftRect;
        Menu_DummyRect.x = -1290;
    }

    // Shrink Current Rect
    Menu_CurrentRect.x += 40;
    Menu_CurrentRect.y += 2;
    Menu_CurrentRect.h -= 4;

    // Expand Left Rect
    Menu_LeftRect.x += 40;
    Menu_LeftRect.y -= 2;
    Menu_LeftRect.h += 4;

    Menu_RightRect.x += 40;
    Menu_DummyRect.x += 40;

    // Force Size
    if (Menu_CurrentRect.x > 919) {
        Menu_CurrentRect.x = 919;
        Menu_LeftRect.x = Menu_DefaultRect.x;
        Menu_DummyRect.x = -475;
        Menu_XMoveDone = true;
    }

    if (Menu_CurrentRect.y > 130) {
        Menu_CurrentRect.y = 130;
        Menu_LeftRect.y = Menu_DefaultRect.y;
        Menu_YMoveDone = true;
    }

    if (Menu_CurrentRect.h < 340) {
        Menu_CurrentRect.h = 340;
        Menu_LeftRect.h = Menu_DefaultRect.h;
        Menu_HMoveDone = true;
    }

    // If we're done, get outta here
    if (Menu_XMoveDone == true && Menu_YMoveDone == true && Menu_HMoveDone == true) {
        Menu_PanelMoving = false;
        Menu_PanelMode = 0;

        // Re-define Panels
        Menu::SetUpPanelSizes();
    }
}