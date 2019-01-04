#include"intro.h"

Intro::Intro()
{
  crossNeedsReset = false;
}

void Intro::doIntro(vita2d_font *font)
{
  int timer = 0;
  int letterCounter1 = 0;
  int letterCounter2 = 0;
  int letterCounter3 = 0;

  while(timer < 180)
  {
    sceCtrlPeekBufferPositive(0, &pad, 1);
    sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);

    if((pad.buttons & SCE_CTRL_CROSS) && !crossNeedsReset)
      {
        timer = 181;
        crossNeedsReset = true;
      }
    else if(!(pad.buttons & SCE_CTRL_CROSS))
      {
        crossNeedsReset = false;
      }

    timer++;
    if(letterCounter1 < 255)
    {
      letterCounter1 += 5;
    }
    if(timer > 51 && letterCounter2 < 255)
    {
      letterCounter2 += 5;
    }
    if(timer > 102 && letterCounter3 < 255)
    {
      letterCounter3 += 5;
    }

    vita2d_start_drawing();
		vita2d_clear_screen();

    vita2d_font_draw_text(font,443, 262, RGBA8(0,255,0,letterCounter1), 20.0f, "G");
    vita2d_font_draw_text(font,473, 262, RGBA8(0,255,0,letterCounter2), 20.0f, "3");
    vita2d_font_draw_text(font,503, 262, RGBA8(0,255,0,letterCounter3), 20.0f, "3");


    vita2d_end_drawing();
		vita2d_swap_buffers();

    if(timer >= 180)
    {
      saveIcon.start();
      int tempTimer = 0;
      while(tempTimer <= 180)
      {
        sceCtrlPeekBufferPositive(0, &pad, 1);
        sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);
        if((pad.buttons & SCE_CTRL_CROSS) && !crossNeedsReset)
          {
            tempTimer = 181;
            crossNeedsReset = true;
          }
        else if(!(pad.buttons & SCE_CTRL_CROSS))
          {
            crossNeedsReset = false;
          }
        tempTimer++;
        vita2d_start_drawing();
    		vita2d_clear_screen();

        vita2d_font_draw_text(font,960 / 2 - vita2d_font_text_width(font, 20.0f, "This game saves data automagically") / 2, 262, RGBA8(255,255,255,255), 20.0f, "This game saves data automagically");
        vita2d_font_draw_text(font,960 / 2 - vita2d_font_text_width(font, 20.0f, "Do not exit or power off when you see this icon") / 2, 282, RGBA8(255,255,244,255), 20.0f, "Do not exit or power off when you see this icon");
        saveIcon.doStuff(960 / 2 - 8, 544 / 2 + 40);

        vita2d_end_drawing();
    		vita2d_swap_buffers();
      }
    }
  }
  vita2d_wait_rendering_done();
  saveIcon.cleanUp();
}
