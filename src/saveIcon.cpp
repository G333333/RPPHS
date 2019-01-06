#include"saveIcon.h"

SaveIcon::SaveIcon()
{
  for(int i = 0; i < 10; i++)
  {
    x[i] = 0;
    xVel[i] = 5;
  }
  timer = 0;
  rad = 0.0;
  //saveImage = vita2d_load_PNG_file("app0:/images/saveImage.png");
}

void SaveIcon::doStuff(int xStart, int yStart)
{
  if(timer < 180)
  {

    rad += 0.2;
    if(rad > 6.28319)
      rad = 0.0;

    vita2d_draw_texture_scale_rotate(saveImage, xStart, yStart, 2, 2, rad);



  /**  if(timer > 0)
      x[0] += xVel[0];
    if(timer > 2)
      x[1] += xVel[1];
    if(timer > 4)
      x[2] += xVel[2];
    if(timer > 6)
      x[3] += xVel[3];
    if(timer > 8)
      x[4] += xVel[4];
    if(timer > 10)
      x[5] += xVel[5];
    if(timer > 12)
      x[6] += xVel[6];
    if(timer > 14)
      x[7] += xVel[7];
    if(timer > 16)
      x[8] += xVel[8];
    if(timer > 18)
      x[9] += xVel[9];

    for(int i = 0; i < 10; i++)
    {
      if(x[i] + 4 > 30 || x[i] < 0)
        xVel[i] = xVel[i] * -1;
    }

    vita2d_draw_rectangle(xStart + 0, yStart + 0, 34, 45, RGBA8(255,255,255,255));
    vita2d_draw_rectangle(xStart + x[0], yStart + 4, 4, 4, RGBA8(255,0,0,255));
    vita2d_draw_rectangle(xStart + x[1], yStart + 8, 4, 4, RGBA8(255,0,0,255));
    vita2d_draw_rectangle(xStart + x[2], yStart + 12, 4, 4, RGBA8(255,0,0,255));
    vita2d_draw_rectangle(xStart + x[3], yStart + 16, 4, 4, RGBA8(255,0,0,255));
    vita2d_draw_rectangle(xStart + x[4], yStart + 20, 4, 4, RGBA8(255,0,0,255));
    vita2d_draw_rectangle(xStart + x[5], yStart + 24, 4, 4, RGBA8(255,0,0,255));
    vita2d_draw_rectangle(xStart + x[6], yStart + 28, 4, 4, RGBA8(255,0,0,255));
    vita2d_draw_rectangle(xStart + x[7], yStart + 32, 4, 4, RGBA8(255,0,0,255));
    vita2d_draw_rectangle(xStart + x[8], yStart + 36, 4, 4, RGBA8(255,0,0,255));
    vita2d_draw_rectangle(xStart + x[9], yStart + 40, 4, 4, RGBA8(255,0,0,255)); **/

    timer++;
  }
}

void SaveIcon::start()
{
  timer = 0;
}

int SaveIcon::getTimer()
{
  return timer;
}

void SaveIcon::cleanUp()
{
  //vita2d_free_texture(saveImage);
  //saveImage = NULL;
}
