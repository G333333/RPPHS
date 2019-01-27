#include"menu.h"

void Menu::init()
{
  status = 1;

  menuRect.x = 966;
  menuRect.y = 122;
  menuRect.w = 255;
  menuRect.h = 300;

  target = 711;
  barFade = 0;
  fade = 0;

  moveUp = false;
  moveDown = false;
  menuPos = 1;
  quit = false;
  credits = false;
  controls = false;

  crossNeedsReset = true;
}

void Menu::start()
{
  target = 711;
  //barFade = 0;
  //fade = 0;

  moveUp = false;
  moveDown = false;

  menuPos = 1;

  crossNeedsReset = true;
}

void Menu::doStuff(bool keys[15], bool showBattery)
{
  vita2d_draw_texture_scale(gameBackground, 0, 0, 2, 2);

  if(!credits && !controls)
  {
    vita2d_draw_rectangle(menuRect.x, menuRect.y, menuRect.w, menuRect.h, RGBA8(menuBGColorR,menuBGColorG,menuBGColorB, fade));
    drawEmptyRect(menuRect, RGBA8(menuBorderR,menuBorderG,menuBorderB,fade));


    switch (menuPos) {
      case 1:
        vita2d_draw_rectangle(menuRect.x + 1, menuRect.y, menuRect.w - 1, 50, RGBA8(menuBarColorR,menuBarColorG,menuBarColorB, barFade));
        break;
      case 2:
        vita2d_draw_rectangle(menuRect.x + 1, menuRect.y + 50, menuRect.w - 1, 50, RGBA8(menuBarColorR,menuBarColorG,menuBarColorB, barFade));
        break;
      case 3:
        vita2d_draw_rectangle(menuRect.x + 1, menuRect.y + 100, menuRect.w - 1, 50, RGBA8(menuBarColorR,menuBarColorG,menuBarColorB, barFade));
        break;
      case 4:
        vita2d_draw_rectangle(menuRect.x + 1, menuRect.y + 150, menuRect.w - 1, 50, RGBA8(menuBarColorR,menuBarColorG,menuBarColorB, barFade));
        break;
      case 5:
        vita2d_draw_rectangle(menuRect.x + 1, menuRect.y + 200, menuRect.w - 1, 50, RGBA8(menuBarColorR,menuBarColorG,menuBarColorB, barFade));
        break;
    }
    vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 30, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Play");
    vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 80, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Options");
    vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 130, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Credits");
    vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 180, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Controls");
    vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 230, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Quit");

    vita2d_draw_texture_scale(crossImage,menuRect.x + 7, menuRect.y + menuRect.h - 40, 1,1);
    vita2d_font_draw_text(font, menuRect.x + 40, menuRect.y + menuRect.h - 16, RGBA8(helpTextR,helpTextG,helpTextB, fade), 20.0f, "Select");

    if(keys[0] && !moveUp)
    {
      menuPos--;
      moveUp = true;
    }

    if(keys[1] && !moveDown)
    {
      menuPos++;
      moveDown = true;
    }

    if(keys[4])
    {
      if(!crossNeedsReset)
      {
        switch (menuPos) {
          case 1:
            target = 966;
            break;
          case 2:
            target = 966;
            status = 3;
            break;
          case 3:
            credits = true;
            break;
          case 4:
            controls = true;
            break;
          case 5:
            quit = true;
            break;
        }
      }
    }
    if(!keys[4])
    {
      crossNeedsReset = false;
    }

    if(keys[9] && !moveUp)
    {
      menuPos--;
      moveUp = true;
    }
    else if(!keys[9] && !keys[0])
    {
      moveUp = false;
    }

    if(keys[8] & !moveDown)
    {
      menuPos++;
      moveDown = true;
    }
    else if(!keys[8] && !keys[1])
    {
      moveDown = false;
    }

    if(menuPos > 5)
    {
      menuPos = 1;
    }
    if(menuPos < 1)
    {
      menuPos = 5;
    }
    /*if(keys[14])
    {
      credits = true;
    }*/
  } else {
    if (credits) {
      showCredits();
      if (keys[5]) credits = false;
    } else {
      showControls();
      if (keys[5]) controls = false;
    }
  }
  /*else if(credits)
  {
    showCredits();
    if(keys[5]) credits = false;
  } else if (controls) {
    showControls();
    if(keys[5]) controls = false;
  }*/
  if(menuRect.x < target)
  {
    menuRect.x += 10;
    if(fade > 10)
    {
      fade -= 10;
      barFade -= 4;
    }
  }
  if(menuRect.x > target)
  {
    menuRect.x -= 10;
    if(fade < 240)
    {
      fade += 10;
      barFade += 4;
    }
  }
  if(menuRect.x >= target && target == 966 && menuPos == 1)
  {
    status = 2;
  }
}

