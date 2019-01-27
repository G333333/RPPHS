#include"snakeGuy.h"

void SnakeGuy::init()
{
  rect1.x = 0;
  rect1.y = 0;
  rect1.w = 16;
  rect1.h = 16;

  rect2.x = 0;
  rect2.y = 0;
  rect2.w = 16;
  rect2.h = 16;

  rect3.x = 0;
  rect3.y = 0;
  rect3.w = 16;
  rect3.h = 16;

  rect4.x = 0;
  rect4.y = 0;
  rect4.w = 16;
  rect4.h = 16;

  rect5.x = 0;
  rect5.y = 0;
  rect5.w = 16;
  rect5.h = 16;

  rect6.x = 0;
  rect6.y = 0;
  rect6.w = 16;
  rect6.h = 16;

  rect7.x = 0;
  rect7.y = 0;
  rect7.w = 16;
  rect7.h = 16;

  rect8.x = 0;
  rect8.y = 0;
  rect8.w = 16;
  rect8.h = 16;

  rect1Active = false;
  rect2Active = false;
  rect3Active = false;
  rect4Active = false;
  rect5Active = false;
  rect6Active = false;
  rect7Active = false;
  rect8Active = false;

  realTarget.x = 0;
  realTarget.y = 0;
  realTarget.w = 1;
  realTarget.h = 1;

  spawning = false;
  spawnCount = 0;
  spawnRadius = 0;

  dying = false;

  targetTimer = 0;

  pause = false;

  moveInterval = 0;
  head = 1; //wich square is the head of the snake;

  for(int i = 0; i < 15; i++)
  {
    particles[i].init();
  }
}

void SnakeGuy::spawn(vitaRect levelRect)
{
  spawning = true;
  dying = false;

  int tempx, tempy;
  int x = levelRect.x;
  int y = levelRect.y;
  int w = levelRect.w;
  int h = levelRect.h;
  tempx = rand() % w + x;
  tempy = rand() % h + y;

  if(tempx < levelRect.x)
  {
    tempx = levelRect.x;
  }
  if(tempx + rect1.w > levelRect.x + levelRect.w)
  {
    tempx = levelRect.x + levelRect.w - rect1.w;
  }
  if(tempy < levelRect.y)
  {
    tempy = levelRect.y;
  }
  if(tempy + rect1.h > levelRect.y + levelRect.h)
  {
    tempy = levelRect.y + levelRect.h - rect1.h;
  }

  rect1.x = tempx;
  rect1.y = tempy;

  rect2.x = tempx;
  rect2.y = tempy;

  rect3.x = tempx;
  rect3.y = tempy;

  rect4.x = tempx;
  rect4.y = tempy;

  rect5.x = tempx;
  rect5.y = tempy;

  rect6.x = tempx;
  rect6.y = tempy;

  rect7.x = tempx;
  rect7.y = tempy;

  rect8.x = tempx;
  rect8.y = tempy;
  tempx = rand() % w + x;
  tempy = rand() % h + y;
  realTarget.x = tempx;
  realTarget.y = tempy;

  moveInterval = 0;
  head = 1;
}

void SnakeGuy::spawn(vitaRect levelRect, int posx, int posy)
{
  spawning = true;
  dying = false;

  int tempx = posx;
  int tempy = posy;

  int x = levelRect.x;
  int y = levelRect.y;
  int w = levelRect.w;
  int h = levelRect.h;

  if(tempx < levelRect.x)
  {
    tempx = levelRect.x;
  }
  if(tempx + rect1.w > levelRect.x + levelRect.w)
  {
    tempx = levelRect.x + levelRect.w - rect1.w;
  }
  if(tempy < levelRect.y)
  {
    tempy = levelRect.y;
  }
  if(tempy + rect1.h > levelRect.y + levelRect.h)
  {
    tempy = levelRect.y + levelRect.h - rect1.h;
  }

  rect1.x = tempx;
  rect1.y = tempy;

  rect2.x = tempx;
  rect2.y = tempy;

  rect3.x = tempx;
  rect3.y = tempy;

  rect4.x = tempx;
  rect4.y = tempy;

  rect5.x = tempx;
  rect5.y = tempy;

  rect6.x = tempx;
  rect6.y = tempy;

  rect7.x = tempx;
  rect7.y = tempy;

  rect8.x = tempx;
  rect8.y = tempy;
  
  tempx = rand() % w + x;
  tempy = rand() % h + y;
  realTarget.x = tempx;
  realTarget.y = tempy;

  moveInterval = 0;
  head = 1;
}

