#include"karen.h"

void Karen::init()
{
  xVel = yVel = 0;

  rect.x = 0;
  rect.y = 0;
  rect.w = 32;
  rect.h = 32;

  target.x = 0;
  target.y = 0;
  target.w = 0;
  target.h = 0;

  active = false;
  spawning = false;
  spawnCount = 0;
  spawnRadius = 0;

  pause = false;

  counter = 0;

  for(int i = 0; i < 15; i++)
  {
    particles[i].init();
  }
}

void Karen::spawn(vitaRect levelRect)
{
  spawning = true;

  int tempx, tempy;
  int x = levelRect.x;
  int y = levelRect.y;
  int w = levelRect.w;
  int h = levelRect.h;
  tempx = rand() % w + x;
  tempy = rand() % h + y;

  rect.x = tempx;
  rect.y = tempy;

  tempx = rand() % w + x;
  tempy = rand() % h + y;

  target.x = tempx;
  target.y = tempy;

  xVel = yVel = 0;
  counter = 0;
}

void Karen::newTarget(vitaRect levelRect)
{
  int tempx, tempy;
  int x = levelRect.x;
  int y = levelRect.y;
  int w = levelRect.w;
  int h = levelRect.h;
  tempx = rand() % w + x;
  tempy = rand() % h + y;

  target.x = tempx;
  target.y = tempy;

  counter = rand() % 40 + 120;
  wait = 0;
}

void Karen::preSpawn()
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
  vita2d_draw_fill_circle(rect.x + rect.w / 2, rect.y + rect.h / 2, spawnRadius, RGBA8(60,170, 244, 100));
}

bool Karen::getSpawning()
{
  return spawning;
}

void Karen::die()
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

vitaRect Karen::getRect()
{
  return rect;
}

bool Karen::getActive()
{
    return active;
}

bool Karen::getParticlesActive()
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

void Karen::moveX()
{
  if(!pause)
  {
    rect.x += xVel;
  }
}

void Karen::moveY()
{
  if(!pause)
  {
    rect.y += yVel;
  }
}

void Karen::moveBackX()
{
  rect.x -= xVel;
}

void Karen::moveBackY()
{
  rect.y -= yVel;
}

void Karen::moveBackX(double playerxVel)
{
  rect.x -= playerxVel;
  for(int i = 0; i < 15; i++)
  {
    particles[i].moveBackX(playerxVel);
  }
}

void Karen::moveBackY(double playeryVel)
{
  rect.y -= playeryVel;
  for(int i = 0; i < 15; i++)
  {
    particles[i].moveBackY(playeryVel);
  }
}

void Karen::doStuff(vita2d_texture *karenImage, vitaRect levelRect, bool pause)
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
    xVel = 1*(cos(angle*pi/180));   // move x
    yVel = 1*(sin(angle*pi/180));   // move y

    if(!this->pause)
    {
      counter--;
    }
    if(counter <= 0)
    {
      target.x = rect.x;
      target.y = rect.y;
      xVel = 0;
      yVel = 0;
      wait++;
      if(wait >= 60)
      {
        newTarget(levelRect);
        wait = 0;
      }
    }

    vita2d_draw_texture_rotate(karenImage, rect.x + 16, rect.y + 16, rad);
    vita2d_draw_fill_circle(rect.x + rect.w / 2, rect.y + rect.h / 2, 32, RGBA8(60,170, 244, 25));
    //drawEmptyRect(rect, RGBA8(0,255,0,255));
  }
  if(!active)
  {
    for(int i = 0; i < 15; i++)
    {
      particles[i].doStuff(rect, RGBA8(0, 0, 244, 255), pause);
    }
  }
  if(spawning)
  {
    preSpawn();
  }
}
