#ifndef _Menu_Class_
#define _Menu_Class_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>

#include <vita2d.h>

#include"functions.h"

class Menu {
private:
  vitaRect menuRect;
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
public:
  void init();
  void start();
  void doStuff(vita2d_texture *gameBackground, vita2d_texture *crossImage, vita2d_texture *circleImage, vita2d_font *font, bool keys[15], int batteryPercent, bool showBattery);
  void menuPartial(vita2d_texture *crossImage, vita2d_font *font);
  int getStatus();
  void setStatus(int status);
  bool getQuit();
  void showCredits(vita2d_texture *circleImage, vita2d_font *font);
};


#endif
