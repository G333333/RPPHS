#ifndef _COMMON_
#define _COMMON_

#include <stdio.h>
#include <string>
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

extern std::string buildDate;

extern int theme;

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

#endif