#include"options.h"

void Options::init()
{
  status = 3;

  menuRect.x = -255;
  menuRect.y = 22;
  menuRect.w = 255;
  menuRect.h = 500;

  battery.x = 856;
  battery.y = 40;
  battery.w = 52;
  battery.h = 15;
  r = b = g = 0;

  target = -255;
  barFade = 0 - menuRect.w;
  fade = 0;

  moveUp = false;
  moveDown = false;
  moveLeft = false;
  moveRight = false;
  menuPos = 1;
  quit = false;

  crossNeedsReset = false;
  circleNeedsReset = false;

  showFps = true;
  showCursor = true;
  showBattery = true;
  cursorSetting = 1;
  deadZone = 12;
  musicLevel = 5.0;
  soundsLevel = 5.0;
}

void Options::setAll(bool showFps, bool showCursor, bool showBattery, int cursorSetting, int deadZone, double musicLevel, double soundsLevel)
{
  this->showFps = showFps;
  this->showCursor = showCursor;
  this->showBattery = showBattery;
  this->cursorSetting = cursorSetting;
  this->deadZone = deadZone;
  this->musicLevel = musicLevel;
  this->soundsLevel = soundsLevel;
}

void Options::start()
{
  target = 0;
  //barFade = 0;
  //fade = 0;

  moveUp = false;
  moveDown = false;

  menuPos = 1;

  crossNeedsReset = true;
  circleNeedsReset = true;
}

