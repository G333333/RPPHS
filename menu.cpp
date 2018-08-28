#include"menu.h"

void Menu::init()
{
  status = 1;

  menuRect.x = 966;
  menuRect.y = 150;
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

void Menu::doStuff(vita2d_texture *gameBackground, vita2d_texture *crossImage, vita2d_texture *circleImage, vita2d_pgf *pgf, bool keys[15], int batteryPercent, bool showBattery)
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
    //vita2d_pgf_draw_textf(pgf, battery.x + battery.w / 2 - 20, battery.y + battery.h / 2 + 10, RGBA8(0,0,255,255), 1.0f, "%d%%", batteryPercent);
    drawEmptyRect(battery, RGBA8(255, 255, 255, 255));
    vita2d_draw_rectangle(batteryTip.x, batteryTip.y, batteryTip.w, batteryTip.h, RGBA8(255, 255, 255, 255));
  }

  if(!credits)
  {
    vita2d_draw_rectangle(menuRect.x, menuRect.y, menuRect.w, menuRect.h, RGBA8(0, 0, 0, fade));
    drawEmptyRect(menuRect, RGBA8(0,255,0,fade));

    switch (menuPos) {
      case 1:
        vita2d_draw_rectangle(menuRect.x + 1, menuRect.y + 15, menuRect.w - 1, 50, RGBA8(0, 255, 0, barFade));
        break;
      case 2:
        vita2d_draw_rectangle(menuRect.x + 1, menuRect.y + 65, menuRect.w - 1, 50, RGBA8(0, 255, 0, barFade));
        break;
      case 3:
        vita2d_draw_rectangle(menuRect.x + 1, menuRect.y + 115, menuRect.w - 1, 50, RGBA8(0, 255, 0, barFade));
        break;
    }
    vita2d_pgf_draw_text(pgf, menuRect.x + 10, menuRect.y + 50, RGBA8(255,255,255,fade), 1.5f, "Play");
    vita2d_pgf_draw_text(pgf, menuRect.x + 10, menuRect.y + 100, RGBA8(255,255,255,fade), 1.5f, "Options");
    vita2d_pgf_draw_text(pgf, menuRect.x + 10, menuRect.y + 150, RGBA8(255,255,255,fade), 1.5f, "quit");

    vita2d_draw_texture_scale(crossImage,menuRect.x + 10, menuRect.y + menuRect.h - 40, 1,1);
    vita2d_pgf_draw_text(pgf, menuRect.x + 45, menuRect.y + menuRect.h - 20, RGBA8(0,255, 0, 255), 1.0f, "Select");

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

    if(menuPos > 3)
    {
      menuPos = 1;
    }
    if(menuPos < 1)
    {
      menuPos = 3;
    }
    if(keys[14])
    {
      credits = true;
    }
  }
  else if(credits)
  {
    showCredits(circleImage, pgf);
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

void Menu::menuPartial(vita2d_texture *crossImage, vita2d_pgf *pgf)
{
  vita2d_draw_rectangle(menuRect.x, menuRect.y, menuRect.w, menuRect.h, RGBA8(0, 0, 0, fade));
  drawEmptyRect(menuRect, RGBA8(0,255,0,fade));

  switch (menuPos) {
    case 1:
      vita2d_draw_rectangle(menuRect.x + 1, menuRect.y + 15, menuRect.w - 1, 50, RGBA8(0, 255, 0, barFade));
      break;
    case 2:
      vita2d_draw_rectangle(menuRect.x + 1, menuRect.y + 65, menuRect.w - 1, 50, RGBA8(0, 255, 0, barFade));
      break;
    case 3:
      vita2d_draw_rectangle(menuRect.x + 1, menuRect.y + 115, menuRect.w - 1, 50, RGBA8(0, 255, 0, barFade));
      break;
  }
  vita2d_pgf_draw_text(pgf, menuRect.x + 10, menuRect.y + 50, RGBA8(255,255,255,fade), 1.5f, "Play");
  vita2d_pgf_draw_text(pgf, menuRect.x + 10, menuRect.y + 100, RGBA8(255,255,255,fade), 1.5f, "Options");
  vita2d_pgf_draw_text(pgf, menuRect.x + 10, menuRect.y + 150, RGBA8(255,255,255,fade), 1.5f, "quit");

  vita2d_draw_texture_scale(crossImage,menuRect.x + 10, menuRect.y + menuRect.h - 40, 1,1);
  vita2d_pgf_draw_text(pgf, menuRect.x + 45, menuRect.y + menuRect.h - 20, RGBA8(0,255, 0, 255), 1.0f, "Select");
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

void Menu::showCredits(vita2d_texture *circleImage, vita2d_pgf *pgf)
{
  vita2d_draw_rectangle(960 / 2 - 960 / 4 - 80 + 1, 544 / 2 - 522 / 4 + 1, 960 - 319, 544 / 2 + 60 - 1, RGBA8(0, 0, 0, 100));
  drawEmptyRect(960 / 2 - 960 / 4 - 80, 544 / 2 - 544 / 4 , 960 - 320, 544 / 2 + 60, RGBA8(0, 255, 0, 100));

  vita2d_pgf_draw_text(pgf, 160 + 5, 544 / 3 - 10, RGBA8(255,255,255,255), 0.9f, "Credits:");
  vita2d_pgf_draw_text(pgf, 160 + 5, 544 / 3 + 10, RGBA8(255,255,255,255), 0.9f, "G33 - Programming - Design");
  vita2d_pgf_draw_text(pgf, 160 + 5, 544 / 3 + 30, RGBA8(255,255,255,255), 0.9f, "MotoLegacy - Player/Enemy/Icon Images - Design");
  vita2d_pgf_draw_text(pgf, 160 + 5, 544 / 3 + 60, RGBA8(255,255,255,255), 0.9f, "Special Thanks:");
  vita2d_pgf_draw_text(pgf, 160 + 5, 544 / 3 + 80, RGBA8(255,255,255,255), 0.9f, "Xerpi - LibVita2d");
  vita2d_pgf_draw_text(pgf, 160 + 5, 544 / 3 + 100, RGBA8(255,255,255,255), 0.9f, "Xyz - SoLoud Ps Vita port");
  vita2d_pgf_draw_text(pgf, 160 + 5, 544 / 3 + 120, RGBA8(255,255,255,255), 0.9f, "Rinnegatamante - Frame Counter Code");
  vita2d_pgf_draw_text(pgf, 160 + 5, 544 / 3 + 140, RGBA8(255,255,255,255), 0.9f, "Every one that contributed to the Vita Sdk");
  vita2d_pgf_draw_text(pgf, 160 + 5, 544 / 3 + 160, RGBA8(255,255,255,255), 0.9f, "Ivan voirol @ opengameart.org - Background images");
  vita2d_pgf_draw_text(pgf, 160 + 5, 544 / 3 + 180, RGBA8(255,255,255,255), 0.9f, "yd @ opengameart.org - Outhere.ogg - Menu Music");
  vita2d_pgf_draw_text(pgf, 160 + 5, 544 / 3 + 200, RGBA8(255,255,255,255), 0.9f, "Trevor Lentz @ opengameart.org - HeroImmortal.ogg - Game Music");


  int tempWidth = vita2d_texture_get_width(circleImage); //get the width and height to draw in correct place.
  int tempHeight = vita2d_texture_get_height(circleImage); //both images are the same size. //used for text too

  vita2d_pgf_draw_text(pgf, 160 + tempWidth + 10, 544 / 2 + 544 / 4 + 40, RGBA8(255,255,255,255), 0.9f, "Main Menu");

  vita2d_draw_texture_scale(circleImage, 160 + 5, 544 / 2 + 544 / 4 + 45 - tempHeight, 1, 1);
}
