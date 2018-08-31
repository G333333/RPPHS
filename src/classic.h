 #ifndef _Classic_Class
#define _Classic_Class

#include <stdio.h>
#include <sstream>
#include <string.h>
#include <stdlib.h>

#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>

#include <vita2d.h>
#include "soloud.h"
#include "soloud_wav.h"
#include <psp2/audioout.h>

#include"functions.h"
#include"player.h"
#include"bullet.h"
#include"gary.h"
#include"karen.h"
#include"jeff.h"
#include"miniJeff.h"
#include"snakeGuy.h"
#include"particle.h"

class Classic {
private:
  int status;
  int points, multiplyer, killCount, mpUpgrade, bulletUpgrade, bulletInterval, bulletSetting, lifeUpgrade;
  vitaRect levelRect;
  bool quit;
  bool pause, startNeedsReset;
  Player player;
  int extraLives;
  Bullet bullets[100];
  Gary garys[20]; //104 total enemies seems to be the limit. garys + karens + jeffs + miniJeffs
  int garyTotal;
  Karen karens[10];
  int karenTotal;
  Jeff jeffs[10];
  int jeffTotal;
  MiniJeff miniJeffs[9];
  int miniJeffTotal;
  int snakeTotal;
  SnakeGuy snakeGuys[10];
  int bulletCounter;
  int bulletTimer;
  bool playGunSound, playExp;
  int safeTime, spawnTime;
  Particle bombParticles[100];
  int particleCount;
  bool bombReset;
  int bombCount;
  int bombUpgrade;
public:
  void init(double levelWidth, double levelHeight);
  void doStuff(vita2d_texture *gameBackground,
              vita2d_texture *playerImage,
              vita2d_texture *bulletImage,
              vita2d_texture *garyImage,
              vita2d_texture *karenImage,
              vita2d_texture *snakeImage1,
              vita2d_texture *snakeImage2,
              vita2d_texture *jeffImage,
              vita2d_texture *cursorCrosshair,
              vita2d_texture *cursorDuck,
              vita2d_texture *cursorWatcher,
              vita2d_texture *cursor1,
              vita2d_texture *cursor2,
              vita2d_texture *circleImage,
              vita2d_texture *triangleImage,
              vita2d_pgf *pgf,
              bool keys[15],
              double lx,
              double ly,
              double rx,
              double ry,
              int batteryPercent,
              bool showFps,
              bool showCursor,
              bool showBattery,
              int cursorSetting,
              int deadZone);
  int getStatus();
  void setStatus(int status);
  bool getQuit();
  void checkGarys();
  void spawnGary(int index);
  void checkKarens();
  void spawnKaren(int index);
  void checkJeffs();
  void spawnJeff(int index);
  void checkMiniJeffs();
  void checkSnakeGuys();
  void checkMap();

  void drawHud(vita2d_pgf * pgf, int batteryPercent, vita2d_texture *playerImage, bool showBattery, bool showFps);
  void drawCursor(vita2d_texture *cursorCrosshair,
                  vita2d_texture *cursorDuck,
                  vita2d_texture *cursorWatcher,
                  vita2d_texture *cursor1,
                  vita2d_texture *cursor2,
                  double rx, double ry, bool showCursor, int cursorSetting);

  bool playGun();
  bool getPlayExp();
  void pauseMenu(vita2d_pgf *pgf, vita2d_texture *circleImage, vita2d_texture *triangleImage);
  int getPoints();
  bool checkPlayer();
  void killPlayer();
  void spawnStuff();

  void gameOver(vita2d_pgf *pgf, vita2d_texture *triangleImage);

  void checkBomb();
  bool bombActive();
};

#endif
