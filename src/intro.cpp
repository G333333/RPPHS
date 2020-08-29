#include "intro.h"

//
// Intro::Intro()
// Initiate Intro Object
//
Intro::Intro() {
    Intro_ResetConfirm = false;
}

//
// Intro::Main()
// Contains Intro initialization and the main Intro loop.
//
void Intro::Main()
{
    // Initialize Variables
    Intro_State = 0;
    Intro_Timer = 0;
    Intro_Alpha = 255;

    // Splash Images
    SplashIMG_G33 = vita2d_load_PNG_file("app0:/images/g33Splash.png");
    SplashIMG_Moto = vita2d_load_PNG_file("app0:/images/motoSplash.png");

    // Set up Controls
    sceCtrlPeekBufferPositive(0, &pad, 1);
    sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);

    // Intro Loop
    while (Intro_State != 3) {
        // Start Drawing
        vita2d_start_drawing();
	    vita2d_clear_screen();

        switch (Intro_State) {
            case 0:
                Intro::Splash_G33();
                break;
            case 1:
                Intro::Splash_MotoLegacy();
                break;
            case 2:
                Intro::Save_Warning();
                break;
            default:
                break;
        }

        // End Drawing
        vita2d_end_drawing();
	    vita2d_swap_buffers();
    }

    // Kill Loop, Free Images, Clean Save Icon
    vita2d_wait_rendering_done();
    vita2d_free_texture(SplashIMG_G33);
    vita2d_free_texture(SplashIMG_Moto);
    Save_Icon.cleanUp();
}

//
// Intro::Reset()
// Resets Intro stats for next Stage
//
void Intro::Reset()
{
    Intro_State++;
    Intro_Timer = 0;
}

//
// Intro::Fade()
// Handles Fade in/out checks
//
void Intro::Fade()
{
    // 'Fade' into the Image
    if (Intro_Timer < 51 && Intro_Alpha > 0) {
        Intro_Alpha -= 5;

        if (Intro_Alpha < 0) { Intro_Alpha = 0; }
    }

    // 'Fade' out of the Image into Black
    if (Intro_Timer > 149) {
        Intro_Alpha += 5;

        if (Intro_Alpha > 255) { Intro_Alpha = 255; }
    }
}

//
// Intro::Splash_G33()
// Displays G33's Splash Image
//
void Intro::Splash_G33() 
{
    // Check if we should Advance to the next Sequence
    if ((pad.buttons & SCE_CTRL_CROSS) && !Intro_ResetConfirm) {
        Intro::Reset();
        Intro_ResetConfirm = true;
    } else if (!(pad.buttons & SCE_CTRL_CROSS)) {
        Intro_ResetConfirm = true;
    }

    Intro_Timer++;

    // Reset when this Stage Ends
    if (Intro_Timer > 200) {
        Intro::Reset();
    }

    // Do Fade Checks
    Intro::Fade();

    // Draw Splash Image
    vita2d_draw_texture(SplashIMG_G33, 0, 0);
    vita2d_draw_rectangle(0, 0, 960, 544, RGBA8(0, 0, 0, Intro_Alpha));
}

//
// Intro::Splash_MotoLegacys()
// Displays MotoLegacys's Splash Image
//
void Intro::Splash_MotoLegacy()
{
    // Check if we should Advance to the next Sequence
    if ((pad.buttons & SCE_CTRL_CROSS) && !Intro_ResetConfirm) {
        Intro::Reset();
        Save_Icon.start();
        Intro_ResetConfirm = true;
    } else if (!(pad.buttons & SCE_CTRL_CROSS)) {
        Intro_ResetConfirm = true;
    }

    Intro_Timer++;

    // Reset when this Stage Ends
    if (Intro_Timer > 200) {
        Intro::Reset();
    }

    // Do Fade Checks
    Intro::Fade();

    // Draw Splash Image
    vita2d_draw_texture(SplashIMG_Moto, 0, 0);
    vita2d_draw_rectangle(0, 0, 960, 544, RGBA8(0, 0, 0, Intro_Alpha));
}

//
// Intro::Save_Warning()
// Displays Auto Save Information
//
void Intro::Save_Warning()
{
    // Check if we should Advance to the next Sequence
    if ((pad.buttons & SCE_CTRL_CROSS) && !Intro_ResetConfirm) {
        Intro::Reset();
        Intro_ResetConfirm = true;
    } else if (!(pad.buttons & SCE_CTRL_CROSS)) {
        Intro_ResetConfirm = true;
    }

    Intro_Timer++;

    // Reset when this Stage Ends
    if (Intro_Timer > 200) {
        Intro::Reset();
    }

    vita2d_font_draw_text(font,960 / 2 - vita2d_font_text_width(font, 20.0f, "This game saves data automagically,") / 2, 262, RGBA8(255,255,255,255), 20.0f, "This game saves data automagically,");
    vita2d_font_draw_text(font,960 / 2 - vita2d_font_text_width(font, 20.0f, "do not exit or power off when you see this icon!") / 2, 282, RGBA8(255,255,244,255), 20.0f, "do not exit or power off when you see this icon!");
    Save_Icon.doStuff(960 / 2 - 8, 544 / 2 + 40);
}