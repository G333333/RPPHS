#ifndef _Karen_Class_
#define _Karen_Class_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>       /* time */


#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>

#include <vita2d.h>

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
  void doStuff(vita2d_texture *karenImage, vitaRect levelRect, bool pause);
};

#endif
