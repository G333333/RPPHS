#include"classic.h"

void Classic::init(double levelWidth, double levelHeight)
{
  god = true;

  levelRect.x = -240;
  levelRect.y = -139;
  levelRect.w = levelWidth;
  levelRect.h = levelHeight;
  status = 1;
  quit = false;
  pause = false;
  startNeedsReset = false;

  points = 0;
  multiplyer = 1;
  killCount = 0;
  mpUpgrade = 5;

  lifeUpgrade = 60000;

  bulletUpgrade = 10000;
  bulletInterval = 3;
  bulletSetting = 1;

  player.init();
  extraLives = 4;
  for(int i = 0; i < 50; i++)
  {
    bullets[i].init();
  }
  bulletCounter = 0;
  bulletTimer = 0;
  playGunSound = false;
  playExp = false;

  safeTime = 0;
  spawnTime = 0;

  garys.resize(10);  
  garyTotal = 10;
  garysAlive = 0;
  for(int i = 0; i < garyTotal; i++)
  {
    garys[i].init();
  }

  karenTotal = 10;
  karens.resize(10);
  for(int i = 0; i < karenTotal; i++)
  {
    karens[i].init();
  }

  jeffTotal = 10;
  jeffsAlive = 0;
  jeffs.resize(10);
  for(int i = 0; i < jeffTotal; i++)
  {
    jeffs[i].init();
  }

  miniJeffTotal = 9;
  miniJeffs.resize(9);
  for(int i = 0; i < miniJeffTotal; i++)
  {
    miniJeffs[i].init();
  }

  snakeTotal = 10;
  snakeGuys.resize(10);
  for(int i = 0; i < snakeTotal; i++)
  {
    snakeGuys[i].init();
  }

  particleCount = 10;
  bombReset = false;
  bombCount = 3;
  bombUpgrade = 80000;
  for(int i = 0; i < particleCount; i++)
  {
    bombParticles[i].init();
  }

  //spawn events 
  eventTimer = 0;
  garyEvent = false;
  jeffEvent = false;
}

void Classic::doStuff(bool keys[15],
                      double lx,
                      double ly,
                      double rx,
                      double ry,
                      int batteryPercent,
                      bool showFps,
                      bool showCursor,
                      bool showBattery,
                      int cursorSetting,
                      int deadZone)
{
  vita2d_draw_texture_scale(gameBackground, levelRect.x, levelRect.y, 1.61, 1.36);

  if((keys[6] && pause) || (keys[6] && extraLives <= 0 && !player.getActive()))
  {
    status = 1;
  }

  if(keys[5] && pause)
  {
    pause = false;
  }
  if(keys[10] && !startNeedsReset)
  {
    startNeedsReset = true;
    if(!pause)
    {
      pause = true;
    }
  }
  else if(!keys[10])
  {
    startNeedsReset = false;
  }

  if((keys[13] && !bombReset) || (keys[14] && !bombReset))
  {
    if(player.getActive() && !bombActive() && bombCount > 0)
    {
      bombReset = true;
      int tempSpeed = 0;
      int tempLife = 0;
      vitaRect tempRect;
      tempRect.x = player.getRect().x + player.getRect().w / 2;
      tempRect.y = player.getRect().y + player.getRect().h / 2;
      tempRect.w = 0;
      tempRect.h = 0;
      bombCount -= 1;
      for(int i = 0; i < particleCount; i++)
      {
        tempSpeed = rand() % 5 + 1;
        tempLife = rand() % 60 + 1;
        bombParticles[i].spawn(tempRect, tempSpeed, tempLife);
        rand(); rand();
      }
    }
  }
  if(!keys[13] && !keys[14])
  {
    bombReset = false;
  }

  playGunSound = false;
  playExp = false; //set this to false each frame.
  if(125 - rx < -deadZone || 125 - rx > deadZone || 130 - ry < -deadZone || 130 - ry > deadZone)//if joystick is past deadzone
  {
    if(!pause)
    {
      if(player.getActive())
      {
        bulletTimer++;
        drawCursor(rx, ry, showCursor, cursorSetting);
      }
    }
    if(bulletTimer > bulletInterval)
    {//pass rx, and ry(joystick coordinates) to the bullet as well as the player rect
      playGunSound = true;
      bullets[bulletCounter].spawn(rx,ry,player.getRect());
      bulletCounter++; // Play the wave
      if(bulletCounter >= 49)
      {
        bulletCounter = 0;
      }

      if(bulletSetting == 2)
      {
        int tempx = rx;
        int tempy = ry;
        if(rx > 62.5 && rx < 186.5)
        {
          tempx = rx - 20;
        }
        else if(rx <= 62.5 || rx >= 187.5)
        {
          tempy = ry - 20;
        }
        bullets[bulletCounter].spawn(tempx, tempy, player.getRect());
        bulletCounter++;
        if(bulletCounter >= 49)
        {
          bulletCounter = 0;
        }
      }
      bulletTimer = 0;
    }
  }


  //set the bullet interval, and weather it shoots two or one bullets.
  if(points >= bulletUpgrade && points < 100000)
  {
    bulletSetting++;
    bulletUpgrade += 10000;
    if(bulletSetting > 2)
    {
      bulletSetting = 1;
    }
    if(bulletSetting == 1)
    {
      bulletInterval = 5;
    }
    else if(bulletSetting == 2)
    {
      bulletInterval = 6;
    }
  }
  else if(points >= 100000)
  {
    bulletSetting = 2;
  }

  if(points >= lifeUpgrade)
  {
    extraLives++;
    lifeUpgrade += lifeUpgrade;
  }

  if(points >= bombUpgrade)
  {
    bombCount += 1;
    bombUpgrade += 80000;
  }

  player.doStuff(lx, ly, deadZone, levelRect, pause);

  for(int i = 0; i < 50; i++)
  {//do bullets. duh
    bullets[i].doStuff(levelRect, player.getRect(), pause);
  }

  for(int i = 0; i < particleCount; i++)
  {
    int tempRed = rand() % 255 + 1;
    int tempGreen = rand() % 255 + 1;
    int tempBlue = rand() % 255 + 1;
    bombParticles[i].doStuff(player.getRect(), RGBA8(tempRed, tempGreen, tempBlue, 255), pause);
  }

  checkGarys();
  for(int i = 0; i < garyTotal; i++)
  {//move garys and check if they are dead.
    garys[i].doStuff(player.getRect(), pause, levelRect);
  }

  checkKarens();
  for(int i = 0; i < karenTotal; i++)
  {
    karens[i].doStuff(levelRect, pause);
  }

  checkJeffs();
  for(int i = 0; i < jeffTotal; i++)
  {
    jeffs[i].doStuff(levelRect, player.getRect(), pause);
  }

  checkMiniJeffs();
  for(int i = 0; i < miniJeffTotal; i++)
  {
    miniJeffs[i].doStuff(pause, levelRect);
  }

  checkSnakeGuys();
  for(int i = 0; i < snakeTotal; i++)
  {
    snakeGuys[i].doStuff(player.getRect(), pause);
  }

  if(!pause)
  {
    spawnStuff();
    if(points > 0)
    {
      if(eventTimer <= 900)
      {
        eventTimer++;
      }
      if(eventTimer >= 900)
      {
        if(!garyEvent && !jeffEvent)
        {
          int event = rand() % 10;
          if(event < 5) garyEvent = true;
          if(event >= 5) jeffEvent = true;
        }
      }
    }
  }

  if(checkPlayer())
  {
    killPlayer();
  }

  if(bombActive())
  {
    checkBomb();
  }

  if(extraLives <= 0 && !player.getActive())
  {
    gameOver();
    killPlayer();
    playGunSound = false;
    playExp = false;
  }

  drawEmptyRect(levelRect, RGBA8(menuBorderR,menuBorderG,menuBorderB,255));
  checkMap();

  drawHud(batteryPercent, showBattery, showFps);

  if(pause)
  {
    pauseMenu();
  }

  /**quick reference:
    keys[0] = up;
    keys[1] = down;
    keys[2] = left;
    keys[3] = right;
    keys[4] = cross;
    keys[5] = square;
    keys[6] = triangle;
    keys[7] = circle;
    keys[8] = ly Up
    keys[9] = ly Down; **/
}

