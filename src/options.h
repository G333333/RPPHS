#ifndef _Options_Class
#define _Options_Class

#include"common.h"

#include"functions.h"

class Options {
private:
  vitaRect menuRect;
  vitaRect battery;
  int r,g,b;
  int status;
  int target, fade, barFade;
  bool leaveMenu;
  bool crossNeedsReset;
  bool circleNeedsReset;
  int menuPos;
  bool moveUp, moveDown, moveLeft, moveRight;
  bool quit;
  bool showFps, showCursor, showBattery;
  int cursorSetting, deadZone;
  double musicLevel, soundsLevel;
public:
  void init();
  void setAll(bool showFps, bool showCursor, bool showBattery, int cursorSetting, int deadZone, double musicLevel, double soundsLevel);
  void start();
  void doStuff(bool keys[15], int batteryPercent);
  void menuPartial();
  int getStatus();
  void setStatus(int status);
  bool getQuit();
  bool getShowFps();
  bool getShowCursor();
  bool getShowBattery();
  int getCursorSetting();
  int getDeadZone();
  double getMusicLevel();
  double getSoundsLevel();
};


#endif
