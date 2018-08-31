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
public:
  Intro();
  void doIntro(vita2d_pgf *pgf);
};

#endif
