#include"miniJeff.h"

void MiniJeff::init()
{
  active = false;
  xVel = yVel = 0;

  rect.x = 0;
  rect.y = 0;
  rect.w = 12;
  rect.h = 12;
  rad = 0;
  angle = 0;

  safeTime = 0;

  for(int i = 0; i < 15; i++)
  {
    particles[i].init();
  }
}

void MiniJeff::spawn(vitaRect start, double angle)
{
  double pi = 3.14159;
  rect.x = start.x;
  rect.y = start.y;

  //angle = atan2(-ty, -tx) * 180 / pi;// kept for reference
  this->angle = angle;
  rad = angle * (pi / 180)  + 1.5708;
  //rad = atan2(-ty, -tx);//radians for image rotation. kept for reference
  xVel = 6*(cos(angle*pi/180));   // move x
  yVel = 6*(sin(angle*pi/180));   // move y

  active = true;

  safeTime = 0;
}

bool MiniJeff::getActive()
{
  return active;
}

vitaRect MiniJeff::getRect()
{
  return rect;
}

void MiniJeff::doStuff(vita2d_texture *jeffImage, bool pause, vitaRect levelRect)
{
  double pi = 3.14159;
  if(active)
  {
    if(safeTime <= 30)
    {
      safeTime++;
    }
    if(!pause)
    {
      rect.x += xVel;
      rect.y += yVel;
    }

    if(rect.x < levelRect.x) //left wall hit
    {
      rect.x = levelRect.x;

      if(yVel > 0.0)
      {
        angle -= 90.0;
      }
      else if(yVel < 0)
      {
        angle += 90.0;
      }
      else if(yVel == 0.0)
      {
        angle -= 180;
      }
      if(angle > 360.0)
      {
        double temp = angle - 360.0;
        angle = 0.0 + temp;
      }
      if(angle < 0)
      {
        double temp = 0 - angle;
        angle = 360 - temp;
      }
      xVel = 6*(cos(angle*pi/180));   // move x
      yVel = 6*(sin(angle*pi/180));   // move y
      rad = angle * (pi / 180)  + 1.5708;
    }

    if(rect.x + rect.w > levelRect.x + levelRect.w) //right wall hit
    {
      rect.x = levelRect.x + levelRect.w - rect.w;

      if(yVel > 0.0)
      {
        angle += 90.0;
      }
      else if(yVel < 0)
      {
        angle -= 90.0;
      }
      else if(yVel == 0.0)
      {
        angle -= 180;
      }
      if(angle > 360.0)
      {
        double temp = angle - 360.0;
        angle = 0.0 + temp;
      }
      if(angle < 0)
      {
        double temp = 0 - angle;
        angle = 360 - temp;
      }
      xVel = 6*(cos(angle*pi/180));   // move x
      yVel = 6*(sin(angle*pi/180));   // move y
      rad = angle * (pi / 180)  + 1.5708;
    }

    if(rect.y < levelRect.y) //top wall hit
    {
      rect.y = levelRect.y;

      if(xVel > 0)
      {
        angle += 90.0;
      }
      else if(xVel < 0)
      {
        angle -= 90.0;
      }
      else if(xVel == 0)
      {
        angle -= 180.0;
      }
      if(angle > 360.0)
      {
        double temp = angle - 360.0;
        angle = 0.0 + temp;
      }
      if(angle < 0)
      {
        double temp = 0 - angle;
        angle = 360 - temp;
      }
      xVel = 6*(cos(angle*pi/180));   // move x
      yVel = 6*(sin(angle*pi/180));   // move y
      rad = angle * (pi / 180)  + 1.5708;
    }

    if(rect.y + rect.h > levelRect.y + levelRect.h) //bottom wall hit
    {

      rect.y = levelRect.y + levelRect.h - rect.h;

      if(xVel > 0)
      {
        angle -= 90.0;
      }
      else if(xVel < 0)
      {
        angle += 90.0;
      }
      else if(xVel == 0)
      {
        angle -= 180.0;
      }
      if(angle > 360.0)
      {
        double temp = angle - 360.0;
        angle = 0.0 + temp;
      }
      if(angle < 0)
      {
        double temp = 0 - angle;
        angle = 360 - temp;
      }
      xVel = 6*(cos(angle*pi/180));   // move x
      yVel = 6*(sin(angle*pi/180));   // move y
      rad = angle * (pi / 180)  + 1.5708;
    }

    vita2d_draw_texture_scale_rotate(jeffImage, rect.x + 4, rect.y + 4, 0.7, 0.7, rad);
    //drawEmptyRect(rect, RGBA8(255,255,255,255));
  }

  if(!active)
  {
    for(int i = 0; i < 15; i++)
    {
      particles[i].doStuff(rect, RGBA8(0,255,0 ,255), pause);
    }
  }
}

void MiniJeff::moveBackX(double playerxVel)
{
  rect.x -= playerxVel;

  for(int i = 0; i < 15; i++)
  {
    particles[i].moveBackX(playerxVel);
  }
}

void MiniJeff::moveBackY(double playeryVel)
{
  rect.y -= playeryVel;

  for(int i = 0; i < 15; i++)
  {
    particles[i].moveBackY(playeryVel);
  }
}

void MiniJeff::die()
{
  if(safeTime >= 30)
  {
    active = false;

    int tempSpeed = 0;
    int tempLife = 0;
    for(int i = 0; i < 15; i++)
    {
      tempSpeed = rand() % 2 + 1;
      tempLife = rand() % 20 + 1;
      particles[i].spawn(rect, tempSpeed, tempLife);
      rand(); rand();
    }
  }
}

int MiniJeff::getSafeTime()
{
  return safeTime;
}
