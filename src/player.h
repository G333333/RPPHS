#ifndef _Player_Class
#define _Player_Class

#include"common.h"

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
  void doStuff(double lx, double ly, int deadZone, vitaRect levelRect, bool pause);
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