int Classic::getStatus()
{
  return status;
}

void Classic::setStatus(int status)
{//this object.status = provided.status{}
  this->status = status;
}

bool Classic::getQuit()
{
  return quit;
}

void Classic::checkGarys()
{
  //here we will move the garys on their x axis, then check for collision with other garys,
  //if there is collision, move them back.
  //then do the same on the y axis.
  //might as well check for bullets while we are here.
  //only enemies that will group together need to check for each other.
  //still check for bullets though.
  for(int i = 0; i < garyTotal; i++)
  {
    garys[i].moveX();
    for(int x = 0; x < garyTotal; x++)
    {
      if(i != x)
      {
        if((checkCollision(garys[i].getRect(), garys[x].getRect()) && garys[x].getActive() && garys[i].getActive() ) ||
           (checkCollision(garys[i].getRect(), garys[x].getRect()) && garys[x].getSpawning() && garys[i].getActive() ) )
        {
          garys[i].moveBackX();
        }
      }
    }
    garys[i].moveY();
    for(int x = 0; x < garyTotal; x++)
    {
      if(i != x)
      {
        if((checkCollision(garys[i].getRect(), garys[x].getRect()) && garys[x].getActive() && garys[i].getActive() ) ||
           (checkCollision(garys[i].getRect(), garys[x].getRect()) && garys[x].getSpawning() && garys[i].getActive() ) )
        {
          garys[i].moveBackY();
        }
      }
    }
    for(int x = 0; x < 50; x++)
    {
      if(checkCollision(garys[i].getRect(), bullets[x].getRect()) && bullets[x].getActive() && garys[i].getActive())
      {
        bullets[x].die();
        garys[i].die();
        garysAlive -= 1;
        points += 14 * multiplyer;
        killCount++;
        playExp = true;
        if(killCount >= mpUpgrade)
        {
          multiplyer++;
          if(mpUpgrade <= 75)
          {
            mpUpgrade = mpUpgrade + mpUpgrade;
          }
          else
          {
            mpUpgrade += 75;
          }
        }
      }
    }
  }
}

