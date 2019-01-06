#ifndef _Gary_Class_
#define _Gary_Class_

#include"common.h"
#include"functions.h"
#include"particle.h"

class Gary{
private:
  double xVel, yVel;
  vitaRect rect;
  bool active, spawning, pause;
  int spawnCount, spawnRadius;
  Particle particles[15];
public:
  void init();
  void spawn(vitaRect levelRect, int x = 0, int y = 0);
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
  void doStuff(vitaRect target, bool pause, vitaRect levelRect);
};

#endif
