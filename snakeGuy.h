#ifndef _Snake_Guy_
#define _Snake_Guy_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>       /* time */


#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/kernel/clib.h>

#include <vita2d.h>

#include"functions.h"
#include"particle.h"

class SnakeGuy{
private:
  vitaRect rect1, rect2, rect3, rect4, rect5, rect6, rect7, rect8;
  bool rect1Active, rect2Active, rect3Active, rect4Active, rect5Active, rect6Active, rect7Active, rect8Active;
  bool spawning, pause;
  int spawnCount, spawnRadius;
  int moveInterval, head;
  Particle particles[15];
public:
  void init();
  void spawn(vitaRect levelRect);
  void preSpawn();
  bool getSpawning();
  void die();
  vitaRect getRect1();
  vitaRect getRect2();
  vitaRect getRect3();
  vitaRect getRect4();
  vitaRect getRect5();
  vitaRect getRect6();
  vitaRect getRect7();
  vitaRect getRect8();
  bool getActive();
  bool getParticlesActive();
  int chooseDirection(vitaRect target);
  void move(vitaRect target, int choice = 6);
  void moveRect1(vitaRect start, int choice);
  void moveRect2(vitaRect start, int choice);
  void moveRect3(vitaRect start, int choice);
  void moveRect4(vitaRect start, int choice);
  void moveRect5(vitaRect start, int choice);
  void moveRect6(vitaRect start, int choice);
  void moveRect7(vitaRect start, int choice);
  void moveRect8(vitaRect start, int choice);
  void moveBackX();
  void moveBackY();
  void moveBackX(double playerxVel);
  void moveBackY(double playeryVel);
  int newHead();
  bool takeDamage(vitaRect bullet, vitaRect target);
  bool hit(vitaRect bullet);
  void doStuff(vitaRect target, bool pause, vita2d_texture *snakeImage1, vita2d_texture *snakeImage2);
};

#endif