void Classic::spawnGary(int index, int x, int y)
{
  if(garyTotal == 0) garyTotal = 1;
  if(garysAlive >= garyTotal && garyTotal <= 20)
  {
    garys.resize(garyTotal * 2);
    garyTotal = garyTotal * 2;
  }
  else if(garysAlive >= garyTotal && garyTotal < 40) //stop it from going over 40 by doubling. 
  {
    garyTotal = 40;
    garys.resize(garyTotal);
  }
  garys[index].init();
  garys[index].spawn(levelRect, x, y);
  for(int i = 0; i < garyTotal; i++)
  {
    if((checkCollision(garys[i].getRect(), garys[index].getRect()) && garys[i].getActive() && i != index) ||
        (checkCollision(garys[i].getRect(), garys[index].getRect()) && garys[i].getSpawning() && i != index)) //cant spawn on an active gary. they will get stuck
    {
      spawnGary(index, x, y);
    }
  }
}

void Classic::checkKarens()
{
  //here we will move the garys on their x axis, then check for collision with other garys,
  //if there is collision, move them back.
  //then do the same on the y axis.
  //might as well check for bullets while we are here.
  //only enemies that will group together need to check for each other.
  //still check for bullets though.
  for(int i = 0; i < karenTotal; i++)
  {
    karens[i].moveX();
    for(int x = 0; x < karenTotal; x++)
    {
      if(i != x)
      {
        if( (checkCollision(karens[i].getRect(), karens[x].getRect()) && karens[x].getActive() && karens[i].getActive() ) ||
              (checkCollision(karens[i].getRect(), karens[x].getRect()) && karens[x].getSpawning() && karens[i].getActive() ))
        {
          karens[i].moveBackX();
        }
      }
    }
    karens[i].moveY();
    for(int x = 0; x < karenTotal; x++)
    {
      if(i != x)
      {
        if(checkCollision(karens[i].getRect(), karens[x].getRect()) && karens[x].getActive())
        {
          karens[i].moveBackY();
        }
      }
    }
    for(int x = 0; x < 50; x++)
    {
      if(checkCollision(karens[i].getRect(), bullets[x].getRect()) && bullets[x].getActive() && karens[i].getActive())
      {
        bullets[x].die();
        karens[i].die();
        points += 12 * multiplyer;
        killCount++;
        playExp = true;
        if(killCount >= mpUpgrade)
        {
          multiplyer++;
          if(mpUpgrade <= 75)
          {
            mpUpgrade = mpUpgrade + mpUpgrade;
          }
          else
          {
            mpUpgrade += 75;
          }
        }
      }
    }
  }
}

void Classic::spawnKaren(int index)
{
  karens[index].spawn(levelRect);
  for(int i = 0; i < karenTotal; i++)
  {
    if( (checkCollision(karens[i].getRect(), karens[index].getRect()) && karens[i].getActive() && i != index) ||
        (checkCollision(karens[i].getRect(), karens[index].getRect()) && karens[i].getSpawning() && i != index)) //cant spawn on an active gary. they will get stuck
    {
      spawnKaren(index);
    }
  }
}

void Classic::checkJeffs()
{
  //here we will move the garys on their x axis, then check for collision with other garys,
  //if there is collision, move them back.
  //then do the same on the y axis.
  //might as well check for bullets while we are here.
  //only enemies that will group together need to check for each other.
  //still check for bullets though.
  for(int i = 0; i < jeffTotal; i++)
  {
    jeffs[i].moveX();
    for(int x = 0; x < jeffTotal; x++)
    {
      if(i != x)
      {
        if( (checkCollision(jeffs[i].getRect(), jeffs[x].getRect()) && jeffs[x].getActive() && jeffs[i].getActive() ) ||
            (checkCollision(jeffs[i].getRect(), jeffs[x].getRect()) && jeffs[x].getSpawning() && jeffs[i].getActive()))
        {
          jeffs[i].moveBackX();
        }
      }
    }
    jeffs[i].moveY();
    for(int x = 0; x < jeffTotal; x++)
    {
      if(i != x)
      {
        if(checkCollision(jeffs[i].getRect(), jeffs[x].getRect()) && jeffs[x].getActive())
        {
          jeffs[i].moveBackY();
        }
      }
    }
    for(int x = 0; x < 50; x++)
    {
      if(checkCollision(jeffs[i].getRect(), bullets[x].getRect()) && bullets[x].getActive() && jeffs[i].getActive())
      {
        bullets[x].die();
        jeffs[i].die();
        jeffsAlive -= 1;
        points += 16 * multiplyer;
        killCount++;
        playExp = true;
        if(killCount >= mpUpgrade)
        {
          multiplyer++;
          if(mpUpgrade <= 75)
          {
            mpUpgrade = mpUpgrade + mpUpgrade;
          }
          else
          {
            mpUpgrade += 75;
          }
        }

        //miniJeff spawning.
        int miniJeffCount = 0; //counts the non-active miniJeffs
        for(int c = 0; c < miniJeffTotal; c++)
        {
          if(miniJeffs[c].getActive() == false)
          {
            miniJeffCount++;
          }
          if(miniJeffCount >= 3)
          {
            miniJeffCount = 0;
            for(int d = 0; d < miniJeffTotal; d++)
            {
              if(miniJeffs[d].getActive() == false)
              {
                double tempAngle;
                switch (miniJeffCount) {
                  case 0:
                    tempAngle = jeffs[i].getAngle() + 45;
                    break;
                  case 1:
                    tempAngle = jeffs[i].getAngle() + 180;
                    break;
                  case 2:
                    tempAngle = jeffs[i].getAngle() - 45;
                    break;
                  }

                if(tempAngle > 360)
                {
                  int temp = tempAngle - 360;
                  tempAngle = 0 + temp;
                }
                if(tempAngle < 0)
                {
                  int temp = 0 - tempAngle;
                  tempAngle = 360 - temp;
                }
                miniJeffs[d].spawn(jeffs[i].getRect(), tempAngle);
                miniJeffCount++;
              }
              if(miniJeffCount > 2)
              {
                break;
              }
            }
            break;
          }
        } //end miniJeff spawning.
      }
    }
  }
}