void Menu::menuPartial()
{
  vita2d_draw_rectangle(menuRect.x, menuRect.y, menuRect.w, menuRect.h, RGBA8(menuBGColorR,menuBGColorG,menuBGColorB, fade));
  drawEmptyRect(menuRect, RGBA8(menuBorderR,menuBorderG,menuBorderB,fade));


  switch (menuPos) {
      case 1:
        vita2d_draw_rectangle(menuRect.x + 1, menuRect.y, menuRect.w - 1, 50, RGBA8(menuBarColorR,menuBarColorG,menuBarColorB, barFade));
        break;
      case 2:
        vita2d_draw_rectangle(menuRect.x + 1, menuRect.y + 50, menuRect.w - 1, 50, RGBA8(menuBarColorR,menuBarColorG,menuBarColorB, barFade));
        break;
      case 3:
        vita2d_draw_rectangle(menuRect.x + 1, menuRect.y + 100, menuRect.w - 1, 50, RGBA8(menuBarColorR,menuBarColorG,menuBarColorB, barFade));
        break;
      case 4:
        vita2d_draw_rectangle(menuRect.x + 1, menuRect.y + 150, menuRect.w - 1, 50, RGBA8(menuBarColorR,menuBarColorG,menuBarColorB, barFade));
        break;
      case 5:
        vita2d_draw_rectangle(menuRect.x + 1, menuRect.y + 200, menuRect.w - 1, 50, RGBA8(menuBarColorR,menuBarColorG,menuBarColorB, barFade));
        break;
    }
  vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 30, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Play");
  vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 80, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Options");
  vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 130, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Credits");
  vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 180, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Controls");
  vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 230, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Quit");

  vita2d_draw_texture_scale(crossImage,menuRect.x + 7, menuRect.y + menuRect.h - 40, 1,1);
  vita2d_font_draw_text(font, menuRect.x + 40, menuRect.y + menuRect.h - 16, RGBA8(helpTextR,helpTextG,helpTextB, fade), 20.0f, "Select");
  if(menuRect.x < target)
  {
    menuRect.x += 10;
    if(fade > 10)
    {
      fade -= 10;
      barFade -= 4;
    }
  }
  if(menuRect.x > target)
  {
    menuRect.x -= 10;
    if(fade < 240)
    {
      fade += 10;
      barFade += 4;
    }
  }
}

int Menu::getStatus()
{
  return status;
}

void Menu::setStatus(int status)
{
  this->status = status;
}

bool Menu::getQuit()
{
  return quit;
}

