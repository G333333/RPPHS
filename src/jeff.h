#ifndef _Jeff_Class_
#define _Jeff_Class_

#include"common.h"

#include"functions.h"
#include"particle.h"

class Jeff{
private:
  double xVel, yVel;
  double speed, angle;
  int counter, wait;
  vitaRect rect, target, bigRect;
  bool active, spawning, pause;
  int spawnCount, spawnRadius;
  Particle particles[15];
public:
  void init();
  void spawn(vitaRect levelRect, int x = 0, int y = 0);
  void newTarget(vitaRect levelRect);
  void preSpawn();
  bool getSpawning();
  void die();
  vitaRect getRect();
  bool getActive();
  bool getParticlesActive();
  double getAngle();
  void moveX();
  void moveY();
  void moveBackX();
  void moveBackY();
  void moveBackX(double playerxVel);
  void moveBackY(double playeryVel);
  void doStuff(vitaRect levelRect, vitaRect playerRect, bool pause);
};

#endif
