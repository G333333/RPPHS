#include"functions.h"

void drawEmptyRect(vitaRect rect, unsigned int color)
{
  vita2d_draw_line(rect.x, rect.y, rect.x + rect.w, rect.y, color);
  vita2d_draw_line(rect.x, rect.y, rect.x, rect.y + rect.h, color);
  vita2d_draw_line(rect.x, rect.y + rect.h, rect.x + rect.w, rect.y + rect.h, color);
  vita2d_draw_line(rect.x + rect.w, rect.y, rect.x + rect.w, rect.y + rect.h, color);
}

void drawEmptyRect(double x1, double y1, double w, double h, unsigned int color)
{
  vita2d_draw_line(x1, y1, x1 + w, y1, color);
  vita2d_draw_line(x1, y1, x1, y1 + h, color);
  vita2d_draw_line(x1, y1 + h, x1 + w, y1 + h, color);
  vita2d_draw_line(x1 + w, y1, x1 + w, y1 + h, color);
}

bool updateKeys(int index, SceCtrlData pad)
{
  bool keys[2];

  if (pad.buttons & SCE_CTRL_UP)
  {
    keys[0] = true;
  }
  else if(pad.buttons != SCE_CTRL_UP)
  {
    keys[0] = false;
  }
  if(pad.buttons & SCE_CTRL_DOWN)
  {
    keys[1] = true;
  }
  else if(pad.buttons != SCE_CTRL_DOWN)
  {
    keys[1] = false;
  }

  return keys[index];
}

bool checkCollision(vitaRect a, vitaRect b)
{
  //The sides of the rectangles
    double leftA, leftB;
    double rightA, rightB;
    double topA, topB;
    double bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
   if( bottomA <= topB )
   {
       return false;
   }

   if( topA >= bottomB )
   {
       return false;
   }

   if( rightA <= leftB )
   {
       return false;
   }

   if( leftA >= rightB )
   {
       return false;
   }

   //If none of the sides from A are outside B
   return true;
}

void logError(std::string input)
{
  std::ofstream logFile;
  sceIoMkdir("ux0:/data/RPPHS", 0777);
  logFile.open("ux0:/data/RPPHS/log.txt", std::ios::app); //fix me
  logFile << input;
  logFile.close();
}
