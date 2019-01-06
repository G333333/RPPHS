#ifndef _Karen_Class_
#define _Karen_Class_

#include"common.h"

#include"functions.h"
#include"particle.h"

class Karen{
private:
  double xVel, yVel;
  int counter, wait;
  vitaRect rect, target;
  bool active, spawning, pause;
  int spawnCount, spawnRadius;
  Particle particles[15];
public:
  void init();
  void spawn(vitaRect levelRect);
  void newTarget(vitaRect levelRect);
  void preSpawn();
  bool getSpawning();
  void die();
  vitaRect getRect();
  bool getActive();
  bool getParticlesActive();
  void moveX();
  void moveY();
  void moveBackX();
  void moveBackY();
  void moveBackX(double playerxVel);
  void moveBackY(double playeryVel);
  void doStuff(vitaRect levelRect, bool pause);
};

#endif
