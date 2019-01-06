#ifndef _Intro_Class
#define _Intro_Class

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>

#include <vita2d.h>
#include "saveIcon.h"

class Intro{
private:
  SaveIcon saveIcon;
  SceCtrlData pad;
  bool crossNeedsReset;
  int introState;
  int introTimer;
  int letterCounter[3];
  vita2d_texture *g33Splash, *motoSplash;
  int fade;
public:
  Intro();
  void doIntro(vita2d_font *font);
  void introG33(vita2d_font *font);
  void introMoto(vita2d_font *font);
  void saveWarning(vita2d_font *font);
};

#endif
