#include"game.h"

/*
 * Symbol of the image.png file
 */
extern unsigned char _binary_image_png_start;

int main()
{
  vita2d_init();
  Game Game;
  Game.init();
  Game.loadFiles();
  Game.doGame();

  Game.quit();
	sceKernelExitProcess(0);
	return 0;
}
