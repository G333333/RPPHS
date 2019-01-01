#ifndef _Gary_Class_
#define _Gary_Class_

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
  void doStuff(vita2d_texture *garyImage, vitaRect target, bool pause, vitaRect levelRect);
};

#endif
