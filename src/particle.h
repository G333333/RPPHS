#ifndef _Particle_Class_
#define _Particle_Class_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>

#include <vita2d.h>

#include"functions.h"
#include"player.h"

class Particle {
private:
  double xVel, yVel;
  double angle;
  bool active;
  vitaRect rect;
  int tx, ty;
  int lifeSpan;
public:
  void init(int w = 4, int h = 4);
  void spawn(vitaRect start, int tempSpeed, int tempLife);
  bool getActive();
  vitaRect getRect();
  void doStuff(vitaRect start, unsigned int color, bool pause);
  void moveBackX(double playerXvel);
  void moveBackY(double playerYvel);
};

#endif