void Classic::spawnJeff(int index, int x, int y)
{
  jeffs[index].spawn(levelRect, x, y);
  for(int i = 0; i < jeffTotal; i++)
  {
    if( (checkCollision(jeffs[i].getRect(), jeffs[index].getRect()) && jeffs[i].getActive() && i != index) ||
        (checkCollision(jeffs[i].getRect(), jeffs[index].getRect()) && jeffs[i].getSpawning() && i != index)) //cant spawn on an active gary. they will get stuck
    {//if collision upon spawn. spawn again because it will get stuck.
      spawnJeff(index, x, y);
    }
  }
}

void Classic::checkMiniJeffs()
{
  for(int
    i = 0; i < miniJeffTotal; i++)
  {
    for(int x = 0; x < 50; x++)
    {
      if(checkCollision(miniJeffs[i].getRect(), bullets[x].getRect()) && miniJeffs[i].getActive() && bullets[x].getActive())
      {
        bullets[x].die();
        miniJeffs[i].die();
        points += 24 * multiplyer;
        killCount++;
        playExp = true;
        if(killCount >= mpUpgrade)
        {
          multiplyer++;
          if(mpUpgrade <= 75)
          {
            mpUpgrade = mpUpgrade + mpUpgrade;
          }
          else
          {
            mpUpgrade += 75;
          }
        }
      }
    }
  }
}

void Classic::checkSnakeGuys()
{
  for(int i = 0; i < snakeTotal; i++)
  {
    for(int x = 0; x < 50; x++)
    {
      if(snakeGuys[i].getActive() && bullets[x].getActive())
      {
          if(snakeGuys[i].takeDamage(bullets[x].getRect(),player.getRect())) //takeDamage function checks if bullet hit the head of snake and if so destoys the head.
          {
            bullets[x].die();
            points += 32 * multiplyer;
            killCount++;
            playExp = true;
            if(killCount >= mpUpgrade)
            {
              multiplyer++;
              if(mpUpgrade <= 75)
              {
                mpUpgrade = mpUpgrade + mpUpgrade;
              }
              else
              {
                mpUpgrade += 75;
              }
            }
          }
          else if(snakeGuys[i].hit(bullets[x].getRect()))
          {
            bullets[x].die();
          }
      }
    }
  }
}

void Classic::checkMap()
{
  //here we check if the player is close to the edge of the screen.
  //if this happens move everything back -= the players velocity. eg player.getxVel() (or yVel) to pass it to objects
  //this creates the scrolling effect
  if(player.getRect().x < 240 && levelRect.x < 30)
  {
    levelRect.x -= player.getxVel();
    player.moveBackX();
    for(int i = 0; i < 50; i++)
    {
      bullets[i].moveBackX(player.getxVel());
    }
    for(int i = 0; i < garyTotal; i++)
    {
      garys[i].moveBackX(player.getxVel());
    }
    for(int i = 0; i < karenTotal; i++)
    {
      karens[i].moveBackX(player.getxVel());
    }
    for(int i = 0; i < jeffTotal; i++)
    {
      jeffs[i].moveBackX(player.getxVel());
    }
    for(int i = 0; i < miniJeffTotal; i++)
    {
      miniJeffs[i].moveBackX(player.getxVel());
    }
    for(int i = 0; i < snakeTotal; i++)
    {
      snakeGuys[i].moveBackX(player.getxVel());
    }
    for(int i = 0; i < particleCount; i++)
    {
      bombParticles[i].moveBackX(player.getxVel());
    }
  }
  if(player.getRect().x > 720 - player.getRect().w && levelRect.x + levelRect.w > 930)
  {
    levelRect.x -= player.getxVel();
    player.moveBackX();
    for(int i = 0; i < 50; i++)
    {
      bullets[i].moveBackX(player.getxVel());
    }
    for(int i = 0; i < garyTotal; i++)
    {
      garys[i].moveBackX(player.getxVel());
    }
    for(int i = 0; i < karenTotal; i++)
    {
      karens[i].moveBackX(player.getxVel());
    }
    for(int i = 0; i < jeffTotal; i++)
    {
      jeffs[i].moveBackX(player.getxVel());
    }
    for(int i = 0; i < miniJeffTotal; i++)
    {
      miniJeffs[i].moveBackX(player.getxVel());
    }
    for(int i = 0; i < snakeTotal; i++)
    {
      snakeGuys[i].moveBackX(player.getxVel());
    }
    for(int i = 0; i < particleCount; i++)
    {
      bombParticles[i].moveBackX(player.getxVel());
    }
  }
  if(player.getRect().y < 238.5 && levelRect.y < 80)
  {
    levelRect.y -= player.getyVel();
    player.moveBackY();
    for(int i = 0; i < 50; i++)
    {
      bullets[i].moveBackY(player.getyVel());
    }
    for(int i = 0; i < garyTotal; i++)
    {
      garys[i].moveBackY(player.getyVel());
    }
    for(int i = 0; i < karenTotal; i++)
    {
      karens[i].moveBackY(player.getyVel());
    }
    for(int i = 0; i < jeffTotal; i++)
    {
      jeffs[i].moveBackY(player.getyVel());
    }
    for(int i = 0; i < miniJeffTotal; i++)
    {
      miniJeffs[i].moveBackY(player.getyVel());
    }
    for(int i = 0; i < snakeTotal; i++)
    {
      snakeGuys[i].moveBackY(player.getyVel());
    }
    for(int i = 0; i < particleCount; i++)
    {
      bombParticles[i].moveBackY(player.getyVel());
    }
  }
  if(player.getRect().y > 308 - player.getRect().h && levelRect.y + levelRect.h > 524)
  {
    levelRect.y -= player.getyVel();
    player.moveBackY();
    for(int i = 0; i < 50; i++)
    {
      bullets[i].moveBackY(player.getyVel());
    }
    for(int i = 0; i < garyTotal; i++)
    {
      garys[i].moveBackY(player.getyVel());
    }
    for(int i = 0; i < karenTotal; i++)
    {
      karens[i].moveBackY(player.getyVel());
    }
    for(int i = 0; i < jeffTotal; i++)
    {
      jeffs[i].moveBackY(player.getyVel());
    }
    for(int i = 0; i < miniJeffTotal; i++)
    {
      miniJeffs[i].moveBackY(player.getyVel());
    }
    for(int i = 0; i < snakeTotal; i++)
    {
      snakeGuys[i].moveBackY(player.getyVel());
    }
    for(int i = 0; i < particleCount; i++)
    {
      bombParticles[i].moveBackY(player.getyVel());
    }
  }
}

