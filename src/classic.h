 #ifndef _Classic_Class
#define _Classic_Class

#include"common.h"

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
  bool god;
  int status;
  int points, multiplyer, killCount, mpUpgrade, bulletUpgrade, bulletInterval, bulletSetting, lifeUpgrade;
  vitaRect levelRect;
  bool quit;
  bool pause, startNeedsReset;
  Player player;
  int extraLives;
  Bullet bullets[50];
  //Gary garys[40]; //104 total enemies seems to be the limit. garys + karens + jeffs + miniJeffs
  std::vector<Gary> garys;
  int garyTotal;
  int garysAlive;
  
  //Karen karens[10];
  std::vector<Karen> karens;
  int karenTotal;
  int karensAlive;

  //Jeff jeffs[10];
  std::vector<Jeff> jeffs;
  int jeffTotal;
  int jeffsAlive;
  
  //MiniJeff miniJeffs[9];
  std::vector<MiniJeff> miniJeffs;
  int miniJeffTotal;
  int miniJeffsAlive;
  
  std::vector<SnakeGuy> snakeGuys;
  int snakeTotal;
  int snakesAlive;
  //SnakeGuy snakeGuys[10];
  
  int bulletCounter;
  int bulletTimer;
  bool playGunSound, playExp;
  int safeTime, spawnTime;
  Particle bombParticles[10];
  int particleCount;
  bool bombReset;
  int bombCount;
  int bombUpgrade;

  //spawn events
  int eventTimer;
  bool garyEvent;
  bool jeffEvent;
public:
  void init(double levelWidth, double levelHeight);
  void doStuff(bool keys[15],
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
  void spawnGary(int index, int x = 0, int y = 0);
  void checkKarens();
  void spawnKaren(int index);
  void checkJeffs();
  void spawnJeff(int index, int x = 0, int y = 0);
  void checkMiniJeffs();
  void checkSnakeGuys();
  void checkMap();

  void drawHud(int batteryPercent, bool showBattery, bool showFps);
  void drawCursor(double rx, double ry, bool showCursor, int cursorSetting);

  bool playGun();
  bool getPlayExp();
  void pauseMenu();
  int getPoints();
  bool checkPlayer();
  void killPlayer();
  void spawnStuff();

  void gameOver();

  void checkBomb();
  bool bombActive();
};

#endif
