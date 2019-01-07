#ifndef _COMMON_
#define _COMMON_

#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <time.h>       /* time */
#include <dirent.h>

#include <iostream>
#include <fstream>

#include <vector>


#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/power.h>
#include <psp2/audioout.h>
#include <psp2/kernel/clib.h>

#include <vita2d.h>
#include "soloud.h"
#include "soloud_wav.h"
#include "soloud_wavstream.h"

extern std::string buildDate;

extern int theme;
extern bool changeTheme;
extern int themeCount;
//extern std::string themes[2];
extern std::vector<std::string> themes;
extern void loadThemes(); //load the Them information
extern void loadImages(std::string folder); //load the images for the theme
extern void loadThemeConfig(std::string folder); //load config file for theme

extern int mainTextR, mainTextG, mainTextB;
extern int helpTextR, helpTextG, helpTextB;
extern int menuBorderR, menuBorderG, menuBorderB;
extern int menuBGColorR, menuBGColorG, menuBGColorB;
extern int menuBarColorR, menuBarColorG, menuBarColorB;
extern int garyColorR, garyColorG, garyColorB;
extern int jeffColorR, jeffColorG, jeffColorB;
extern int miniColorR, miniColorG, miniColorB;
extern int karenColorR, karenColorG, karenColorB;
extern int snakeColorR, snakeColorG, snakeColorB;
extern int bulletPColorR, bulletPColorG, bulletPColorB;

extern vita2d_texture *garyImage;
extern vita2d_texture *karenImage;
extern vita2d_texture *jeffImage;
extern vita2d_texture *snakeImage1;
extern vita2d_texture *snakeImage2;
extern vita2d_texture *gameBackground;
extern vita2d_texture *playerImage;
extern vita2d_texture *bulletImage;
extern vita2d_texture *crossImage;
extern vita2d_texture *circleImage;
extern vita2d_texture *triangleImage;
extern vita2d_texture *cursorCrosshair;
extern vita2d_texture *cursorDuck;
extern vita2d_texture *cursorWatcher;
extern vita2d_texture *cursor1;
extern vita2d_texture *cursor2;
extern vita2d_texture *saveImage;;

#endif