void Classic::drawHud(int batteryPercent, bool showBattery, bool showFps)
{
  //draw left hud background
  int fade = 150;
  for(int i = 0; i < 150; i++)
  {
    vita2d_draw_line(10 + i, 10, 9 + i, 80, RGBA8(menuBarColorR,menuBarColorG,menuBarColorB, fade));
    if(fade > 0)
    {
      fade--;
    }
  }
  //draw right hud background
  if(showBattery || showFps)
  {
    fade = 150;
    for(int i = 0; i < 150; i++)
    {
      vita2d_draw_line(955 - i, 10, 955 - i, 80, RGBA8(menuBarColorR,menuBarColorG,menuBarColorB, fade));
      if(fade > 0)
      {
        fade--;
      }
    }
  }

  //battery stuff
  int r,g,b;

  vitaRect battery;
  battery.x = 856;
  battery.y = 50;
  battery.w = 52;
  battery.h = 15;

  vitaRect batteryTip;
  batteryTip.x = battery.x + battery.w;
  batteryTip.y = battery.y + battery.h / 4;
  batteryTip.w = 3;
  batteryTip.h = battery.h / 2;

  //battery stuff
   if(batteryPercent > 50)
   {
     r = 0;
     g = 255;
     b = 0;
   }
   else if(batteryPercent > 25 && batteryPercent <= 50)
   {
     r = 244;
     g = 244;
     b = 0;
   }

   else if(batteryPercent <= 25)
   {
     r = 255;
     g = 0;
     b = 0;
   }
   if(showBattery)
   {
     for(int i = 0; i < batteryPercent / 2; i++)
     {
       vita2d_draw_line(battery.x + i + 1, battery.y, battery.x + i + 1, battery.y + battery.h, RGBA8(r,g,b,255));
     }
     //vita2d_font_draw_textf(font, battery.x + battery.w / 2 - 20, battery.y + battery.h / 2 + 10, RGBA8(0,0,255,255), 20.0f, "%d%%", batteryPercent);
     drawEmptyRect(battery, RGBA8(menuBorderR,menuBorderG,menuBorderB, 255));
     vita2d_draw_rectangle(batteryTip.x, batteryTip.y, batteryTip.w, batteryTip.h, RGBA8(menuBorderR,menuBorderG,menuBorderB, 255));
   }
   //end battery stuff

   //draw points and multiplyer
   vita2d_font_draw_textf(font, 15, 30, RGBA8(mainTextR,mainTextG,mainTextB,255), 20.0f, "P:%d", points);
   vita2d_font_draw_textf(font, 15, 50, RGBA8(mainTextR,mainTextG,mainTextB,255), 20.0f, "M:%d", multiplyer);

   //draw Extra lives and bombs count

   vita2d_font_draw_textf(font, 15, 70, RGBA8(mainTextR,mainTextG,mainTextB,255), 20.0f, "L:%d", extraLives);
   vita2d_font_draw_textf(font, 45, 70, RGBA8(mainTextR,mainTextG,mainTextB,255), 20.0f, "B:%d", bombCount);
}

