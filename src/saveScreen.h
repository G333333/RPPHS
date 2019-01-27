#ifndef _Save_Screen_
#define _Save_Screen_

#include"common.h"

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
  int fade;
public:
  void init(int points);
  void start(int points);
  void doStuff(bool keys[15], bool showBattery);
  int getStatus();
  void setStatus(int status);
  bool getQuit();
  std::string getFinalInput();
  int getPoints();
};


#endif
