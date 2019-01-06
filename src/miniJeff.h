#ifndef _Mini_Jeff_
#define _Mini_Jeff_

#include"common.h"

#include"functions.h"
#include"particle.h"

class MiniJeff {
private:
  double xVel, yVel;
  float rad;
  double angle;
  bool active;
  vitaRect rect;
  Particle particles[15];
  int safeTime;
public:
  void init();
  void spawn(vitaRect start, double angle);
  bool getActive();
  vitaRect getRect();
  void doStuff(bool pause, vitaRect levelRect);
  void moveBackX(double playerxVel);
  void moveBackY(double playeryVel);
  void die();
  int getSafeTime();
};

#endif
