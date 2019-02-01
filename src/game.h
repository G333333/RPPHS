#ifndef _Game_Class_
#define _Game_Class_

#include "common.h"
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
  int status;
  int scores_int[10];
  std::string scores_str[10];
  double levelWidth, levelHeight;
  SceCtrlData pad;
  
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