void SnakeGuy::preSpawn()
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
    rect1Active = true;
    rect2Active = true;
    rect3Active = true;
    rect4Active = true;
    rect5Active = true;
    rect6Active = true;
    rect7Active = true;
    rect8Active = true;
    spawning = false;
  }
  vita2d_draw_fill_circle(rect1.x + rect1.w / 2, rect1.y + rect1.h / 2, spawnRadius, RGBA8(snakeColorR, snakeColorG,snakeColorB, 100));
}

bool SnakeGuy::getSpawning()
{
  return spawning;
}

void SnakeGuy::die()
{
  vitaRect temp;
  dying = true;
  spawning = false;
  switch (head) {
    case 1:
      temp = rect1;
      rect1Active = false;
      break;
    case 2:
      temp = rect2;
      rect2Active = false;
      break;
    case 3:
      temp = rect3;
      rect3Active = false;
      break;
    case 4:
      temp = rect4;
      rect4Active = false;
      break;
    case 5:
      temp = rect5;
      rect5Active = false;
      break;
    case 6:
      temp = rect6;
      rect6Active = false;
      break;
    case 7:
      temp = rect7;
      rect7Active = false;
      break;
    case 8:
      temp = rect8;
      rect8Active = false;
      break;
  }
  head = newHead();
  int tempSpeed = 0;
  int tempLife = 0;
  for(int i = 0; i < 15; i++)
  {
    tempSpeed = rand() % 2 + 1;
    tempLife = 5;
    particles[i].spawn(temp, tempSpeed, tempLife);
    rand(); rand();
  }
}

vitaRect SnakeGuy::getRect1()
{
  return rect1;
}

vitaRect SnakeGuy::getRect2()
{
  return rect2;
}

vitaRect SnakeGuy::getRect3()
{
  return rect3;
}

vitaRect SnakeGuy::getRect4()
{
  return rect4;
}

vitaRect SnakeGuy::getRect5()
{
  return rect5;
}

vitaRect SnakeGuy::getRect6()
{
  return rect6;
}

vitaRect SnakeGuy::getRect7()
{
  return rect7;
}

vitaRect SnakeGuy::getRect8()
{
  return rect8;
}

bool SnakeGuy::getActive()
{
    if(rect1Active)
    {
      return true;
    }
    if(rect2Active)
    {
      return true;
    }
    if(rect3Active)
    {
      return true;
    }
    if(rect4Active)
    {
      return true;
    }
    if(rect5Active)
    {
      return true;
    }
    if(rect6Active)
    {
      return true;
    }
    if(rect7Active)
    {
      return true;
    }
    if(rect8Active)
    {
      return true;
    }
    return false;
}

bool SnakeGuy::getParticlesActive()
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

void SnakeGuy::move(vitaRect target)
{
  moveRect1(target);
  moveRect2(rect1);
  moveRect3(rect2);
  moveRect4(rect3);
  moveRect5(rect4);
  moveRect6(rect5);
  moveRect7(rect6);
  moveRect8(rect7);
}

