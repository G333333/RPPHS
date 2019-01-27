#include"player.h"

void Player::init()
{
  xVel = 0;
  yVel = 0;

  rect.x = 380;
  rect.y = 225;
  rect.w = 24;
  rect.h = 24;

  rad = 0.0;

  active = false;
}

void Player::doStuff(double lx, double ly, int deadZone, vitaRect levelRect, bool pause)
{
  if(active)
  {
    double pi = 3.14159;
    double tx, ty;
    tx = 125 - lx;
    ty = 130 - ly;
    if(tx < deadZone && tx > -deadZone)
    {
      tx = 0;
    }
    if(ty < deadZone && ty > -deadZone)
    {
      ty = 0;
    }
    double angle = atan2(-ty, -tx) * 180 / pi;//angle for movement.
    xVel = 4*(cos(angle*pi/180));   // move x
    yVel = 4*(sin(angle*pi/180));   // move y
    if(tx < -10 || tx > 10 || ty < -10 || ty > 10)
    {
      if(!pause)
      {
        rad = atan2(-ty, -tx);
      }//radians for image rotation.
    }
    if(tx == 0)
    {
      xVel = 0;
    }
    if(!pause)
    {
      rect.x += xVel;
    }
    if(rect.x <= levelRect.x)
    {
      rect.x = levelRect.x;
    }
    if(rect.x >= levelRect.x + levelRect.w - rect.w)
    {
      rect.x = levelRect.x + levelRect.w - rect.w;
    }
    if(!pause)
    {
      rect.y += yVel;
    }
    if(rect.y <= levelRect.y)
    {
      rect.y = levelRect.y;
    }
    if(rect.y >= levelRect.y + levelRect.h - rect.h)
    {
      rect.y = levelRect.y + levelRect.h - rect.h;
    }

    vita2d_draw_texture_rotate(playerImage, rect.x + 12, rect.y + 12, rad);
    //drawEmptyRect(rect, RGBA8(0,255,0,255));
  }
}

vitaRect Player::getRect()
{
  return rect;
}

bool Player::getActive()
{
  return active;
}

void Player::setxVel(double xVel)
{
  this->xVel = xVel;
}

void Player::setyVel(double yVel)
{
  this->yVel = yVel;
}

double Player::getxVel()
{
  return xVel;
}

double Player::getyVel()
{
  return yVel;
}

void Player::moveBackX()
{
  rect.x -= xVel;
}

void Player::moveBackY()
{
  rect.y -= yVel;
}

void Player::die()
{
  active = false;
}

void Player::spawn()
{
  active = true;
  rect.x = 960 / 2 - rect.w / 2;
  rect.y = 544 / 2 - rect.w / 2;
}
