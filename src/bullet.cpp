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

  for(int i = 0; i < 1; i++)
  {
    particles[i].init();
  }
}

void Bullet::spawn(double angle, vitaRect start)
{
  rect.x = start.x + start.w / 4;
  rect.y = start.y + start.h / 4;
  this->rad = angle;

  xVel = 10*(cos(rad));   // move x wtf mate......
  yVel = 10*(sin(rad));   // move y

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

void Bullet::doStuff(vitaRect levelRect, vitaRect start, bool pause)
{
  if(!active)
  {
    rect.x = start.x + 12;
    rect.y = start.y + 12;

    for(int i = 0; i < 1; i++)
    {
      particles[i].doStuff(rect, RGBA8(bulletPColorR,bulletPColorG,bulletPColorB,255), pause);
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
      for(int i = 0; i < 1; i++)
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
