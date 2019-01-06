#include"gary.h"

void Gary::init()
{
  xVel = yVel = 0;

  rect.x = 0;
  rect.y = 0;
  rect.w = 32;
  rect.h = 32;

  active = false;
  spawning = false;
  spawnCount = 0;
  spawnRadius = 0;

  pause = false;

  for(int i = 0; i < 15; i++)
  {
    particles[i].init();
  }
}

void Gary::spawn(vitaRect levelRect, int x, int y)
{
  spawning = true;

  int tempx, tempy;
  int lx = levelRect.x;
  int ly = levelRect.y;
  int lw = levelRect.w;
  int lh = levelRect.h;
  tempx = rand() % lw + lx;
  tempy = rand() % lh + ly;

  if(x == 0 && y == 0)
  {
    rect.x = tempx;
    rect.y = tempy;
  }
  else
  {
    rect.x = x; 
    rect.y = y;
  }


  xVel = yVel = 0;
}

void Gary::preSpawn()
{
  if(!pause)
  {
    spawnRadius += 2;
  }
  if(spawnRadius >= 32)
  {
    spawnRadius = 0;
    spawnCount++;
  }
  if(spawnCount > 2)
  {
    spawnRadius = 0;
    spawnCount = 0;
    active = true;
    spawning = false;
  }
  vita2d_draw_fill_circle(rect.x + rect.w / 2, rect.y + rect.h / 2, spawnRadius, RGBA8(garyColorR,garyColorG,garyColorB,100));
}

bool Gary::getSpawning()
{
  return spawning;
}

void Gary::die()
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

vitaRect Gary::getRect()
{
  return rect;
}

bool Gary::getActive()
{
    return active;
}

bool Gary::getParticlesActive()
{
  for(int i = 0; i < 15; i++)
  {
    if(particles[i].getActive())
    {
      return true;
    }
  }
  return false;
}

void Gary::moveX()
{
  if(!pause)
  {
    rect.x += xVel;
  }
}

void Gary::moveY()
{
  if(!pause)
  {
    rect.y += yVel;
  }
}

void Gary::moveBackX()
{
  rect.x -= xVel;
}

void Gary::moveBackY()
{
  rect.y -= yVel;
}

void Gary::moveBackX(double playerxVel)
{
  rect.x -= playerxVel;
  for(int i = 0; i < 15; i++)
  {
    particles[i].moveBackX(playerxVel);
  }
}

void Gary::moveBackY(double playeryVel)
{
  rect.y -= playeryVel;
  for(int i = 0; i < 15; i++)
  {
    particles[i].moveBackY(playeryVel);
  }
}

void Gary::doStuff(vitaRect target, bool pause, vitaRect levelRect)
{
  this->pause = pause;
  if(rect.x < levelRect.x)
  {
    rect.x = levelRect.x;
  }
  if(rect.x + rect.w > levelRect.x + levelRect.w)
  {
    rect.x = levelRect.x + levelRect.w - rect.w;
  }
  if(rect.y < levelRect.y)
  {
    rect.y = levelRect.y;
  }
  if(rect.y + rect.h > levelRect.y + levelRect.h)
  {
    rect.y = levelRect.y + levelRect.h - rect.h;
  }
  if(active)
  {
    double pi = 3.14159;
    double tx, ty;
    tx = rect.x - target.x;
    ty = rect.y - target.y;

    double angle = atan2(-ty, -tx) * 180 / pi;//angle for movement.
    float rad = atan2(-ty, -tx);//radians for image rotation.
    xVel = 2*(cos(angle*pi/180));   // move x
    yVel = 2*(sin(angle*pi/180));   // move y

    vita2d_draw_texture_rotate(garyImage, rect.x + 16, rect.y + 16, rad);
    vita2d_draw_fill_circle(rect.x + rect.w / 2, rect.y + rect.h / 2, 32, RGBA8(garyColorR,garyColorG,garyColorB,20));
    //drawEmptyRect(rect, RGBA8(0,255,0,255));
  }
  if(!active)
  {
    for(int i = 0; i < 15; i++)
    {
      particles[i].doStuff(rect, RGBA8(garyColorR,garyColorG,garyColorB,255), pause);
    }
  }
  if(spawning)
  {
    preSpawn();
  }
}
