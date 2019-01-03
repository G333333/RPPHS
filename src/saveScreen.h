#ifndef _Save_Screen_
#define _Save_Screen_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>

#include <vita2d.h>

#include"functions.h"

class SaveScreen {
private:
  vitaRect menuRect;
  vitaRect battery;
  int r,g,b;
  int status;
  bool crossNeedsReset;
  int menuPos;
  bool moveUp, moveDown, moveLeft, moveRight;
  bool quit;
  std::string letters[36] = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","0","1","2","3","4","5","6","7","8","9"};
  int pos1, pos2, pos3;
  std::string finalInput;
  int points;
public:
  void init(int points);
  void start(int points);
  void doStuff(vita2d_texture *gameBackground, vita2d_texture *crossImage, vita2d_font *font, bool keys[15], int batteryPercent, bool showBattery);
  int getStatus();
  void setStatus(int status);
  bool getQuit();
  std::string getFinalInput();
  int getPoints();
};


#endif
