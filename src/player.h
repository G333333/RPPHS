#ifndef _Player_Class
#define _Player_Class

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>

#include <vita2d.h>

#include"functions.h"

class Player{
private:
  vitaRect rect;
  double xVel;
  double yVel;
  float rad;
  bool active;
public:
  void init();
  void doStuff(vita2d_texture *playerImage, double lx, double ly, int deadZone, vitaRect levelRect, bool pause);
  vitaRect getRect();
  bool getActive();
  void setxVel(double xVel);
  void setyVel(double yVel);
  double getxVel();
  double getyVel();
  void moveBackX();
  void moveBackY();
  void die();
  void spawn();
};
#endif
