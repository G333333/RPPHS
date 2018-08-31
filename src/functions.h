#ifndef _Functions_File_
#define _Functions_File_

#include <vita2d.h>

#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/io/stat.h>

#include <iostream>
#include <fstream>

struct vitaRect {
  double x;
  double y;
  double w;
  double h;
};

void drawEmptyRect(vitaRect rect, unsigned int color);
void drawEmptyRect(double x1, double y1, double w, double h, unsigned int color);

bool updateKeys(int index, SceCtrlData pad);

bool checkCollision(vitaRect a, vitaRect b);

void logError(std::string input);

#endif
