#include "messageBox.h"

bool makeYesNoBox(std::string message, std::string message1)
{
  SceCtrlData gamePad;
  memset(&gamePad, 0, sizeof(gamePad));

  int textWidth = vita2d_font_text_width(font, 20.0f, message.c_str());
  int boxWidth = textWidth + 20;
  while(true)
  {
    sceCtrlPeekBufferPositive(0, &gamePad, 1);
    sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);

    vita2d_start_drawing();

    vita2d_draw_rectangle(960 / 2 - boxWidth / 2, 544 / 2 - 50, boxWidth, 100, RGBA8(menuBGColorR, menuBGColorG,menuBGColorB,255));
    drawEmptyRect(960 / 2 - boxWidth / 2, 544 / 2 - 50, boxWidth, 100, RGBA8(menuBorderR, menuBorderG,menuBarColorB,255));
    vita2d_font_draw_text(font, 960 / 2 - textWidth / 2, 544 / 2 - 25, RGBA8(mainTextR, mainTextG, mainTextB,255), 20.0f, message.c_str());
    vita2d_font_draw_text(font, 960 / 2 - textWidth / 2, 544 / 2 - 10, RGBA8(mainTextR, mainTextG, mainTextB,255), 20.0f, message1.c_str());
    
    vita2d_font_draw_text(font, 960 / 2 - boxWidth / 2 + 42, 544 / 2 + 50 - 37 + vita2d_font_text_height(font, 20.0f,"No"), RGBA8(mainTextR, mainTextG, mainTextB,255), 20.0f, "No");
    vita2d_draw_texture(circleImage, 960 / 2 - boxWidth / 2 + 5, 544 / 2 + 50 - 37);
    vita2d_font_draw_text(font, 960 / 2 + boxWidth / 2 - 42 - vita2d_font_text_width(font, 20.0f,"Yes"), 544 / 2 + 50 - 37 + vita2d_font_text_height(font, 20.0f,"No"), RGBA8(mainTextR, mainTextG,mainTextB,255), 20.0f, "Yes");
    vita2d_draw_texture(crossImage, 960/ 2 + boxWidth / 2 - 37, 544 / 2 + 50 - 37);

    vita2d_end_drawing();
    vita2d_swap_buffers();

    if(gamePad.buttons & SCE_CTRL_CROSS)
    {
      return true;
    }
    if(gamePad.buttons & SCE_CTRL_CIRCLE)
    {
      return false;
    }
  }
}