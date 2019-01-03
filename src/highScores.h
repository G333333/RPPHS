#ifndef _High_Scores_
#define _High_Scores_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>

#include <vita2d.h>

#include"functions.h"

class HighScores {
private:
  vitaRect menuRect;
  vitaRect battery;
  int r,g,b;
  int status;
  int target, fade;
  bool leaveMenu;
  bool crossNeedsReset;
  bool goToMenu;
  int barFade;
public:
  void init();
  void start();
  void doStuff(vita2d_texture *gameBackground, vita2d_texture *crossImage, vita2d_texture *circleImage, vita2d_font *font, bool keys[15], int batteryPercent, bool showBattery, int scores_int[10], std::string scores_str[10], int newScore);
  void menuPartial(vita2d_texture *crossImage, vita2d_texture *circleImage, vita2d_font *font, int scores_int[10], std::string scores_str[10]);
  int getStatus();
  void setStatus(int status);
  bool getQuit();
};


#endif
