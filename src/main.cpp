#include"game.h"
#include <psp2/kernel/sysmem.h> 


/*
 * Symbol of the image.png file
 */
//extern unsigned char _binary_image_png_start;

int main()
{
  //sceKernelGetFreeMemorySize(_USER_RW)
  vita2d_init_advanced((2 * 1024 * 1024));
  Game Game;
  Game.init();
  Game.loadFiles();
  Game.doGame();

  Game.quit();
	sceKernelExitProcess(0);
	return 0;
}
