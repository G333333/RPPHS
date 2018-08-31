#include"jeff.h"

void Jeff::init()
{
  xVel = yVel = 0;
  speed = 0;
  angle = 0.0;

  rect.x = 0;
  rect.y = 0;
  rect.w = 32;
  rect.h = 32;

  target.x = 0;
  target.y = 0;
  target.w = 0;
  target.h = 0;

  bigRect.x = rect.x - 100;
  bigRect.y = rect.y - 100;
  bigRect.w = 200 + rect.w;
  bigRect.h = 200 + rect.h;

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

void Jeff::spawn(vitaRect levelRect)
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

void Jeff::newTarget(vitaRect levelRect)
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

void Jeff::preSpawn()
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
  vita2d_draw_fill_circle(rect.x + rect.w / 2, rect.y + rect.h / 2, spawnRadius, RGBA8(0,200, 0, 100));
}

bool Jeff::getSpawning()
{
  return spawning;
}

void Jeff::die()
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

vitaRect Jeff::getRect()
{
  return rect;
}

bool Jeff::getActive()
{
    return active;
}

bool Jeff::getParticlesActive()
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

void Jeff::moveX()
{
  if(!pause)
  {
    rect.x += xVel;
  }
}

void Jeff::moveY()
{
  if(!pause)
  {
    rect.y += yVel;
  }
}

void Jeff::moveBackX()
{
  rect.x -= xVel;
}

void Jeff::moveBackY()
{
  rect.y -= yVel;
}

void Jeff::moveBackX(double playerxVel)
{
  rect.x -= playerxVel;
  for(int i = 0; i < 15; i++)
  {
    particles[i].moveBackX(playerxVel);
  }
}

void Jeff::moveBackY(double playeryVel)
{
  rect.y -= playeryVel;
  for(int i = 0; i < 15; i++)
  {
    particles[i].moveBackY(playeryVel);
  }
}

void Jeff::doStuff(vita2d_texture *jeffImage, vitaRect levelRect, vitaRect playerRect, bool pause)
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
    bigRect.x = rect.x - 100;
    bigRect.y = rect.y - 100;
    double pi = 3.14159;
    double tx, ty;
    tx = rect.x - target.x;
    ty = rect.y - target.y;

    angle = atan2(-ty, -tx) * 180 / pi;//angle for movement.
    float rad = atan2(-ty, -tx);//radians for image rotation.
    xVel = speed*(cos(angle*pi/180));   // move x
    yVel = speed*(sin(angle*pi/180));   // move y

    if(!checkCollision(bigRect, playerRect))
    {
      speed = 1;
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
        rad += 0.001;
        if(wait >= 60)
        {
          newTarget(levelRect);
          wait = 0;
        }
      }
    }

    else
    {
      speed = 3;
      target.x = playerRect.x;
      target.y = playerRect.y;

      wait = 0;
      counter = 60;
    }

    vita2d_draw_texture_rotate(jeffImage, rect.x + 16, rect.y + 16, rad + 1.5708);
    vita2d_draw_fill_circle(rect.x + rect.w / 2, rect.y + rect.h / 2, 32, RGBA8(0,255, 0, 25));
    //drawEmptyRect(bigRect, RGBA8(0,255,0,255));
  }
  if(!active)
  {
    for(int i = 0; i < 15; i++)
    {
      particles[i].doStuff(rect, RGBA8(0, 255, 0, 255), pause);
    }
  }
  if(spawning)
  {
    preSpawn();
  }
}

double Jeff::getAngle()
{
  return angle;
}
