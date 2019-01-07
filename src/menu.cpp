#include"menu.h"

void Menu::init()
{
  status = 1;

  menuRect.x = 966;
  menuRect.y = 122;
  menuRect.w = 255;
  menuRect.h = 300;

  battery.x = 856;
  battery.y = 40;
  battery.w = 52;
  battery.h = 15;
  r = b = g = 0;

  target = 711;
  barFade = 0;
  fade = 0;

  moveUp = false;
  moveDown = false;
  menuPos = 1;
  quit = false;
  credits = false;

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

void Menu::doStuff(vita2d_font *font, bool keys[15], int batteryPercent, bool showBattery)
{
  vita2d_draw_texture_scale(gameBackground, 0, 0, 2, 2);

 //battery stuff
  if(batteryPercent > 50)
  {
    r = 0;
    g = 255;
    b = 0;
  }
  else if(batteryPercent > 25 && batteryPercent <= 50)
  {
    r = 244;
    g = 244;
    b = 0;
  }

  else if(batteryPercent <= 25)
  {
    r = 255;
    g = 0;
    b = 0;
  }
  vitaRect batteryTip;
  batteryTip.x = battery.x + battery.w;
  batteryTip.y = battery.y + battery.h / 4;
  batteryTip.w = 3;
  batteryTip.h = battery.h / 2;

  if(showBattery)
  {
    for(int i = 0; i < batteryPercent / 2; i++)
    {
      vita2d_draw_line(battery.x + i + 1, battery.y, battery.x + i + 1, battery.y + battery.h, RGBA8(r,g,b,255));
    }
    //vita2d_font_draw_textf(font, battery.x + battery.w / 2 - 20, battery.y + battery.h / 2 + 10, RGBA8(0,0,255,255), 20.0f, "%d%%", batteryPercent);
    drawEmptyRect(battery, RGBA8(menuBorderR,menuBorderG,menuBorderB, 255));
    vita2d_draw_rectangle(batteryTip.x, batteryTip.y, batteryTip.w, batteryTip.h, RGBA8(menuBorderR,menuBorderG,menuBorderB, 255));
  }

  if(!credits)
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
    }
    vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 30, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Play");
    vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 80, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Options");
    vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 130, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Credits");
    vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 180, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Quit");

    vita2d_draw_texture_scale(crossImage,menuRect.x + 10, menuRect.y + menuRect.h - 40, 1,1);
    vita2d_font_draw_text(font, menuRect.x + 45, menuRect.y + menuRect.h - 20, RGBA8(helpTextR,helpTextG,helpTextB, fade), 20.0f, "Select");

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

    if(menuPos > 4)
    {
      menuPos = 1;
    }
    if(menuPos < 1)
    {
      menuPos = 4;
    }
    /*if(keys[14])
    {
      credits = true;
    }*/
  }
  else if(credits)
  {
    showCredits(font);
    if(keys[5]) credits = false;
  }
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

void Menu::menuPartial(vita2d_font *font)
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
    }
  vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 30, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Play");
  vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 80, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Options");
  vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 130, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Credits");
  vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 180, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Quit");

  vita2d_draw_texture_scale(crossImage,menuRect.x + 10, menuRect.y + menuRect.h - 40, 1,1);
  vita2d_font_draw_text(font, menuRect.x + 45, menuRect.y + menuRect.h - 20, RGBA8(helpTextR,helpTextG, helpTextB,fade), 20.0f, "Select");
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

void Menu::showCredits(vita2d_font *font)
{
  vita2d_draw_rectangle(160, 142, 640, 332, RGBA8(menuBGColorR,menuBGColorG,menuBGColorB, 100));
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
