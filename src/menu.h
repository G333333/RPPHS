#ifndef _Menu_Class_
#define _Menu_Class_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include"common.h"

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
  bool controls;
public:
  void init();
  void start();
  void doStuff(bool keys[15], bool showBattery);
  void menuPartial();
  int getStatus();
  void setStatus(int status);
  bool getQuit();
  void showCredits();
  void showControls();
};


#endif
