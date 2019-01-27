#include"game.h"
#include <psp2/kernel/sysmem.h> 

int main()
{
  vita2d_init_advanced((2 * 1024 * 1024));
  Game Game;
  Game.init();
  Game.loadFiles();
  Game.doGame();

  Game.quit();
	sceKernelExitProcess(0);
	return 0;
}
