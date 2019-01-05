#ifndef _Game_Class_
#define _Game_Class_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>       /* time */

#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/power.h>
#include <psp2/audioout.h>
#include <psp2/kernel/clib.h>

#include <vita2d.h>
#include "soloud.h"
#include "soloud_wav.h"
#include "soloud_wavstream.h"

#include"functions.h"
#include"intro.h"
#include"menu.h"
#include"options.h"
#include"classic.h"
#include"fpsCounter.h"
#include"saveScreen.h"
#include"saveIcon.h"
#include"highScores.h"

class Game {
private:
  bool quitGame;
  int status;
  int scores_int[10];
  std::string scores_str[10];
  double levelWidth, levelHeight;
  SceCtrlData pad;
	vita2d_font *font;
	vita2d_texture *garyImage;
  vita2d_texture *karenImage;
  vita2d_texture *jeffImage;
  vita2d_texture *snakeImage1;
  vita2d_texture *snakeImage2;
  vita2d_texture *gameBackground;
  vita2d_texture *playerImage;
  vita2d_texture *bulletImage;
  vita2d_texture *crossImage;
  vita2d_texture *circleImage;
  vita2d_texture *triangleImage;
  vita2d_texture *cursorCrosshair;
  vita2d_texture *cursorDuck;
  vita2d_texture *cursorWatcher;
  vita2d_texture *cursor1;
  vita2d_texture *cursor2;
  bool showFps, showCursor, showBattery;
  int cursorSetting, deadZone;
  double musicVol, soundVol;
  Intro intro;
  Menu menu;
  Options options;
  Classic classic;
  FpsCounter fpsCounter;
  bool keys[15];
  bool playingGameSound;

  SoLoud::Soloud gSoloud; // SoLoud engine
  SoLoud::Wav gWave;      // One wave file
  SoLoud::Wav exp1;
  SoLoud::WavStream OutThere;
  SoLoud::WavStream HeroImmortal;

  SaveScreen saveScreen;
  SaveIcon saveIcon;

  HighScores highScores;

public:
  void init();
  void loadFiles();
  void saveScores(int newScore, std::string newStr);
  bool checkScores(int newScore);
  void loadScores();
  void setDefaultScores();
  void loadSettings();
  void setSettings();
  void saveSettings();
  void doGame();
  void quit();
};


#endif
