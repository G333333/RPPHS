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

  realTarget.x = 0;
  realTarget.y = 0;
  realTarget.w = 1;
  realTarget.h = 1; 

  rect1Active = false;
  rect2Active = false;
  rect3Active = false;
  rect4Active = false;
  rect5Active = false;
  rect6Active = false;
  rect7Active = false;
  rect8Active = false;

  spawning = false;
  spawnCount = 0;
  spawnRadius = 0;

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
  this->levelRect = levelRect;

  int tempx, tempy;
  int x = levelRect.x;
  int y = levelRect.y;
  int w = levelRect.w;
  int h = levelRect.h;
  tempx = rand() % w + x;
  tempy = rand() % h + y;

  realTarget.x = rand() % w + x;
  realTarget.y = rand() % h + y;
  
  if(realTarget.x < levelRect.x) realTarget.x = levelRect.x;
  if(realTarget.x > levelRect.x + levelRect.w) realTarget.x = levelRect.x + levelRect.w - 10;
  if(realTarget.y < levelRect.y) realTarget.y = levelRect.x;
  if(realTarget.y> levelRect.y + levelRect.h) realTarget.y = levelRect.y - 10;

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
  switch (head) {
    case 1:
      temp = rect1;
      break;
    case 2:
      temp = rect2;
      break;
    case 3:
      temp = rect3;
      break;
    case 4:
      temp = rect4;
      break;
    case 5:
      temp = rect5;
      break;
    case 6:
      temp = rect6;
      break;
    case 7:
      temp = rect7;
      break;
    case 8:
      temp = rect8;
      break;
  }
  rect1Active = false;
  rect2Active = false;
  rect3Active = false;
  rect4Active = false;
  rect5Active = false;
  rect6Active = false;
  rect7Active = false;
  rect8Active = false;
  int tempSpeed = 0;
  int tempLife = 0;
  for(int i = 0; i < 15; i++)
  {
    tempSpeed = rand() % 2 + 1;
    tempLife = rand() % 20 + 1;
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

int SnakeGuy::chooseDirection(vitaRect target)
{
  int choice = 0;
  vitaRect temp;
  switch (head) {
    case 1:
      temp = rect1;
      break;
    case 2:
      temp = rect2;
      break;
    case 3:
      temp = rect3;
      break;
    case 4:
      temp = rect4;
      break;
    case 5:
      temp = rect5;
      break;
    case 6:
      temp = rect6;
      break;
    case 7:
      temp = rect7;
      break;
    case 8:
      temp = rect8;
      break;
  }

  int distanceX = temp.x - target.x;
  int distanceY = temp.y - target.y;

  if(distanceX < 0)
  {
    distanceX *= -1; //make it positive
  }
  if(distanceY < 0)
  {
    distanceY *= -1; //make it positive
  }

  if(distanceX > distanceY)
  {
    if(target.x > temp.x)
    {
      choice = 1;
    }
    else
      choice = 2;
  }
  else
  {
    if(target.y > temp.y)
    {
      choice = 3;
    }
    else
      choice = 4;
  }


  return choice;
}

void SnakeGuy::move(vitaRect target, int choice)
{

  if(choice != 5)
  {
    choice = chooseDirection(target);
  }

  switch (head) {
      case 1:
        if(rect8Active) moveRect8(rect1, choice);
        else if(rect7Active) moveRect7(rect1, choice);
        else if(rect6Active) moveRect6(rect1, choice);
        else if(rect5Active) moveRect5(rect1, choice);
        else if(rect4Active) moveRect4(rect1, choice);
        else if(rect3Active) moveRect3(rect1, choice);
        else if(rect2Active) moveRect2(rect1, choice);
        else moveRect1(rect1, choice);
        break;

      case 2:
        if(rect1Active) moveRect1(rect2, choice);
        else if(rect8Active) moveRect8(rect2, choice);
        else if(rect7Active) moveRect7(rect2, choice);
        else if(rect6Active) moveRect6(rect2, choice);
        else if(rect5Active) moveRect5(rect2, choice);
        else if(rect4Active) moveRect4(rect2, choice);
        else if(rect3Active) moveRect3(rect2, choice);
        else moveRect2(rect2, choice);
        break;

      case 3:
        if(rect2Active) moveRect2(rect3, choice);
        else if(rect1Active) moveRect1(rect3, choice);
        else if(rect8Active) moveRect8(rect3, choice);
        else if(rect7Active) moveRect7(rect3, choice);
        else if(rect6Active) moveRect6(rect3, choice);
        else if(rect5Active) moveRect5(rect3, choice);
        else if(rect4Active) moveRect4(rect3, choice);
        else moveRect3(rect3, choice);
        break;

      case 4:
        if(rect3Active) moveRect3(rect4, choice);
        else if(rect2Active) moveRect2(rect4, choice);
        else if(rect1Active) moveRect1(rect4, choice);
        else if(rect8Active) moveRect8(rect4, choice);
        else if(rect7Active) moveRect7(rect4, choice);
        else if(rect6Active) moveRect6(rect4, choice);
        else if(rect5Active) moveRect5(rect4, choice);
        else moveRect4(rect4, choice);
        break;

      case 5:
        if(rect4Active) moveRect4(rect5, choice);
        else if(rect3Active) moveRect3(rect5, choice);
        else if(rect2Active) moveRect2(rect5, choice);
        else if(rect1Active) moveRect1(rect5, choice);
        else if(rect8Active) moveRect8(rect5, choice);
        else if(rect7Active) moveRect7(rect5, choice);
        else if(rect6Active) moveRect6(rect5, choice);
        else moveRect5(rect5, choice);
        break;

      case 6:
        if(rect5Active) moveRect5(rect6, choice);
        else if(rect4Active) moveRect4(rect6, choice);
        else if(rect3Active) moveRect3(rect6, choice);
        else if(rect2Active) moveRect2(rect6, choice);
        else if(rect1Active) moveRect1(rect6, choice);
        else if(rect8Active) moveRect8(rect6, choice);
        else if(rect7Active) moveRect7(rect6, choice);
        else moveRect6(rect6, choice);
        break;

      case 7:
        if(rect6Active) moveRect6(rect7, choice);
        else if(rect5Active) moveRect5(rect7, choice);
        else if(rect4Active) moveRect4(rect7, choice);
        else if(rect3Active) moveRect3(rect7, choice);
        else if(rect2Active) moveRect2(rect7, choice);
        else if(rect1Active) moveRect1(rect7, choice);
        else if(rect8Active) moveRect8(rect7, choice);
        else moveRect7(rect7, choice);
        break;

      case 8:
        if(rect7Active) moveRect7(rect8, choice);
        else if(rect6Active) moveRect6(rect8, choice);
        else if(rect5Active) moveRect5(rect8, choice);
        else if(rect4Active) moveRect4(rect8, choice);
        else if(rect3Active) moveRect3(rect8, choice);
        else if(rect2Active) moveRect2(rect8, choice);
        else if(rect1Active) moveRect1(rect8, choice);
        else moveRect8(rect8, choice);
        break;
  }
}

void SnakeGuy::moveRect1(vitaRect start, int choice)
{
  head = 1;
  switch (choice) {
    case 1:
      rect1.x = start.x + 17;
      rect1.y = start.y;
      break;
    case 2:
      rect1.x = start.x - 17;
      rect1.y = start.y;
      break;
    case 3:
      rect1.y = start.y + 17;
      rect1.x = start.x;
      break;
    case 4:
      rect1.y = start.y - 17;
      rect1.x = start.x;
      break;
    case 5:
      rect1.x = start.x;
      rect1.y = start.y;
      break;
  }
}

void SnakeGuy::moveRect2(vitaRect start, int choice)
{
  head = 2;
  switch (choice) {
    case 1:
      rect2.x = start.x + 17;
      rect2.y = start.y;
      break;
    case 2:
      rect2.x = start.x - 17;
      rect2.y = start.y;
      break;
    case 3:
      rect2.y = start.y + 17;
      rect2.x = start.x;
      break;
    case 4:
      rect2.y = start.y - 17;
      rect2.x = start.x;
      break;
    case 5:
      rect2.x = start.x;
      rect2.y = start.y;
      break;
  }
}

void SnakeGuy::moveRect3(vitaRect start, int choice)
{
  head = 3;
  switch (choice) {
    case 1:
      rect3.x = start.x + 17;
      rect3.y = start.y;
      break;
    case 2:
      rect3.x = start.x - 17;
      rect3.y = start.y;
      break;
    case 3:
      rect3.y = start.y + 17;
      rect3.x = start.x;
      break;
    case 4:
      rect3.y = start.y - 17;
      rect3.x = start.x;
      break;
    case 5:
      rect3.x = start.x;
      rect3.y = start.y;
      break;
  }
}

void SnakeGuy::moveRect4(vitaRect start, int choice)
{
  head = 4;
  switch (choice) {
    case 1:
      rect4.x = start.x + 17;
      rect4.y = start.y;
      break;
    case 2:
      rect4.x = start.x - 17;
      rect4.y = start.y;
      break;
    case 3:
      rect4.y = start.y + 17;
      rect4.x = start.x;
      break;
    case 4:
      rect4.y = start.y - 17;
      rect4.x = start.x;
      break;
    case 5:
      rect4.x = start.x;
      rect4.y = start.y;
      break;
  }
}

void SnakeGuy::moveRect5(vitaRect start, int choice)
{
  head = 5;
  switch (choice) {
    case 1:
      rect5.x = start.x + 17;
      rect5.y = start.y;
      break;
    case 2:
      rect5.x = start.x - 17;
      rect5.y = start.y;
      break;
    case 3:
      rect5.y = start.y + 17;
      rect5.x = start.x;
      break;
    case 4:
      rect5.y = start.y - 17;
      rect5.x = start.x;
      break;
  }
}

void SnakeGuy::moveRect6(vitaRect start, int choice)
{
  head = 6;
  switch (choice) {
    case 1:
      rect6.x = start.x + 17;
      rect6.y = start.y;
      break;
    case 2:
      rect6.x = start.x - 17;
      rect6.y = start.y;
      break;
    case 3:
      rect6.y = start.y + 17;
      rect6.x = start.x;
      break;
    case 4:
      rect6.y = start.y - 17;
      rect6.x = start.x;
      break;
    case 5:
      rect6.x = start.x;
      rect6.y = start.y;
      break;
  }
}

void SnakeGuy::moveRect7(vitaRect start, int choice)
{
  head = 7;
  switch (choice) {
    case 1:
      rect7.x = start.x + 17;
      rect7.y = start.y;
      break;
    case 2:
      rect7.x = start.x - 17;
      rect7.y = start.y;
      break;
    case 3:
      rect7.y = start.y + 17;
      rect7.x = start.x;
      break;
    case 4:
      rect7.y = start.y - 17;
      rect7.x = start.x;
      break;
    case 5:
      rect7.x = start.x;
      rect7.y = start.y;
      break;
  }
}

void SnakeGuy::moveRect8(vitaRect start, int choice)
{
  head = 8;
  switch (choice) {
    case 1:
      rect8.x = start.x + 17;
      rect8.y = start.y;
      break;
    case 2:
      rect8.x = start.x - 17;
      rect8.y = start.y;
      break;
    case 3:
      rect8.y = start.y + 17;
      rect8.x = start.x;
      break;
    case 4:
      rect8.y = start.y - 17;
      rect8.x = start.x;
      break;
    case 5:
      rect8.x = start.x;
      rect8.y = start.y;
      break;
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
  for(int i = 0; i < 15; i++)
  {
    particles[i].moveBackY(playeryVel);
  }
}

int SnakeGuy::newHead()
{
  switch (head) {
    case 1:
      if(rect2Active) return 2;
      else if(rect3Active) return 3;
      else if(rect4Active) return 4;
      else if(rect5Active) return 5;
      else if(rect6Active) return 6;
      else if(rect7Active) return 7;
      else if(rect8Active) return 8;
      else return 1;
      break;
    case 2:
      if(rect3Active) return 3;
      else if(rect4Active) return 4;
      else if(rect5Active) return 5;
      else if(rect6Active) return 6;
      else if(rect7Active) return 7;
      else if(rect8Active) return 8;
      else if(rect1Active) return 1;
      else return 2;
      break;
    case 3:
      if(rect4Active) return 4;
      else if(rect5Active) return 5;
      else if(rect6Active) return 6;
      else if(rect7Active) return 7;
      else if(rect8Active) return 8;
      else if(rect1Active) return 1;
      else if(rect2Active) return 2;
      else return 3;
      break;
    case 4:
      if(rect5Active) return 5;
      else if(rect6Active) return 6;
      else if(rect7Active) return 7;
      else if(rect8Active) return 8;
      else if(rect1Active) return 1;
      else if(rect2Active) return 2;
      else if(rect3Active) return 3;
      else return 4;
      break;
    case 5:
      if(rect6Active) return 6;
      else if(rect7Active) return 7;
      else if(rect8Active) return 8;
      else if(rect1Active) return 1;
      else if(rect2Active) return 2;
      else if(rect3Active) return 3;
      else if(rect4Active) return 4;
      else return 5;
      break;
    case 6:
      if(rect7Active) return 7;
      else if(rect8Active) return 8;
      else if(rect1Active) return 1;
      else if(rect2Active) return 2;
      else if(rect3Active) return 3;
      else if(rect4Active) return 4;
      else if(rect5Active) return 5;
      else return 6;
      break;
    case 7:
      if(rect8Active) return 8;
      else if(rect1Active) return 1;
      else if(rect2Active) return 2;
      else if(rect3Active) return 3;
      else if(rect4Active) return 4;
      else if(rect5Active) return 5;
      else if(rect6Active) return 6;
      else return 7;
      break;
    case 8:
      if(rect1Active) return 1;
      else if(rect2Active) return 2;
      else if(rect3Active) return 3;
      else if(rect4Active) return 4;
      else if(rect5Active) return 5;
      else if(rect6Active) return 6;
      else if(rect7Active) return 7;
      else return 8;
      break;
  }
  return 1;
}

bool SnakeGuy::takeDamage(vitaRect bullet, vitaRect target)
{
  switch (head) {
    case 1:
      if(checkCollision(bullet, rect1))
      {
        rect1Active = false;
        head = newHead();
        if(!getActive())
        {
          die();
        }
        return true;
      }
      break;
    case 2:
      if(checkCollision(bullet, rect2))
      {
        rect2Active = false;
        head = newHead();
        if(!getActive())
        {
          die();
        }
        return true;
      }
      break;
    case 3:
      if(checkCollision(bullet, rect3))
      {
        rect3Active = false;
        head = newHead();
        if(!getActive())
        {
          die();
        }
        return true;
      }
      break;
    case 4:
      if(checkCollision(bullet, rect4))
      {
        rect4Active = false;
        head = newHead();
        if(!getActive())
        {
          die();
        }
        return true;
      }
      break;
    case 5:
      if(checkCollision(bullet, rect5))
      {
        rect5Active = false;
        head = newHead();
        if(!getActive())
        {
          die();
        }
        return true;
      }
      break;
    case 6:
      if(checkCollision(bullet, rect6))
      {
        rect6Active = false;
        head = newHead();
        if(!getActive())
        {
          die();
        }
        return true;
      }
      break;
    case 7:
      if(checkCollision(bullet, rect7))
      {
        rect7Active = false;
        head = newHead();
        if(!getActive())
        {
          die();
        }
        return true;
      }
      break;
    case 8:
      if(checkCollision(bullet, rect8))
      {
        rect8Active = false;
        head = newHead();
        if(!getActive())
        {
          die();
        }
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

void SnakeGuy::doStuff(vitaRect target, bool pause)
{
  targetTimer++;
  
  if(targetTimer > 300)
  {
    targetTimer = 0;
    realTarget.x = rand() % 400 + (target.x - 200);
    realTarget.y = rand() % 400 + (target.y - 200);

    if(realTarget.x < levelRect.x) realTarget.x = levelRect.x;
    if(realTarget.x > levelRect.x + levelRect.w) realTarget.x = levelRect.x + levelRect.w - 10;
    if(realTarget.y < levelRect.y) realTarget.y = levelRect.x;
    if(realTarget.y> levelRect.y + levelRect.h) realTarget.y = levelRect.y - 10;
  }
  this->pause = pause;
  //keep the rects together for when spawning particles is needed.
  vitaRect tempRect;
  switch (head) {
    case 1:
      tempRect = rect1;
      break;
    case 2:
      tempRect = rect2;
      break;
    case 3:
      tempRect = rect3;
      break;
    case 4:
      tempRect = rect4;
      break;
    case 5:
      tempRect = rect5;
      break;
    case 6:
      tempRect = rect6;
      break;
    case 7:
      tempRect = rect7;
      break;
    case 8:
      tempRect = rect8;
      break;
  }
  if(!rect1Active)
  {
    rect1.x = tempRect.x;
    rect1.y = tempRect.y;
  }
  if(!rect2Active)
  {
    rect2.x = tempRect.x;
    rect2.y = tempRect.y;
  }
  if(!rect3Active)
  {
    rect3.x = tempRect.x;
    rect3.y = tempRect.y;
  }
  if(!rect4Active)
  {
    rect4.x = tempRect.x;
    rect4.y = tempRect.y;
  }
  if(!rect5Active)
  {
    rect5.x = tempRect.x;
    rect5.y = tempRect.y;
  }
  if(!rect6Active)
  {
    rect6.x = tempRect.x;
    rect6.y = tempRect.y;
  }
  if(!rect7Active)
  {
    rect7.x = tempRect.x;
    rect7.y = tempRect.y;
  }
  if(!rect8Active)
  {
    rect8.x = tempRect.x;
    rect8.y = tempRect.y;
  }
  //end of keeping rects together.
  if(getActive())
  {
    if(!pause)
    {
      moveInterval++;
    }

    if(moveInterval > 15)
    {
      move(realTarget);
      moveInterval = 0;
    }

    if(rect1Active)
    {
      if(head == 1)
      {
        vita2d_draw_texture(snakeImage2, rect1.x, rect1.y);
      }
      else
      vita2d_draw_texture(snakeImage1, rect1.x, rect1.y);
    }
    if(rect2Active)
    {
      if(head == 2)
      {
        vita2d_draw_texture(snakeImage2, rect2.x, rect2.y);
      }
      else
      vita2d_draw_texture(snakeImage1, rect2.x, rect2.y);
    }
    if(rect3Active)
    {
      if(head == 3)
      {
        vita2d_draw_texture(snakeImage2, rect3.x, rect3.y);
      }
      else
      vita2d_draw_texture(snakeImage1, rect3.x, rect3.y);
    }
    if(rect4Active)
    {
      if(head == 4)
      {
        vita2d_draw_texture(snakeImage2, rect4.x, rect4.y);
      }
      else
      vita2d_draw_texture(snakeImage1, rect4.x, rect4.y);
    }
    if(rect5Active)
    {
      if(head == 5)
      {
        vita2d_draw_texture(snakeImage2, rect5.x, rect5.y);
      }
      else
      vita2d_draw_texture(snakeImage1, rect5.x, rect5.y);
    }
    if(rect6Active)
    {
      if(head == 6)
      {
        vita2d_draw_texture(snakeImage2, rect6.x, rect6.y);
      }
      else
      vita2d_draw_texture(snakeImage1, rect6.x, rect6.y);
    }
    if(rect7Active)
    {
      if(head == 7)
      {
        vita2d_draw_texture(snakeImage2, rect7.x, rect7.y);
      }
      else
      vita2d_draw_texture(snakeImage1, rect7.x, rect7.y);
    }
    if(rect8Active)
    {
      if(head == 8)
      {
        vita2d_draw_texture(snakeImage2, rect8.x, rect8.y);
      }
      else
      vita2d_draw_texture(snakeImage1, rect8.x, rect8.y);
    }
  }
  if(!getActive())
  {
    for(int i = 0; i < 15; i++)
    {
      particles[i].doStuff(rect1, RGBA8(snakeColorR,snakeColorG,snakeColorB,255), pause);
    }
  }
  if(spawning)
  {
    preSpawn();
  }
}
