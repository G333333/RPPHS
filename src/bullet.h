#ifndef _Bullet_Class_
#define _Bullet_Class_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>

#include <vita2d.h>

#include"functions.h"
#include"player.h"
#include"particle.h"

class Bullet {
private:
  double xVel, yVel;
  float rad;
  double angle;
  bool active;
  vitaRect rect;
  Particle particles[1];
public:
  void init();
  void spawn(double rx, double ry, vitaRect start);
  bool getActive();
  void die();
  vitaRect getRect();
  void doStuff(vita2d_texture *bulletImage, vitaRect levelRect, vitaRect start, bool pause);
  void moveBackX(double playerXvel);
  void moveBackY(double playerYvel);
};

#endif