void Menu::showCredits()
{
  vita2d_draw_rectangle(160, 142, 640, 332, RGBA8(menuBGColorR,menuBGColorG,menuBGColorB, 240));
  drawEmptyRect(160, 142, 640, 332, RGBA8(menuBorderR,menuBorderG,menuBorderB, 100));

  vita2d_font_draw_text(font, 960 / 2 - vita2d_font_text_width(font, 20.0f, "CREDITS") / 2, 544 / 3 - 15, RGBA8(mainTextR,mainTextG,mainTextB,255), 20.0f, "CREDITS");
  vita2d_font_draw_text(font, 160 + 5, 544 / 3 + 10, RGBA8(mainTextR,mainTextG,mainTextB,255), 20.0f, "G33: Programming, Design");
  vita2d_font_draw_text(font, 160 + 5, 544 / 3 + 30, RGBA8(mainTextR,mainTextG,mainTextB,255), 20.0f, "MotoLegacy: Livearea, Player/Enemies, Programming, Design");
  vita2d_font_draw_text(font, 960 / 2 - vita2d_font_text_width(font, 20.0f, "SPECIAL THANKS") / 2, 544 / 3 + 80, RGBA8(mainTextR,mainTextG,mainTextB,255), 20.0f, "SPECIAL THANKS");
  vita2d_font_draw_text(font, 160 + 5, 544 / 3 + 100, RGBA8(mainTextR,mainTextG,mainTextB,255), 20.0f, "- Xerpi: libVita2D");
  vita2d_font_draw_text(font, 160 + 5, 544 / 3 + 120, RGBA8(mainTextR,mainTextG,mainTextB,255), 20.0f, "- Xyz: SoLoud Vita Port");
  vita2d_font_draw_text(font, 160 + 5, 544 / 3 + 140, RGBA8(mainTextR,mainTextG,mainTextB,255), 20.0f, "- Rinnegatamante: FPS Counter Code");
  vita2d_font_draw_text(font, 160 + 5, 544 / 3 + 160, RGBA8(mainTextR,mainTextG,mainTextB,255), 20.0f, "- VitaSDK Contributors");
  vita2d_font_draw_text(font, 160 + 5, 544 / 3 + 180, RGBA8(mainTextR,mainTextG,mainTextB,255), 20.0f, "- Ivan voirol @ OpenGameArt: Background Grid");
  vita2d_font_draw_text(font, 160 + 5, 544 / 3 + 200, RGBA8(mainTextR,mainTextG,mainTextB,255), 20.0f, "- yd @ OpenGameArt: Menu Music (outhere.ogg)");
  vita2d_font_draw_text(font, 160 + 5, 544 / 3 + 220, RGBA8(mainTextR,mainTextG,mainTextB,255), 20.0f, "- Trevor Lentz @ OpenGameArt: Game Music (heroimmortal.ogg)");
  
  std::string tempString = "Build Date: ";
  tempString += buildDate;
  vita2d_font_draw_text(font, 160 + 5, 544 - 20, RGBA8(mainTextR,mainTextG,mainTextB,255), 20.0f, tempString.c_str());


  int tempWidth = vita2d_texture_get_width(circleImage); //get the width and height to draw in correct place.
  int tempHeight = vita2d_texture_get_height(circleImage); //both images are the same size. //used for text too

  vita2d_font_draw_text(font, 160 + tempWidth + 10, 544 / 2 + 544 / 4 + 47, RGBA8(helpTextR,helpTextG,helpTextB,255), 20.0f, "Main Menu");

  vita2d_draw_texture_scale(circleImage, 160 + 5, 544 / 2 + 544 / 4 + 55 - tempHeight, 1, 1);
}

void Menu::showControls()
{
  vita2d_draw_rectangle(160, 142, 640, 232, RGBA8(menuBGColorR,menuBGColorG,menuBGColorB, 240));
  drawEmptyRect(160, 142, 640, 232, RGBA8(menuBorderR,menuBorderG,menuBorderB, 100));

  vita2d_font_draw_text(font, 960 / 2 - vita2d_font_text_width(font, 20.0f, "CONTROLS") / 2, 544 / 3 - 15, RGBA8(mainTextR,mainTextG,mainTextB,255), 20.0f, "CONTROLS");
  
  vita2d_font_draw_text(font, 160 + 40, 544 / 3 + 14, RGBA8(mainTextR,mainTextG,mainTextB,255), 20.0f, "Move Player");
  vita2d_draw_texture_scale(lStick, 160 + 5, 544 / 3 + 20 - vita2d_texture_get_height(lStick), 1, 1);

  vita2d_font_draw_text(font, 160 + 40, 544 / 3 + 54, RGBA8(mainTextR,mainTextG,mainTextB,255), 20.0f, "Shoot");
  vita2d_draw_texture_scale(rStick, 160 + 5, 544 / 3 + 60 - vita2d_texture_get_height(rStick), 1, 1);

  vita2d_font_draw_text(font, 160 + 42, 544 / 3 + 88, RGBA8(mainTextR,mainTextG,mainTextB,255), 20.0f, "/");
  vita2d_font_draw_text(font, 160 + 95, 544 / 3 + 90, RGBA8(mainTextR,mainTextG,mainTextB,255), 20.0f, "Fire Bomb");
  vita2d_draw_texture_scale(lTriggerImage, 160 + 5, 544 / 3 + 90 - vita2d_texture_get_height(lTriggerImage), 1, 1);
  vita2d_draw_texture_scale(rTriggerImage, 160 + 52, 544 / 3 + 90 - vita2d_texture_get_height(rTriggerImage), 1, 1);

  vita2d_font_draw_text(font, 160 + vita2d_texture_get_width(circleImage) + 10, 544 / 2 + 544 / 4 + 47 - 100, RGBA8(helpTextR,helpTextG,helpTextB,255), 20.0f, "Main Menu");
  vita2d_draw_texture_scale(circleImage, 160 + 5, 544 / 2 + 544 / 4 + 55 - 100 - vita2d_texture_get_height(circleImage), 1, 1);
}