void SnakeGuy::moveRect1(vitaRect target)
{
  double pi, tx, ty, angle, xVel, yVel;
  float rad;

  if(!rect1Active && head == 1) head = newHead();

  pi = 3.14159;
  tx = rect1.x - target.x;
  ty = rect1.y - target.y;

  angle = atan2(-ty, -tx) * 180 / pi;//angle for movement.
  rad = atan2(-ty, -tx);//radians for image rotation.
  xVel = 2*(cos(angle*pi/180));   // move x
  yVel = 2*(sin(angle*pi/180));   // move y

  if(!pause)
  {
    rect1.x += xVel;
    rect1.y += yVel;
  }
  if(rect1Active)
  {
    if(head == 1) vita2d_draw_texture_rotate(snakeImage2, rect1.x, rect1.y, rad);
    else vita2d_draw_texture_rotate(snakeImage1, rect1.x, rect1.y, rad);
  }
}

void SnakeGuy::moveRect2(vitaRect target)
{
  double pi, tx, ty, angle, xVel, yVel, distance;
  float rad;

  if(!rect2Active && head == 2) head = newHead();

  pi = 3.14159;
  tx = rect2.x - target.x;
  ty = rect2.y - target.y;

  angle = atan2(-ty, -tx) * 180 / pi;//angle for movement.
  rad = atan2(-ty, -tx);//radians for image rotation.
  xVel = 2*(cos(angle*pi/180));   // move x
  yVel = 2*(sin(angle*pi/180));   // move y
  distance = sqrt(tx * tx + ty * ty);

  if(!pause && distance > 15.0)
  {
    rect2.x += xVel;
    rect2.y += yVel;
  }
  if(rect2Active)
  {
    if(head == 2) vita2d_draw_texture_rotate(snakeImage2, rect2.x, rect2.y, rad);
    else vita2d_draw_texture_rotate(snakeImage1, rect2.x, rect2.y, rad);
  }
}
void SnakeGuy::moveRect3(vitaRect target)
{
  double pi, tx, ty, angle, xVel, yVel, distance;
  float rad;

  if(!rect3Active && head == 3) head = newHead();

  pi = 3.14159;
  tx = rect3.x - target.x;
  ty = rect3.y - target.y;

  angle = atan2(-ty, -tx) * 180 / pi;//angle for movement.
  rad = atan2(-ty, -tx);//radians for image rotation.
  xVel = 2*(cos(angle*pi/180));   // move x
  yVel = 2*(sin(angle*pi/180));   // move y
  distance = sqrt(tx * tx + ty * ty);

  if(!pause && distance > 15.0)
  {
    rect3.x += xVel;
    rect3.y += yVel;
  }
  
  if(rect3Active)
  {
    if(head == 3) vita2d_draw_texture_rotate(snakeImage2, rect3.x, rect3.y, rad);
    else vita2d_draw_texture_rotate(snakeImage1, rect3.x, rect3.y, rad);
  }
}
void SnakeGuy::moveRect4(vitaRect target)
{
  double pi, tx, ty, angle, xVel, yVel, distance;
  float rad;

  if(!rect4Active && head == 4) head = newHead();

  pi = 3.14159;
  tx = rect4.x - target.x;
  ty = rect4.y - target.y;

  angle = atan2(-ty, -tx) * 180 / pi;//angle for movement.
  rad = atan2(-ty, -tx);//radians for image rotation.
  xVel = 2*(cos(angle*pi/180));   // move x
  yVel = 2*(sin(angle*pi/180));   // move y
  distance = sqrt(tx * tx + ty * ty);

  if(!pause && distance > 15.0)
  {
    rect4.x += xVel;
    rect4.y += yVel;
  }
  if(rect4Active)
  {
    if(head == 4) vita2d_draw_texture_rotate(snakeImage2, rect4.x, rect4.y, rad);
    else vita2d_draw_texture_rotate(snakeImage1, rect4.x, rect4.y, rad);
  }
}
void SnakeGuy::moveRect5(vitaRect target)
{
  double pi, tx, ty, angle, xVel, yVel, distance;
  float rad;

  if(!rect5Active && head == 5) head = newHead();

  pi = 3.14159;
  tx = rect5.x - target.x;
  ty = rect5.y - target.y;

  angle = atan2(-ty, -tx) * 180 / pi;//angle for movement.
  rad = atan2(-ty, -tx);//radians for image rotation.
  xVel = 2*(cos(angle*pi/180));   // move x
  yVel = 2*(sin(angle*pi/180));   // move y
  distance = sqrt(tx * tx + ty * ty);

  if(!pause && distance > 15.0)
  {
    rect5.x += xVel;
    rect5.y += yVel;
  }
  if(rect5Active)
  {
    if(head == 5) vita2d_draw_texture_rotate(snakeImage2, rect5.x, rect5.y, rad);
    else vita2d_draw_texture_rotate(snakeImage1, rect5.x, rect5.y, rad);
  }
}
void SnakeGuy::moveRect6(vitaRect target)
{
  double pi, tx, ty, angle, xVel, yVel, distance;
  float rad;

  if(!rect6Active && head == 6) head = newHead();

  pi = 3.14159;
  tx = rect6.x - target.x;
  ty = rect6.y - target.y;

  angle = atan2(-ty, -tx) * 180 / pi;//angle for movement.
  rad = atan2(-ty, -tx);//radians for image rotation.
  xVel = 2*(cos(angle*pi/180));   // move x
  yVel = 2*(sin(angle*pi/180));   // move y
  distance = sqrt(tx * tx + ty * ty);

  if(!pause && distance > 15.0)
  {
    rect6.x += xVel;
    rect6.y += yVel;
  }
  if(rect6Active)
  {
    if(head == 6) vita2d_draw_texture_rotate(snakeImage2, rect6.x, rect6.y, rad);
    else vita2d_draw_texture_rotate(snakeImage1, rect6.x, rect6.y, rad);
  }
}
void SnakeGuy::moveRect7(vitaRect target)
{
  double pi, tx, ty, angle, xVel, yVel, distance;
  float rad;

  if(!rect7Active && head == 7) head = newHead();

  pi = 3.14159;
  tx = rect7.x - target.x;
  ty = rect7.y - target.y;

  angle = atan2(-ty, -tx) * 180 / pi;//angle for movement.
  rad = atan2(-ty, -tx);//radians for image rotation.
  xVel = 2*(cos(angle*pi/180));   // move x
  yVel = 2*(sin(angle*pi/180));   // move y
  distance = sqrt(tx * tx + ty * ty);

  if(!pause && distance > 15.0)
  {
    rect7.x += xVel;
    rect7.y += yVel;
  }
  if(rect7Active)
  {
    if(head == 7) vita2d_draw_texture_rotate(snakeImage2, rect7.x, rect7.y, rad);
    else vita2d_draw_texture_rotate(snakeImage1, rect7.x, rect7.y, rad);
  }
}
void SnakeGuy::moveRect8(vitaRect target)
{
  double pi, tx, ty, angle, xVel, yVel, distance;
  float rad;

  if(!rect8Active && head == 8) head = newHead();

  pi = 3.14159;
  tx = rect8.x - target.x;
  ty = rect8.y - target.y;

  angle = atan2(-ty, -tx) * 180 / pi;//angle for movement.
  rad = atan2(-ty, -tx);//radians for image rotation.
  xVel = 2*(cos(angle*pi/180));   // move x
  yVel = 2*(sin(angle*pi/180));   // move y
  distance = sqrt(tx * tx + ty * ty);

  if(!pause && distance > 15.0)
  {
    rect8.x += xVel;
    rect8.y += yVel;
  }
  if(rect8Active)
  {
    if(head == 8) vita2d_draw_texture_rotate(snakeImage2, rect8.x, rect8.y, rad);
    else vita2d_draw_texture_rotate(snakeImage1, rect8.x, rect8.y, rad);
  }
}

