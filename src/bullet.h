#ifndef _Bullet_Class_
#define _Bullet_Class_

#include"common.h"
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
  void spawn(double angle, vitaRect start);
  bool getActive();
  void die();
  vitaRect getRect();
  void doStuff(vitaRect levelRect, vitaRect start, bool pause);
  void moveBackX(double playerXvel);
  void moveBackY(double playerYvel);
};

#endif
