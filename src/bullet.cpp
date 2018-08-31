#include"bullet.h"

void Bullet::init()
{
  active = false;
  xVel = yVel = 0;

  rect.x = 0;
  rect.y = 0;
  rect.w = 8;
  rect.h = 8;
  rad = 0;
  angle = 0;

  for(int i = 0; i < 2; i++)
  {
    particles[i].init();
  }
}

void Bullet::spawn(double rx, double ry, vitaRect start)
{
  double pi = 3.14159;
  double tx, ty;
  tx = 125 - rx;
  ty = 130 - ry;

  angle = atan2(-ty, -tx) * 180 / pi;//angle for movement.
  rad = atan2(-ty, -tx);//radians for image rotation.
  xVel = 10*(cos(angle*pi/180));   // move x
  yVel = 10*(sin(angle*pi/180));   // move y

  active = true;
}

bool Bullet::getActive()
{
  return active;
}

void Bullet::die()
{
  active = false;
}

vitaRect Bullet::getRect()
{
  return rect;
}

void Bullet::doStuff(vita2d_texture *bulletImage, vitaRect levelRect, vitaRect start, bool pause)
{
  if(!active)
  {
    rect.x = start.x + 12;
    rect.y = start.y + 12;

    for(int i = 0; i < 2; i++)
    {
      particles[i].doStuff(rect, RGBA8(241,244,66,255), pause);
    }
  }

  if(active)
  {
    if(!pause)
    {
      rect.x += xVel;
      rect.y += yVel;
    }

    if(rect.x < levelRect.x || rect.x > levelRect.x + levelRect.w - rect.w || rect.y < levelRect.y || rect.y > levelRect.y + levelRect.h - rect.h)
    {
      active = false;
      int tempSpeed = 0;
      int tempLife = 0;
      for(int i = 0; i < 2; i++)
      {
        tempSpeed = rand() % 2 + 1;
        tempLife = rand() % 20 + 1;
        particles[i].spawn(rect, tempSpeed, tempLife);
        rand(); rand();
      }
    }

    vita2d_draw_texture_scale_rotate(bulletImage, rect.x + 4, rect.y + 4, 0.5, 0.5, rad);
    //drawEmptyRect(rect, RGBA8(255,255,255,255));
  }
}

void Bullet::moveBackX(double playerXvel)
{
  rect.x -= playerXvel;
}

void Bullet::moveBackY(double playerYvel)
{
  rect.y -= playerYvel;
}