void SnakeGuy::moveBackX(double playerxVel)
{
  rect1.x -= playerxVel;
  rect2.x -= playerxVel;
  rect3.x -= playerxVel;
  rect4.x -= playerxVel;
  rect5.x -= playerxVel;
  rect6.x -= playerxVel;
  rect7.x -= playerxVel;
  rect8.x -= playerxVel;
  realTarget.x -= playerxVel;
  for(int i = 0; i < 15; i++)
  {
    particles[i].moveBackX(playerxVel);
  }
}

void SnakeGuy::moveBackY(double playeryVel)
{
  rect1.y -= playeryVel;
  rect2.y -= playeryVel;
  rect3.y -= playeryVel;
  rect4.y -= playeryVel;
  rect5.y -= playeryVel;
  rect6.y -= playeryVel;
  rect7.y -= playeryVel;
  rect8.y -= playeryVel;
  realTarget.y -= playeryVel;
  for(int i = 0; i < 15; i++)
  {
    particles[i].moveBackY(playeryVel);
  }
}

int SnakeGuy::newHead()
{
  switch (head) {
    case 1:
      return 2;
      break;
    case 2:
      return 3;
      break;
    case 3:
      return 4;
      break;
    case 4:
      return 5;
      break;
    case 5:
      return 6;
      break;
    case 6:
      return 7;
      break;
    case 7:
      return 8;
      break;
    case 8:
      return 8;
      break;
    default:
    return 8;
  }
}

