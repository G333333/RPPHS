#include"fpsCounter.h"

void FpsCounter::init()
{
  tick = 0;
  frames = 0;
  fps = 0;
}

void FpsCounter::update()
{
  uint64_t t_tick = sceKernelGetProcessTimeWide();

  if (tick == 0)
  {
		tick = t_tick;
	}
  else
  {
		if ((t_tick - tick) > 1000000)
    {
			fps = frames;
			frames = 0;
			tick = t_tick;
		}
  }
  frames++;
}

int FpsCounter::getFps()
{
  return fps;
}
