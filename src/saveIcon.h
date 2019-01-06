#ifndef _Save_Icon_
#define _Save_Icon_

#include"common.h"

class SaveIcon{
private:
  int timer;
  float rad;
  int x[10];
  int xVel[10];
public:
  SaveIcon();
  void doStuff(int xStart, int yStart);
  void start();
  int getTimer();
  void cleanUp();
};

#endif