void Options::doStuff(bool keys[15], int batteryPercent)
{
  //make sure things don't go out of bounds. like deadZone
  if(cursorSetting < 1)
  {
    cursorSetting = 5;
  }
  if(cursorSetting > 5)
  {
    cursorSetting = 1;
  }

  if(deadZone < 10)
  {
    deadZone = 10;
  }
  if(deadZone > 50)
  {
    deadZone = 50;
  }

  if(musicLevel < 0.0)
  {
    musicLevel = 0.0;
  }
  if(musicLevel > 20.0)
  {
    musicLevel = 20.0;
  }

  if(soundsLevel < 0.0)
  {
    soundsLevel = 0.0;
  }
  if(soundsLevel > 10.0)
  {
    soundsLevel = 10.0;
  }

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
    case 6:
      vita2d_draw_rectangle(menuRect.x + 1, menuRect.y + 250, menuRect.w - 1, 50, RGBA8(menuBarColorR,menuBarColorG,menuBarColorB, barFade));
      break;
    case 7:
      vita2d_draw_rectangle(menuRect.x + 1, menuRect.y + 300, menuRect.w - 1, 50, RGBA8(menuBarColorR, menuBarColorG,menuBarColorB, barFade));
      break;
    case 8:
      vita2d_draw_rectangle(menuRect.x + 1, menuRect.y + 350, menuRect.w - 1, 50, RGBA8(menuBarColorR,menuBarColorG,menuBarColorB, barFade));
      break;
  }

  int tempWidth = 0; //used to calculate the space needed for the text that changes
  if(showFps)
  {
    tempWidth = vita2d_font_text_width(font, 20.0f, "< Yes >");
    vita2d_font_draw_text(font, menuRect.x + menuRect.w - tempWidth - 5, menuRect.y + 30, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "< Yes >");
    vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 30, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Show Fps:");
  }
  else
  {
    tempWidth = vita2d_font_text_width(font, 20.0f, "< No >");
    vita2d_font_draw_text(font, menuRect.x + menuRect.w - tempWidth - 5, menuRect.y + 30, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "< No >");
    vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 30, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Show Fps:");
  }

  if(showCursor)
  {
    tempWidth = vita2d_font_text_width(font, 20.0f, "< Yes >");
    vita2d_font_draw_text(font, menuRect.x + menuRect.w - tempWidth - 5, menuRect.y + 80, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "< Yes >");
    vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 80, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Show Cursor");
  }
  else
  {
    tempWidth = vita2d_font_text_width(font, 20.0f, "< No >");
    vita2d_font_draw_text(font, menuRect.x + menuRect.w - tempWidth - 5, menuRect.y + 80, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "< No >");
    vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 80, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Show Cursor");
  }
  if(showBattery)
  {
    tempWidth = vita2d_font_text_width(font, 20.0f, "< Yes >");
    vita2d_font_draw_text(font, menuRect.x + menuRect.w - tempWidth - 5, menuRect.y + 130, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "< Yes >");
    vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 130, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Show Battery:");
  }
  else
  {
    tempWidth = vita2d_font_text_width(font, 20.0f, "< No >");
    vita2d_font_draw_text(font, menuRect.x + menuRect.w - tempWidth - 5, menuRect.y + 130, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "< No >");
    vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 130, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Show Battery:");
  }

  /**
    1 = crosshair
    2 =  cursorDuck
    3 = cursorWatcher
    4 = cursor1 = circle
    5 = finger **/
  switch (cursorSetting) {
    case 1:
      tempWidth = vita2d_font_text_width(font, 20.0f, "< Crosshair >");
      vita2d_font_draw_text(font, menuRect.x + menuRect.w - tempWidth - 5, menuRect.y + 180, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "< Crosshair >");
      vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 180, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Cursor:");
      break;
    case 2:
      tempWidth = vita2d_font_text_width(font, 20.0f, "< Duck >");
      vita2d_font_draw_text(font, menuRect.x + menuRect.w - tempWidth - 5, menuRect.y + 180, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "< Duck >");
      vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 180, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Cursor:");
      break;
    case 3:
      tempWidth = vita2d_font_text_width(font, 20.0f, "< Watcher? >");
      vita2d_font_draw_text(font, menuRect.x + menuRect.w - tempWidth - 5, menuRect.y + 180, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "< Watcher? >");
      vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 180, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Cursor:");
      break;
    case 4:
      tempWidth = vita2d_font_text_width(font, 20.0f, "< Crosshair 2 >");
      vita2d_font_draw_text(font, menuRect.x + menuRect.w - tempWidth - 5, menuRect.y + 180, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "< Crosshair 2 >");
      vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 180, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Cursor:");
      break;
    case 5:
      tempWidth = vita2d_font_text_width(font, 20.0f, "< Finger >");
      vita2d_font_draw_text(font, menuRect.x + menuRect.w - tempWidth - 5, menuRect.y + 180, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "< Finger >");
      vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 180, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Cursor:");
      break;
  }

  vita2d_font_draw_textf(font, menuRect.x + 10, menuRect.y + 230, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Deadzone: %d", deadZone);
  vita2d_draw_rectangle(menuRect.x + menuRect.w - 60, menuRect.y + 215, 50, 20, RGBA8(mainTextR,mainTextG,mainTextB,fade));
  int r = 0;
  int g = 255;
  int b = 0;
  for(int i = 0; i < deadZone; i++)
  {
    vita2d_draw_line(menuRect.x + menuRect.w - 59 + i, menuRect.y + 216, menuRect.x + menuRect.w - 59 + i, menuRect.y + 234, RGBA8(r, g, b, 255));
    r += 5;
    g -= 5;
    if(r > 255)
    {
      r = 255;
    }
    if(r < 0)
    {
      r = 0;
    }
    if(g > 255)
    {
      g = 255;
    }
    if(g < 0)
    {
      g = 0;
    }
  }

  vita2d_font_draw_textf(font, menuRect.x + 10, menuRect.y + 280, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Music: %.0lf", musicLevel);
  vita2d_draw_rectangle(menuRect.x + menuRect.w - 60, menuRect.y + 260, 50, 20, RGBA8(mainTextR,mainTextG,mainTextB,fade));
  r = 0;
  g = 255;
  b = 0;
  for(double i = 0; i < musicLevel * 5.0; i += 1.0)
  {
    vita2d_draw_line(menuRect.x + menuRect.w - 59 + i, menuRect.y + 261, menuRect.x + menuRect.w - 59 + i, menuRect.y + 279, RGBA8(r, g, b, 255));
    r += 5;
    g -= 5;
    if(r > 255)
    {
      r = 255;
    }
    if(r < 0)
    {
      r = 0;
    }
    if(g > 255)
    {
      g = 255;
    }
    if(g < 0)
    {
      g = 0;
    }
  }

  vita2d_font_draw_textf(font, menuRect.x + 10, menuRect.y + 330, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Sounds: %.0lf", soundsLevel);
  vita2d_draw_rectangle(menuRect.x + menuRect.w - 60, menuRect.y + 315, 50, 20, RGBA8(mainTextR,mainTextG,mainTextB,fade));
  r = 0;
  g = 255;
  b = 0;
  for(double i = 0; i < soundsLevel * 5.0; i += 1.0)
  {
    vita2d_draw_line(menuRect.x + menuRect.w - 59 + i, menuRect.y + 316, menuRect.x + menuRect.w - 59 + i, menuRect.y + 334, RGBA8(r, g, b, 255));
    r += 5;
    g -= 5;
    if(r > 255)
    {
      r = 255;
    }
    if(r < 0)
    {
      r = 0;
    }
    if(g > 255)
    {
      g = 255;
    }
    if(g < 0)
    {
      g = 0;
    }
  }

  vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 380, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Theme");
  
  tempWidth = vita2d_font_text_width(font, 20.0f, themes[theme].c_str());
  vita2d_font_draw_text(font, menuRect.x + menuRect.w - tempWidth - 5, menuRect.y + 380, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, themes[theme].c_str());
  
  vita2d_draw_texture_scale(circleImage ,menuRect.x + 10, menuRect.y + menuRect.h - 40, 1,1);
  vita2d_font_draw_text(font, menuRect.x + 45, menuRect.y + menuRect.h - 17, RGBA8(helpTextR,helpTextG, helpTextB, 255), 20.0f, "Return");
  
  if(menuRect.x < target)
  {
    menuRect.x += 10;
    if(fade < 240)
    {
      fade += 10;
      barFade += 4;
    }
  }
  if(menuRect.x > target)
  {
    menuRect.x -= 10;
    if(fade > 10)
    {
      fade -= 10;
      barFade -= 4;
    }
  }
  if(menuRect.x <= target && target == 0 - menuRect.w && menuPos == 1)
  {
    //status = 2;
  }

  /**quick reference:
    keys[0] = up;
    keys[1] = down;
    keys[2] = left;
    keys[3] = right;
    keys[4] = cross;
    keys[5] = circle;
    keys[6] = triangle;
    keys[7] = square;
    keys[8] = ly Up
    keys[9] = ly Down; **/
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

  if((keys[2] && !moveLeft) || (keys[11] && !moveLeft))
  {
    moveLeft = true;
    switch (menuPos) {
      case 1:
        if(showFps)
        {
          showFps = false;
        }
        else
        {
          showFps = true;
        }
        break;
      case 2:
        if(showCursor)
        {
          showCursor = false;
        }
        else
        {
          showCursor = true;
        }
        break;
      case 3:
        if(showBattery)
        {
          showBattery = false;
        }
        else
        {
          showBattery = true;
        }
        break;
      case 4:
        cursorSetting--;
        break;
      case 5:
        deadZone--;
        break;
      case 6:
        musicLevel -= 1.0;
        break;
      case 7:
        soundsLevel -= 1.0;
        break;
      case 8:
        theme--;
        if(theme < 0) theme = themeCount - 1;
        changeTheme = true;
        break;
    }
  }
  if(!keys[2] && !keys[11])
  {
    moveLeft = false;
  }

  if((keys[3] && !moveRight) || (keys[12] && !moveRight))
  {
    moveRight = true;
    switch (menuPos) {
      case 1:
        if(showFps)
        {
          showFps = false;
        }
        else
        {
          showFps = true;
        }
        break;
      case 2:
        if(showCursor)
        {
          showCursor = false;
        }
        else
        {
          showCursor = true;
        }
        break;
      case 3:
        if(showBattery)
        {
          showBattery = false;
        }
        else
        {
          showBattery = true;
        }
        break;
      case 4:
        cursorSetting++;
        break;
      case 5:
        deadZone++;
        break;
      case 6:
        musicLevel += 1.0;
        break;
      case 7:
        soundsLevel += 1.0;
        break;
      case 8:
        theme++;
        if(theme > themeCount - 1) theme = 0;
        changeTheme = true;
        break;
    }
  }
  if(!keys[3] && !keys[12])
  {
    moveRight = false;
  }

  if(keys[4])
  {
    if(!crossNeedsReset)
    {

    }
  }
  if(!keys[4])
  {
    crossNeedsReset = false;
  }

  if(keys[5] && !circleNeedsReset)
  {
    target = 0 - menuRect.w;
    status = 1;
    circleNeedsReset = true;
  }

  else if(!keys[5])
  {
    circleNeedsReset = false;
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

  if(menuPos > 8)
  {
    menuPos = 1;
  }
  if(menuPos < 1)
  {
    menuPos = 8;
  }
}

void Options::menuPartial()
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
    case 6:
      vita2d_draw_rectangle(menuRect.x + 1, menuRect.y + 250, menuRect.w - 1, 50, RGBA8(menuBarColorR,menuBarColorG,menuBarColorB, barFade));
      break;
    case 7:
      vita2d_draw_rectangle(menuRect.x + 1, menuRect.y + 300, menuRect.w - 1, 50, RGBA8(menuBarColorR,menuBarColorG,menuBarColorB, barFade));
      break;
    case 8:
      vita2d_draw_rectangle(menuRect.x + 1, menuRect.y + 350, menuRect.w - 1, 50, RGBA8(menuBarColorR,menuBarColorG,menuBarColorB, barFade));
      break;
  }

  int tempWidth = 0; //used to calculate the space needed for the text that changes
  if(showFps)
  {
    tempWidth = vita2d_font_text_width(font, 20.0f, "< Yes >");
    vita2d_font_draw_text(font, menuRect.x + menuRect.w - tempWidth - 5, menuRect.y + 30, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "< Yes >");
    vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 30, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Show Fps:");
  }
  else
  {
    tempWidth = vita2d_font_text_width(font, 20.0f, "< No >");
    vita2d_font_draw_text(font, menuRect.x + menuRect.w - tempWidth - 5, menuRect.y + 30, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "< No >");
    vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 30, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Show Fps:");
  }

  if(showCursor)
  {
    tempWidth = vita2d_font_text_width(font, 20.0f, "< Yes >");
    vita2d_font_draw_text(font, menuRect.x + menuRect.w - tempWidth - 5, menuRect.y + 80, RGBA8(255,255,255,fade), 20.0f, "< Yes >");
    vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 80, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Show Cursor");
  }
  else
  {
    tempWidth = vita2d_font_text_width(font, 20.0f, "< No >");
    vita2d_font_draw_text(font, menuRect.x + menuRect.w - tempWidth - 5, menuRect.y + 80, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "< No >");
    vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 80, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Show Cursor");
  }
  if(showBattery)
  {
    tempWidth = vita2d_font_text_width(font, 20.0f, "< Yes >");
    vita2d_font_draw_text(font, menuRect.x + menuRect.w - tempWidth - 5, menuRect.y + 130, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "< Yes >");
    vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 130, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Show Battery:");
  }
  else
  {
    tempWidth = vita2d_font_text_width(font, 20.0f, "< No >");
    vita2d_font_draw_text(font, menuRect.x + menuRect.w - tempWidth - 5, menuRect.y + 130, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "< No >");
    vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 130, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Show Battery:");
  }

  /**
    1 = crosshair
    2 =  cursorDuck
    3 = cursorWatcher
    4 = cursor1 = circle
    5 = finger **/
  switch (cursorSetting) {
    case 1:
      tempWidth = vita2d_font_text_width(font, 20.0f, "< Crosshair >");
      vita2d_font_draw_text(font, menuRect.x + menuRect.w - tempWidth - 5, menuRect.y + 180, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "< Crosshair >");
      vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 180, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Cursor:");
      break;
    case 2:
      tempWidth = vita2d_font_text_width(font, 20.0f, "< Duck >");
      vita2d_font_draw_text(font, menuRect.x + menuRect.w - tempWidth - 5, menuRect.y + 180, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "< Duck >");
      vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 180, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Cursor:");
      break;
    case 3:
      tempWidth = vita2d_font_text_width(font, 20.0f, "< Watcher? >");
      vita2d_font_draw_text(font, menuRect.x + menuRect.w - tempWidth - 5, menuRect.y + 180, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "< Watcher? >");
      vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 180, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Cursor:");
      break;
    case 4:
      tempWidth = vita2d_font_text_width(font, 20.0f, "< Crosshair 2 >");
      vita2d_font_draw_text(font, menuRect.x + menuRect.w - tempWidth - 5, menuRect.y + 180, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "< Crosshair 2 >");
      vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 180, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Cursor:");
      break;
    case 5:
      tempWidth = vita2d_font_text_width(font, 20.0f, "< Finger >");
      vita2d_font_draw_text(font, menuRect.x + menuRect.w - tempWidth - 5, menuRect.y + 180, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "< Finger >");
      vita2d_font_draw_text(font, menuRect.x + 10, menuRect.y + 180, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Cursor:");
      break;
  }

  vita2d_font_draw_textf(font, menuRect.x + 10, menuRect.y + 230, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Deadzone: %d", deadZone);
  vita2d_draw_rectangle(menuRect.x + menuRect.w - 60, menuRect.y + 215, 50, 20, RGBA8(mainTextR,mainTextG,mainTextB,fade));
  int r = 0;
  int g = 255;
  int b = 0;
  for(int i = 0; i < deadZone; i++)
  {
    vita2d_draw_line(menuRect.x + menuRect.w - 59 + i, menuRect.y + 216, menuRect.x + menuRect.w - 59 + i, menuRect.y + 234, RGBA8(r, g, b, 255));
    r += 5;
    g -= 5;
    if(r > 255)
    {
      r = 255;
    }
    if(r < 0)
    {
      r = 0;
    }
    if(g > 255)
    {
      g = 255;
    }
    if(g < 0)
    {
      g = 0;
    }
  }

  vita2d_font_draw_textf(font, menuRect.x + 10, menuRect.y + 280,  RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Music: %.0lf", musicLevel);
  vita2d_draw_rectangle(menuRect.x + menuRect.w - 60, menuRect.y + 260, 50, 20,  RGBA8(mainTextR,mainTextG,mainTextB,fade));
  r = 0;
  g = 255;
  b = 0;
  for(double i = 0; i < musicLevel * 5.0; i += 1.0)
  {
    vita2d_draw_line(menuRect.x + menuRect.w - 59 + i, menuRect.y + 261, menuRect.x + menuRect.w - 59 + i, menuRect.y + 279, RGBA8(r, g, b, 255));
    r += 5;
    g -= 5;
    if(r > 255)
    {
      r = 255;
    }
    if(r < 0)
    {
      r = 0;
    }
    if(g > 255)
    {
      g = 255;
    }
    if(g < 0)
    {
      g = 0;
    }
  }

  vita2d_font_draw_textf(font, menuRect.x + 10, menuRect.y + 330, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, "Sounds: %.0lf", soundsLevel);
  vita2d_draw_rectangle(menuRect.x + menuRect.w - 60, menuRect.y + 315, 50, 20, RGBA8(mainTextR,mainTextG,mainTextB,fade));
  r = 0;
  g = 255;
  b = 0;
  for(double i = 0; i < soundsLevel * 5.0; i += 1.0)
  {
    vita2d_draw_line(menuRect.x + menuRect.w - 59 + i, menuRect.y + 316, menuRect.x + menuRect.w - 59 + i, menuRect.y + 334, RGBA8(r, g, b, 255));
    r += 5;
    g -= 5;
    if(r > 255)
    {
      r = 255;
    }
    if(r < 0)
    {
      r = 0;
    }
    if(g > 255)
    {
      g = 255;
    }
    if(g < 0)
    {
      g = 0;
    }
  }

  tempWidth = vita2d_font_text_width(font, 20.0f, themes[theme].c_str());
  vita2d_font_draw_text(font, menuRect.x + menuRect.w - tempWidth - 5, menuRect.y + 380, RGBA8(mainTextR,mainTextG,mainTextB,fade), 20.0f, themes[theme].c_str());
  
  vita2d_draw_texture_scale(circleImage ,menuRect.x + 10, menuRect.y + menuRect.h - 40, 1,1);
  vita2d_font_draw_text(font, menuRect.x + 45, menuRect.y + menuRect.h - 17, RGBA8(helpTextR,helpTextG, helpTextB, 255), 20.0f, "Return");
  if(menuRect.x < target)
  {
    menuRect.x += 10;
    if(fade < 240)
    {
      fade += 10;
      barFade += 4;
    }
  }
  if(menuRect.x > target)
  {
    menuRect.x -= 10;
    if(fade > 10)
    {
      fade -= 10;
      barFade -= 4;
    }
  }
}

int Options::getStatus()
{
  return status;
}

void Options::setStatus(int status)
{
  this->status = status;
}

bool Options::getQuit()
{
  return quit;
}

bool Options::getShowFps()
{
  return showFps;
}

bool Options::getShowCursor()
{
  return showCursor;
}

bool Options::getShowBattery()
{
  return showBattery;
}

int Options::getCursorSetting()
{
  return cursorSetting;
}

int Options::getDeadZone()
{
  return deadZone;
}

double Options::getMusicLevel()
{
  return musicLevel / 10.0;
}

double Options::getSoundsLevel()
{
  return soundsLevel / 10.0;
}
