#ifndef _High_Scores_
#define _High_Scores_

#include"common.h"

#include"functions.h"

class HighScores {
private:
  vitaRect menuRect;
  vitaRect battery;
  int r,g,b;
  int status;
  int target, fade;
  bool leaveMenu;
  bool crossNeedsReset;
  bool goToMenu;
  int barFade;
public:
  void init();
  void start();
  void doStuff(bool keys[15], int batteryPercent, bool showBattery, int scores_int[10], std::string scores_str[10], int newScore);
  void menuPartial(int scores_int[10], std::string scores_str[10]);
  int getStatus();
  void setStatus(int status);
  bool getQuit();
};


#endif
