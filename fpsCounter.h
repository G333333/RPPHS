#ifndef _Fps_Class_
#define _Fps_Class_

#include <psp2/kernel/processmgr.h>

class FpsCounter {
private:
  uint64_t tick;
  int frames;
  int fps;
public:
  void init();
  void update();
  int getFps();
};

#endif
