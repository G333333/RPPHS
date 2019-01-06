#include"saveScreen.h"

void SaveScreen::init(int points)
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

  moveUp = false;
  moveDown = false;
  moveLeft = false;
  moveRight = false;
  menuPos = 1;
  quit = false;

  crossNeedsReset = false;
  pos1 = pos2 = pos3 = 0;
  finalInput = "";
  this->points = points;
}

void SaveScreen::start(int points)
{
  moveUp = false;
  moveDown = false;

  menuPos = 1;

  crossNeedsReset = true;

  this->points = points;

  pos1 = 0;
  pos2 = 0;
  pos3 = 0;

  finalInput = "";
}

void SaveScreen::doStuff(vita2d_font *font, bool keys[15], int batteryPercent, bool showBattery)
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
    drawEmptyRect(battery, RGBA8(255, 255, 255, 255));
    vita2d_draw_rectangle(batteryTip.x, batteryTip.y, batteryTip.w, batteryTip.h, RGBA8(255, 255, 255, 255));
  }

  drawEmptyRect(960 / 2 - 960 / 4, 544 / 2 - 544 / 4 , 960 / 2, 544 / 2, RGBA8(0, 255, 0, 100));
  vita2d_draw_rectangle(960 / 2 - 960 / 4 + 1, 544 / 2 - 522 / 4 + 1, 960 / 2 - 1, 544 / 2 - 1, RGBA8(0, 0, 0, 100));

  vita2d_font_draw_text(font, 960 / 2 - vita2d_font_text_width(font, 20.0f, "New High Score! Please enter your initials.") / 2, 544 / 2, RGBA8(255,255,255,255), 20.0f, "New High Score! Please enter your initials.");

  vita2d_font_draw_textf(font, 960 / 2 - vita2d_font_text_width(font, 20.0f, "Current Score:") / 2, 544 / 2 + 20, RGBA8(255,255,255,255), 20.0f, "Current Score: %d", points);

  vita2d_font_draw_text(font, 960 / 2 - vita2d_font_text_width(font, 20.0f, "Current Score:") / 2 + 20, 544 / 2 + 40, RGBA8(255,255,255,255), 20.0f, letters[pos1].c_str());
  vita2d_font_draw_text(font, 960 / 2 - vita2d_font_text_width(font, 20.0f, "Current Score:") / 2 + 40, 544 / 2 + 40, RGBA8(255,255,255,255), 20.0f, letters[pos2].c_str());
  vita2d_font_draw_text(font, 960 / 2 - vita2d_font_text_width(font, 20.0f, "Current Score:") / 2 + 60, 544 / 2 + 40, RGBA8(255,255,255,255), 20.0f, letters[pos3].c_str());

  switch (menuPos) {
    case 1:
      vita2d_font_draw_text(font, 960 / 2 - vita2d_font_text_width(font, 20.0f, "Current Score:") / 2 + 20, 544 / 2 + 50, RGBA8(255,255,255,255), 20.0f, "_");
      break;
    case 2:
      vita2d_font_draw_text(font, 960 / 2 - vita2d_font_text_width(font, 20.0f, "Current Score:") / 2 + 40, 544 / 2 + 50, RGBA8(255,255,255,255), 20.0f, "_");
      break;
    case 3:
      vita2d_font_draw_text(font, 960 / 2 - vita2d_font_text_width(font, 20.0f, "Current Score:") / 2 + 60, 544 / 2 + 50, RGBA8(255,255,255,255), 20.0f, "_");
      break;
  }

  int tempWidth = vita2d_texture_get_width(crossImage); //get the width and height to draw in correct place.
  int tempHeight = vita2d_texture_get_height(crossImage); //both images are the same size. //used for text too

  //uh.. x = half the screen - 1/4 of the screen = edge of pause menu. draw image here. draw text to right of image.
  //y = half the screen plus 1/4 of screen = bottom edge of pause menu. draw image here. draw text here - image width - text tempWidth
  vita2d_font_draw_text(font, 960 / 2 - 960 / 4 + tempWidth + 10, 544 / 2 + 544 / 4 - 10, RGBA8(255,255,255,255), 20.0f, "Continue");

  vita2d_draw_texture_scale(crossImage, 960 / 2 - 960 / 4 + 10, 544 / 2 + 544 / 4 - tempHeight, 1, 1);

  finalInput = letters[pos1] + letters[pos2] + letters[pos3];

  /**quick reference:
    keys[0] = up;
    keys[1] = down;
    keys[2] = left;
    keys[3] = right;
    keys[4] = cross;
    keys[5] = square;
    keys[6] = triangle;
    keys[7] = circle;
    keys[8] = ly Up
    keys[9] = ly Down; **/ //these are not accurate.
  if(keys[0] && !moveUp)
  {
    switch (menuPos) {
      case 1:
        pos1++;
        break;
      case 2:
        pos2++;
        break;
      case 3:
        pos3++;
        break;
    }
    moveUp = true;
  }

  if(keys[1] && !moveDown)
  {
    switch (menuPos) {
      case 1:
        pos1--;
        break;
      case 2:
        pos2--;
        break;
      case 3:
        pos3--;
        break;
    }
    moveDown = true;
  }

  if((keys[2] && !moveLeft) || (keys[11] && !moveLeft))
  {
    menuPos--;
    moveLeft = true;
  }
  if(!keys[2] && !keys[11])
  {
    moveLeft = false;
  }

  if((keys[3] && !moveRight) || (keys[12] && !moveRight))
  {
    menuPos++;
    moveRight = true;
  }
  if(!keys[3] && !keys[12])
  {
      moveRight = false;
  }

  if(keys[4])
  {
    if(!crossNeedsReset)
    {
      status = 5;
    }
  }
  if(!keys[4])
  {
    crossNeedsReset = false;
  }

  if(keys[9] && !moveUp)
  {
    switch (menuPos) {
      case 1:
        pos1++;
        break;
      case 2:
        pos2++;
        break;
      case 3:
        pos3++;
        break;
    }
    moveUp = true;
  }
  else if(!keys[9] && !keys[0])
  {
    moveUp = false;
  }

  if(keys[8] & !moveDown)
  {
    switch (menuPos) {
      case 1:
        pos1--;
        break;
      case 2:
        pos2--;
        break;
      case 3:
        pos3--;
        break;
    }
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

  if(pos1 > 35)
  {
    pos1 = 0;
  }
  if(pos1 < 0)
  {
    pos1 = 35;
  }

  if(pos2 > 35)
  {
    pos2 = 0;
  }
  if(pos2 < 0)
  {
    pos2 = 35;
  }

  if(pos3 > 35)
  {
    pos3 = 0;
  }
  if(pos3 < 0)
  {
    pos3 = 35;
  }
}

int SaveScreen::getStatus()
{
  return status;
}

void SaveScreen::setStatus(int status)
{
  this->status = status;
}

std::string SaveScreen::getFinalInput()
{
  return finalInput;
}

int SaveScreen::getPoints()
{
  return points;
}