bool SnakeGuy::takeDamage(vitaRect bullet, vitaRect target)
{
  switch (head) {
    case 1:
      if(checkCollision(bullet, rect1))
      {
        die();
        return true;
      }
      break;
    case 2:
      if(checkCollision(bullet, rect2))
      {
        die();
        return true;
      }
      break;
    case 3:
      if(checkCollision(bullet, rect3))
      {
        die();
        return true;
      }
      break;
    case 4:
      if(checkCollision(bullet, rect4))
      {
        die();
        return true;
      }
      break;
    case 5:
      if(checkCollision(bullet, rect5))
      {
        die();
        return true;
      }
      break;
    case 6:
      if(checkCollision(bullet, rect6))
      {
        die();
        return true;
      }
      break;
    case 7:
      if(checkCollision(bullet, rect7))
      {
        die();
        return true;
      }
      break;
    case 8:
      if(checkCollision(bullet, rect8))
      {
        die();
        return true;
      }
      break;
  }

  return false;
}

bool SnakeGuy::hit(vitaRect bullet)
{
  if(checkCollision(bullet, rect1) && rect1Active)
  {
    return true;
  }
  else if(checkCollision(bullet, rect2) && rect2Active)
  {
    return true;
  }
  else if(checkCollision(bullet, rect3) && rect3Active)
  {
    return true;
  }
  else if(checkCollision(bullet, rect4) && rect4Active)
  {
    return true;
  }
  else if(checkCollision(bullet, rect5) && rect5Active)
  {
    return true;
  }
  else if(checkCollision(bullet, rect6) && rect6Active)
  {
    return true;
  }
  else if(checkCollision(bullet, rect7) && rect7Active)
  {
    return true;
  }
  else if(checkCollision(bullet, rect8) && rect8Active)
  {
    return true;
  }

  return false;
}

void SnakeGuy::doStuff(vitaRect target, bool pause, vitaRect levelRect)
{
  this->pause = pause;
  
  if(getActive())
  {
    if(checkCollision(rect1, realTarget))
    {
      int x = levelRect.x;
      int y = levelRect.y;
      int w = levelRect.w;
      int h = levelRect.h;
      int tempx = rand() % w + x;
      int tempy = rand() % h + y;
      realTarget.x = tempx;
      realTarget.y = tempy;
    }
    move(realTarget);
  }
  if(dying && getActive())
  {
    for(int i = 0; i < 15; i++)
    {
      particles[i].doStuff(rect1, RGBA8(snakeColorR,snakeColorG,snakeColorB,255), pause);
    }
  }
  if(!getParticlesActive() && dying)
  {
    die();
  }
  if(spawning)
  {
    preSpawn();
  }
}
