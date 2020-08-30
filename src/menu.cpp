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

    Menu_DummyIMG = vita2d_load_PNG_file("app0:/images/theme/default/touch.png");

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

    // Rank Menu
    if (Menu_State < 2) {
        Menu::MenuRank();
    }

    // Main Menu
    if (Menu_State < 3) {
        Menu::MenuMain();
    }

    // Options Menu
    if (Menu_State < 4 && Menu_State > 0) {
        Menu::MenuOptions();
    }

    // Draw Panels
    Menu::DrawPanels();

    // Left/Right Triggers: Change Panels
    if ((Buttons[13] && !Menu_PanelMoving && Menu_State > 0) || Menu_PanelMode == 2) {
        Menu::PanelRight();
    } else if ((Buttons[14] && !Menu_PanelMoving && Menu_State < MENU_COUNT) || Menu_PanelMode == 1) {
        Menu::PanelLeft();
    }

    // 'debug' Text
    vita2d_font_draw_text(font, 20, 25, RGBA8(255, 0, 0, 255), 20.0f, "super epic rpphs 2.0 menu concept (w.i.p.)");
    vita2d_font_draw_text(font, 20, 40, RGBA8(255, 0, 0, 255), 20.0f, "haha lol");
    std::string Menu_DebugString;
    Menu_DebugString = "Menu State: ";
    Menu_DebugString += std::to_string(Menu_State);
    vita2d_font_draw_text(font, 20, 55, RGBA8(255, 0, 0, 255), 20.0f, Menu_DebugString.c_str());
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
    if (Menu_State < MENU_COUNT) {
        // top
        vita2d_draw_rectangle(Menu_RightRect.x, Menu_RightRect.y, Menu_RightRect.w, 4, RGBA8(0, 255, 0, 255));
        // bottom
        vita2d_draw_rectangle(Menu_RightRect.x, Menu_RightRect.h + Menu_RightRect.y, Menu_RightRect.w, 4, RGBA8(0, 255, 0, 255));
        // left
        vita2d_draw_rectangle(Menu_RightRect.x, Menu_RightRect.y, 4, Menu_RightRect.h, RGBA8(0, 255, 0, 255));
        // right
        vita2d_draw_rectangle(Menu_RightRect.w + Menu_RightRect.x, Menu_RightRect.y, 4, Menu_RightRect.h + 4, RGBA8(0, 255, 0, 255));
    }

    // Left Panel
    if (Menu_State > 0) {
        // top
        vita2d_draw_rectangle(Menu_LeftRect.x, Menu_LeftRect.y, Menu_LeftRect.w, 4, RGBA8(0, 255, 0, 255));
        // bottom
        vita2d_draw_rectangle(Menu_LeftRect.x, Menu_LeftRect.h + Menu_LeftRect.y, Menu_LeftRect.w, 4, RGBA8(0, 255, 0, 255));
        // left
        vita2d_draw_rectangle(Menu_LeftRect.x, Menu_LeftRect.y, 4, Menu_LeftRect.h, RGBA8(0, 255, 0, 255));
        // right
        vita2d_draw_rectangle(Menu_LeftRect.w + Menu_LeftRect.x, Menu_LeftRect.y, 4, Menu_LeftRect.h + 4, RGBA8(0, 255, 0, 255));
    }

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
// Menu::MenuRank()
// The Ranks Menu
//
void Menu::MenuRank()
{
    // Calculate Scaling and Offsets
    vitaRect Menu_RelevantPanel;
    if (Menu_State == MENU_RANK) {
        Menu_RelevantPanel = Menu_CurrentRect;
    } else if (Menu_State == 1) {
        Menu_RelevantPanel = Menu_LeftRect;
    }

    float Menu_XOffset = Menu_RelevantPanel.x + 4;
    float Menu_YOffset = Menu_RelevantPanel.y + 4;

    Menu_ScaleFactor = (Menu_RelevantPanel.h / Menu_DefaultRect.h);

    vita2d_font_draw_text(font, Menu_XOffset + 5, Menu_YOffset + 150, RGBA8(255, 255, 0, 255), 35.0f * Menu_ScaleFactor, "POOOOG RANKS MENUUU!");
}

//
// Menu::MenuMain()
// The Main Menu
//
void Menu::MenuMain()
{
    // Calculate Scaling and Offsets
    vitaRect Menu_RelevantPanel;
    if (Menu_State == MENU_MAIN) {
        Menu_RelevantPanel = Menu_CurrentRect;
    } else if (Menu_State == 0) {
        Menu_RelevantPanel = Menu_RightRect;
    } else if (Menu_State == 2) {
        Menu_RelevantPanel = Menu_LeftRect;
    }

    float Menu_XOffset = Menu_RelevantPanel.x + 4;
    float Menu_YOffset = Menu_RelevantPanel.y + 4;

    Menu_ScaleFactor = (Menu_RelevantPanel.h / Menu_DefaultRect.h);

    vita2d_draw_texture_scale(Menu_DummyIMG, Menu_XOffset + 100, Menu_YOffset + 80, 3 * Menu_ScaleFactor, 3 * Menu_ScaleFactor);

    vita2d_font_draw_text(font, Menu_XOffset + 25, Menu_YOffset + 25, RGBA8(0, 0, 255, 255), 20.0f * Menu_ScaleFactor, "lol this is the main menu (or is it owo)");
    vita2d_font_draw_text(font, Menu_XOffset + 5, Menu_YOffset + 60, RGBA8(255, 0, 255, 255), 25.0f * Menu_ScaleFactor, "RPPHS IS THE NEW CALL OF DUTY!! UWU XDD");
    vita2d_font_draw_text(font, Menu_XOffset + 5, Menu_YOffset + 150, RGBA8(255, 255, 255, 255), 35.0f * Menu_ScaleFactor, "MAIN MENU HAHAHAHA");
}

//
// Menu::MenuOptions()
// The Options Menu
//
void Menu::MenuOptions()
{
    // Calculate Scaling and Offsets
    vitaRect Menu_RelevantPanel;
    if (Menu_State == MENU_OPTIONS) {
        Menu_RelevantPanel = Menu_CurrentRect;
    } else if (Menu_State == 1) {
        Menu_RelevantPanel = Menu_RightRect;
    }

    float Menu_XOffset = Menu_RelevantPanel.x + 4;
    float Menu_YOffset = Menu_RelevantPanel.y + 4;

    Menu_ScaleFactor = (Menu_RelevantPanel.h / Menu_DefaultRect.h);

    vita2d_font_draw_text(font, Menu_XOffset + 5, Menu_YOffset + 150, RGBA8(0, 255, 255, 255), 35.0f * Menu_ScaleFactor, "i got lazy here lol");
    vita2d_font_draw_text(font, Menu_XOffset + 5, Menu_YOffset + 180, RGBA8(255, 255, 0, 255), 35.0f * Menu_ScaleFactor, "this is options doe!");
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

    if (Menu_State != MENU_COUNT - 1)
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
        Menu_State++;

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

    if (Menu_State != 1)
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
        Menu_State--;

        // Re-define Panels
        Menu::SetUpPanelSizes();
    }
}