void Classic::drawCursor(double rx, double ry, bool showCursor, int cursorSetting)
  {
    //cursor
    int tempCursorX = 125 - rx;
    int tempCursorY = 130 - ry;

    double angle = atan2(-tempCursorY, -tempCursorX);
  
    // Distance = sqrt[ (b-y)^2 + (a-x)^2 ]
  
    double xpos = player.getRect().x + (player.getRect().w / 2) - (-100.0 * cos(angle));
    double ypos = player.getRect().y + (player.getRect().h / 2) - (-100.0 * sin(angle));

    float rad = atan2(-tempCursorY, -tempCursorX);

    if(showCursor)
    {
      switch (cursorSetting) {
        case 1:
          vita2d_draw_texture_rotate(cursorCrosshair, xpos, ypos, 0);
          break;
        case 2:
          vita2d_draw_texture_rotate(cursorDuck, xpos, ypos, 0);
          break;
        case 3:
          vita2d_draw_texture_rotate(cursorWatcher, xpos, ypos, rad + 1.5708);
          break;
        case 4:
          vita2d_draw_texture_rotate(cursor1, xpos, ypos, 0);
          break;
        case 5:
          vita2d_draw_texture_rotate(cursor2, xpos, ypos, rad + 1.5708);
          break;
      }
    }
  }

bool Classic::playGun()
{
  return playGunSound;
}

bool Classic::getPlayExp()
{
  return playExp;
}

void Classic::pauseMenu()
{
  vita2d_draw_rectangle(240, 136, 480, 272, RGBA8(menuBGColorR,menuBGColorG,menuBGColorB, 100));
  drawEmptyRect(240, 136, 480, 272, RGBA8(menuBorderR,menuBorderG,menuBorderB, 100));

  vita2d_font_draw_text(font, 960 / 2 - vita2d_font_text_width(font, 20.0f, "PAUSED") / 2, 544 / 2, RGBA8(mainTextR,mainTextG,mainTextB,255), 20.0f, "PAUSED");

  vita2d_font_draw_text(font, 960 / 2 - vita2d_font_text_width(font, 20.0f, "Current Score:") / 2, 544 / 2 + 20, RGBA8(mainTextR,mainTextG,mainTextB,255), 20.0f, "Current Score:");

  vita2d_font_draw_textf(font, 960 / 2 - vita2d_font_text_width(font, 20.0f, std::to_string(points).c_str()) / 2, 544 / 2 + 40, RGBA8(mainTextR,mainTextG,mainTextB,255), 20.0f, "%d", points);

  int tempWidth = vita2d_texture_get_width(circleImage); //get the width and height to draw in correct place.
  int tempHeight = vita2d_texture_get_height(circleImage); //both images are the same size. //used for text too

  //uh.. x = half the screen - 1/4 of the screen = edge of pause menu. draw image here. draw text to right of image.
  //y = half the screen plus 1/4 of screen = bottom edge of pause menu. draw image here. draw text here - image width - text tempWidth
  vita2d_font_draw_text(font, 960 / 2 - 960 / 4 + tempWidth + 10, 544 / 2 + 544 / 4 - 10, RGBA8(helpTextR,helpTextG,helpTextB,255), 20.0f, "Continue");
  vita2d_font_draw_text(font, 960 / 2 + 960 / 4 - vita2d_font_text_width(font, 20.0f, "Main Menu") - tempWidth - 10, 544 / 2 + 544 / 4 - 10, RGBA8(helpTextR,helpTextG,helpTextB,255), 20.0f, "Main Menu");

  vita2d_draw_texture_scale(circleImage, 960 / 2 - 960 / 4 + 10, 544 / 2 + 544 / 4 - tempHeight, 1, 1);
  vita2d_draw_texture_scale(triangleImage, 960 / 2 + 960 / 4 - tempWidth - 10, 544 / 2 + 544 / 4 - tempHeight, 1, 1);

}

int Classic::getPoints()
{
  return points;
}

bool Classic::checkPlayer()
{ 
  if(god) return false;
  
  for(int i = 0; i < garyTotal; i++)
  {
    if(checkCollision(player.getRect(), garys[i].getRect()) && garys[i].getActive() && player.getActive())
    {
      return true;
    }
  }

  for(int i = 0; i < karenTotal; i++)
  {
    if(checkCollision(player.getRect(), karens[i].getRect()) && karens[i].getActive() && player.getActive())
    {
      return true;
    }
  }

  for(int i = 0; i < jeffTotal; i++)
  {
    if(checkCollision(player.getRect(), jeffs[i].getRect()) && jeffs[i].getActive() && player.getActive())
    {
      return true;
    }
  }

  for(int i = 0; i < miniJeffTotal; i++)
  {
    if(checkCollision(player.getRect(), miniJeffs[i].getRect()) && miniJeffs[i].getActive() && player.getActive() && miniJeffs[i].getSafeTime() > 30)
    {
      return true;
    }
  }

  for(int i = 0; i < snakeTotal; i++)
  {
    if(checkCollision(player.getRect(), snakeGuys[i].getRect1()) && snakeGuys[i].getActive())
    {
      return true;
    }
  }

  return false;
}

void Classic::killPlayer()
{
  player.die();
  safeTime = 0;

  multiplyer = 1;
  mpUpgrade = 5;
  killCount = 0;

  for(int i = 0; i < 50; i++)
  {
    bullets[i].die();
  }

  for(int i = 0; i < garyTotal; i++)
  {
    garysAlive = 0;
    if(garys[i].getActive() || garys[i].getSpawning())
    {
      garys[i].die();
    }
  }

  for(int i = 0; i < karenTotal; i++)
  {
    if(karens[i].getActive() || karens[i].getSpawning())
    {
      karens[i].die();
    }
  }

  for(int i = 0; i < jeffTotal; i++)
  {
    jeffsAlive = 0;
    if(jeffs[i].getActive() || jeffs[i].getSpawning())
    {
      jeffs[i].die();
    }
  }

  for(int i = 0; i < miniJeffTotal; i++)
  {
    if(miniJeffs[i].getActive())
    {
      miniJeffs[i].die();
    }
  }

  for(int i = 0; i < snakeTotal; i++)
  {
    if(snakeGuys[i].getActive())
    {
      snakeGuys[i].die();
    }
  }
}

