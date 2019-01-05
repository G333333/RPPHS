#include "intro.h"

Intro::Intro()
{
    crossNeedsReset = false;
}

void Intro::doIntro(vita2d_font *font)
{
    introState = 0;
    introTimer = 0;

    letterCounter[0] = 0;
    letterCounter[1] = 0;
    letterCounter[2] = 0;

    fade = 255;

    motoSplash = vita2d_load_PNG_file("app0:/images/motoSplash.png");

    //main intro handler, switch between intros
    while (introState != 3) {
        switch(introState) {
            case 0:
                Intro::introG33(font);
                break;
            case 1:
                Intro::introMoto(font);
                break;
            case 2:
                Intro::saveWarning(font);
                break;
            default:
                break;
        }
    }

    vita2d_wait_rendering_done();
    saveIcon.cleanUp();
}

void Intro::introG33(vita2d_font *font)
{
    sceCtrlPeekBufferPositive(0, &pad, 1);
    sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);

    if ((pad.buttons & SCE_CTRL_CROSS) && !crossNeedsReset) {
        introState = 1;
        introTimer = 0;
        crossNeedsReset = true;
    } else if (!(pad.buttons & SCE_CTRL_CROSS)) {
        crossNeedsReset = false;
    }

    introTimer++;

    if (introTimer > 180) {
        introState = 1;
        introTimer = 0;
    }

    //G
    letterCounter[0] += 5;
    if (letterCounter[0] >= 255)
        letterCounter[0] = 255;

    //3-1
    if (introTimer > 51) {
        letterCounter[1] += 5;
        if (letterCounter[1] >= 255)
            letterCounter[1] = 255;
    }

    //3-2
    if (introTimer > 102) {
        letterCounter[2] += 5;
        if (letterCounter[2] >= 255)
            letterCounter[2] = 255;
    }

    vita2d_start_drawing();
	vita2d_clear_screen();

    vita2d_font_draw_text(font, 443, 262, RGBA8(0, 255, 0, letterCounter[0]), 20.0f, "G");
    vita2d_font_draw_text(font, 473, 262, RGBA8(0, 255, 0, letterCounter[1]), 20.0f, "3");
    vita2d_font_draw_text(font, 503, 262, RGBA8(0, 255, 0, letterCounter[2]), 20.0f, "3");


    vita2d_end_drawing();
	vita2d_swap_buffers();
}

void Intro::introMoto(vita2d_font *font)
{
    sceCtrlPeekBufferPositive(0, &pad, 1);
    sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);

    if ((pad.buttons & SCE_CTRL_CROSS) && !crossNeedsReset) {
        introState = 2;
        introTimer = 0;
        crossNeedsReset = true;
        saveIcon.start();
    } else if (!(pad.buttons & SCE_CTRL_CROSS)) {
        crossNeedsReset = false;
    }

    introTimer++;

    if (introTimer > 180) {
        introState = 2;
        introTimer = 0;
        saveIcon.start();
    }

    if (introTimer < 51) {
        if (fade > 0) {
            fade -= 5;
        } else if (fade < 0) {
            fade = 0;
        }
    }

    if (introTimer > 129) {
        fade += 5;

        if (fade > 255)
            fade = 255;
    }

    vita2d_start_drawing();
	vita2d_clear_screen();

    vita2d_draw_texture(motoSplash, 0, 0);
    vita2d_draw_rectangle(0, 0, 960, 544, RGBA8(0, 0, 0, fade));

    vita2d_end_drawing();
	vita2d_swap_buffers();
}

void Intro::saveWarning(vita2d_font *font)
{
    sceCtrlPeekBufferPositive(0, &pad, 1);
    sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);

    if ((pad.buttons & SCE_CTRL_CROSS) && !crossNeedsReset) {
        introTimer = 0;
        introState = 3;
        crossNeedsReset = true;
    } else if(!(pad.buttons & SCE_CTRL_CROSS)) {
        crossNeedsReset = false;
    }

    introTimer++;

    if (introTimer > 180) {
        introTimer = 0;
        introState = 3;
    }

    vita2d_start_drawing();
    vita2d_clear_screen();

    vita2d_font_draw_text(font,960 / 2 - vita2d_font_text_width(font, 20.0f, "This game saves data automagically") / 2, 262, RGBA8(255,255,255,255), 20.0f, "This game saves data automagically");
    vita2d_font_draw_text(font,960 / 2 - vita2d_font_text_width(font, 20.0f, "Do not exit or power off when you see this icon") / 2, 282, RGBA8(255,255,244,255), 20.0f, "Do not exit or power off when you see this icon");
    saveIcon.doStuff(960 / 2 - 8, 544 / 2 + 40);

    vita2d_end_drawing();
    vita2d_swap_buffers();
}
