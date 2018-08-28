#ifndef _Save_Icon_
#define _Save_Icon_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>

#include <vita2d.h>

class SaveIcon{
private:
  int timer;
  float rad;
  int x[10];
  int xVel[10];
  vita2d_texture *saveImage;
public:
  SaveIcon();
  void doStuff(int xStart, int yStart);
  void start();
  int getTimer();
  void cleanUp();
};

#endif