void Classic::spawnStuff()
{
  if(safeTime < 120)
  {
    safeTime++;
  }

  if(safeTime >= 50 && !player.getActive() && extraLives > 0)
  {
    killPlayer();
    player.spawn();
    extraLives -= 1;

    levelRect.x = -240;
    levelRect.y = -139;
  }

  if(safeTime >= 120)
  {
    if(garysAlive < garyTotal / 2) 
    {
      std::vector<Gary> tempVector;
      for(int i = 0; i < garyTotal; i++)
      {
        if(garys[i].getActive()) tempVector.push_back(garys[i]);
      }
      garys = tempVector;
      garyTotal = garysAlive;
    }
    
    spawnTime++;
    int spawnTimeEnd;
    if(garyEvent || jeffEvent) spawnTimeEnd = 240;
    else spawnTimeEnd = 120;
    if(spawnTime >= spawnTimeEnd)
    {
      int karenCounter = 0;
      int garyCounter = 0;
      int jeffCounter = 0;
      int snakeCounter = 0;

      if(points <= 100)
      {
        karenCounter = rand() % 11;
        garyCounter = 0;
        jeffCounter = 0;
        snakeCounter = 0;
      }
      if(points >= 100 && points < 1000)
      {
        karenCounter = rand() % 11;
        garyCounter = rand() % 6;
        jeffCounter = 0;
        snakeCounter = 0;
      }
      if(points >= 1000 && points < 2500)
      {
        karenCounter = rand() % 11;
        garyCounter = rand() % 9;
        jeffCounter = 0;
        snakeCounter = 0;
      }
      if(points >= 2500 && points < 5000)
      {
        karenCounter = rand() % 11;
        garyCounter = rand() % 13;
        jeffCounter = rand() % 3;
        snakeCounter = 0;
      }
      if(points >= 5000 && points < 10000)
      {
        karenCounter = rand() % 11;
        garyCounter = rand() % 15;
        jeffCounter = rand() % 5;
        snakeCounter = rand() % 2;
      }
      if(points >= 10000 && points < 20000)
      {
        karenCounter = rand() % 11;
        garyCounter = rand() % 17;
        jeffCounter = rand() % 7;
        snakeCounter = rand() % 3;
      }
      if(points >= 20000 && points < 30000)
      {
        karenCounter = rand() % 11;
        garyCounter = rand() % 19;
        jeffCounter = rand() % 9;
        snakeCounter = rand() % 5;
      }
      if(points >= 30000 && points < 40000)
      {
        karenCounter = rand() % 11;
        garyCounter = rand() % 21;
        jeffCounter = rand() % 11;
        snakeCounter = rand() % 7;
      }
      if(points >= 40000 && points < 50000)
      {
        karenCounter = rand() % 11;
        garyCounter = rand() % 21;
        jeffCounter = rand() % 11;
        snakeCounter = rand() % 9;
      }
      if(points >= 50000)
      {
        karenCounter = rand() % 11;
        garyCounter = rand() % 31;
        jeffCounter = rand() % 11;
        snakeCounter = rand() % 11;
      }

      if(garyEvent || jeffEvent)
      {
        karenCounter = 1;
        garyCounter = 1;
        jeffCounter = 1;
        snakeCounter = 1;
      }


      for(int i = 0; i < karenTotal; i++)
      {
        if(!karens[i].getActive() && karenCounter > 0)
        {
          spawnKaren(i);
          karenCounter--;
        }
      }

      if(!garyEvent)
      {
        for(int i = 0; i < garyTotal; i++)
        {
          if(!garys[i].getActive() && garyCounter > 0)
          {
            spawnGary(i);
            garysAlive += 1;
            garyCounter--;
          }
        }
      }
      if(garyEvent && garysAlive == 0)
      {
        garyTotal = 40;
        garys.resize(garyTotal);
        eventTimer = 0;
        garyEvent = false;
        int spawnX = player.getRect().x - 175;
        int spawnY = player.getRect().y - 175;

        if(spawnX <= levelRect.x) spawnX = levelRect.x + 10;
        if(spawnX >= levelRect.x + levelRect.w) spawnX = levelRect.x + levelRect.w - 397;
        if(spawnY <= levelRect.y) spawnY = levelRect.y + 10;
        if(spawnY >= levelRect.y + levelRect.h) spawnY = levelRect.y + levelRect.h - 397;
        
        for(int i = 0; i < 10; i++)
        {
          spawnGary(i, spawnX, spawnY);
          garysAlive += 1;
          spawnX += 35;
        }
        for(int i = 10; i < 20; i++)
        {
          spawnGary(i, spawnX, spawnY);
          garysAlive += 1;
          spawnY += 35;
        }
        for(int i = 20; i < 30; i++)
        {
          spawnGary(i, spawnX, spawnY);
          garysAlive += 1;
          spawnX -= 35;
        }
        for(int i = 30; i < 40; i++)
        {
          spawnGary(i, spawnX, spawnY);
          garysAlive += 1;
          spawnY -= 35;
        }
      }

      if(!jeffEvent)
      {
        for(int i = 0; i < jeffTotal; i++)
        {
          if(!jeffs[i].getActive() && jeffCounter > 0)
          {
            spawnJeff(i);
            jeffsAlive += 1;
            jeffCounter--;
          }
        }
      }

      if(jeffEvent)
      {
        for(int i = 0; i < jeffTotal; i++)
        {
          jeffs[i].die();
          jeffsAlive -= 1;
        }
        eventTimer = 0; 
        jeffEvent = 0;
        int x = player.getRect().x - 132;
        if(player.getRect().x > levelRect.x + levelRect.w - 234)
          x = levelRect.x + levelRect.w - 234;
        else if(player.getRect().x < levelRect.x + 234)
          x = levelRect.x + 2;
        
        int y = player.getRect().y - 88;
        if(player.getRect().y > levelRect.y + levelRect.h - 175)
          y = levelRect.y + levelRect.h - 175;
        else if(player.getRect().y < levelRect.y + 175)
          y = levelRect.y + 2;
        int tempy = y;
        for(int i = 0; i < 5; i++)
        {
          spawnJeff(i, x, y);
          jeffsAlive += 1;
          y += 35;
        }
        y = tempy;
        x += 232;
        for(int i = 5; i < 10; i++)
        {
          spawnJeff(i, x, y);
          jeffsAlive += 1;
          y += 35;
        }
      }

      for(int i = 0; i < snakeTotal; i++)
      {
        if(!snakeGuys[i].getActive() && snakeCounter > 0)
        {
          snakeGuys[i].spawn(levelRect);
          snakeCounter--;
        }
      }

      spawnTime = 0;
    }
  }
}

