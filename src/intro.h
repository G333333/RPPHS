#ifndef _Intro_Class
#define _Intro_Class

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>

#include <vita2d.h>
#include "saveIcon.h"

class Intro{
private:
    SaveIcon Save_Icon;
    SceCtrlData pad;
    bool Intro_ResetConfirm;
    int Intro_State;
    int Intro_Timer;
    int Intro_Alpha;
    vita2d_texture *SplashIMG_G33, *SplashIMG_Moto;
public:
    Intro();
    void Reset();
    void Fade();
    void Main();
    void Splash_G33();
    void Splash_MotoLegacy();
    void Save_Warning();
};

#endif
