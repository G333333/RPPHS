#include"particle.h"

void Particle::init(int w, int h)
{
  active = false;
  xVel = yVel = 0;

  rect.x = 0;
  rect.y = 0;
  rect.w = w;
  rect.h = w;
  angle = 0;

  tx = ty = 0;
  lifeSpan = 0;
}

void Particle::spawn(vitaRect start, int tempSpeed, int tempLife)
{
  rect.x = start.x;
  rect.y = start.y;
  double pi = 3.14159;
  tx = rand() % 20 + rect.x - 10;
  ty = rand() % 20 + rect.y - 10;
  double dx = start.x - tx;
  double dy = start.y - ty;

  angle = atan2(-dy, -dx) * 180 / pi;//angle for movement.
  xVel = tempSpeed*(cos(angle*pi/180));   // move x
  yVel = tempSpeed*(sin(angle*pi/180));   // move y

  active = true;
  lifeSpan = tempLife;
}

bool Particle::getActive()
{
  return active;
}

vitaRect Particle::getRect()
{
  return rect;
}

void Particle::doStuff(vitaRect start, unsigned int color, bool pause)
{
  if(!active)
  {
    rect.x = start.x + 16;
    rect.y = start.y + 16;
  }
  if(active)
  {
    if(!pause)
    {
      rect.x += xVel;
      rect.y += yVel;

      lifeSpan--;
    }

    vita2d_draw_line(rect.x, rect.y + rect.h / 2, rect.x + rect.w, rect.y + rect.h / 2, color);
    vita2d_draw_line(rect.x + rect.w / 2, rect.y, rect.x + rect.w / 2, rect.y + rect.h, color);

    vita2d_draw_line(rect.x, rect.y, rect.x + rect.w, rect.y + rect.h, color);
    vita2d_draw_line(rect.x + rect.w, rect.y, rect.x, rect.y + rect.h, color);
    

    if(rect.x < 0 || rect.x + rect.w > 944 || rect.y < 0 || rect.y + rect.h > 544)//fix me!!
    {
      active = false;
    }
    if(lifeSpan <= 0)
    {
      active = false;
    }
  }
}

void Particle::moveBackX(double playerXvel)
{
  rect.x -= playerXvel;
}

void Particle::moveBackY(double playerYvel)
{
  rect.y -= playerYvel;
}