void Classic::gameOver()
{
  drawEmptyRect(960 / 2 - 960 / 4, 544 / 2 - 544 / 4 , 960 / 2, 544 / 2, RGBA8(menuBorderR,menuBorderG,menuBorderB, 100));
  vita2d_draw_rectangle(960 / 2 - 960 / 4 + 1, 544 / 2 - 522 / 4 + 1, 960 / 2 - 1, 544 / 2 - 1, RGBA8(menuBGColorR,menuBGColorG,menuBGColorB, 100));

  vita2d_font_draw_text(font, 960 / 2 - vita2d_font_text_width(font, 20.0f, "Game Over") / 2, 544 / 2, RGBA8(mainTextR,mainTextG,mainTextB,255), 20.0f, "Game Over");

  vita2d_font_draw_text(font, 960 / 2 - vita2d_font_text_width(font, 20.0f, "Current Score:") / 2, 544 / 2 + 20, RGBA8(mainTextR,mainTextG,mainTextB,255), 20.0f, "Current Score:");
  vita2d_font_draw_textf(font, 960 / 2 - 50, 544 / 2 + 40, RGBA8(mainTextR,mainTextG,mainTextB,255), 20.0f, "%d", points);

  int tempWidth = vita2d_texture_get_width(triangleImage); //get the width and height to draw in correct place.
  int tempHeight = vita2d_texture_get_height(triangleImage); //both images are the same size. //used for text too

  //uh.. x = half the screen - 1/4 of the screen = edge of pause menu. draw image here. draw text to right of image.
  //y = half the screen plus 1/4 of screen = bottom edge of pause menu. draw image here. draw text here - image width - text tempWidth
  vita2d_font_draw_text(font, 960 / 2 - 960 / 4 + tempWidth + 10, 544 / 2 + 544 / 4 - 10, RGBA8(helpTextR,helpTextG,helpTextB,255), 20.0f, "Return to Menu");

  vita2d_draw_texture_scale(triangleImage, 960 / 2 - 960 / 4 + 10, 544 / 2 + 544 / 4 - tempHeight, 1, 1);
}

void Classic::checkBomb()
{
  for(int i = 0; i < particleCount; i++)
  {
    if(bombParticles[i].getActive())
    {
      for(int g = 0; g < garyTotal; g++)
      {
        if(garys[g].getActive())
        {
          if(checkCollision(garys[g].getRect(), bombParticles[i].getRect()))
          {
            garys[g].die();
            garysAlive -= 1;
          }
        }
      }
      for(int k = 0; k < karenTotal; k++)
      {
        if(karens[k].getActive())
        {
          if(checkCollision(karens[k].getRect(), bombParticles[i].getRect()))
          {
            karens[k].die();
          }
        }
      }
      for(int j = 0; j < jeffTotal; j++)
      {
        if(jeffs[j].getActive())
        {
          if(checkCollision(jeffs[j].getRect(), bombParticles[i].getRect()))
          {
            jeffs[j].die();
            jeffsAlive -= 1;
          }
        }
      }
      for(int m = 0; m < miniJeffTotal; m++)
      {
        if(miniJeffs[m].getActive())
        {
          if(checkCollision(miniJeffs[m].getRect(), bombParticles[i].getRect()))
          {
            miniJeffs[m].die();
          }
        }
      }
      for(int s = 0; s < snakeTotal; s++)
      {
        if(snakeGuys[s].getActive())
        {
          if(snakeGuys[s].hit(bombParticles[i].getRect()) )
          {
            snakeGuys[s].die();
          }
        }
      }
    }
  }
}

bool Classic::bombActive()
{
  for(int i = 0; i < particleCount; i++)
  {
    if(bombParticles[i].getActive())
    {
      return true;
    }
  }
  return false;
}
