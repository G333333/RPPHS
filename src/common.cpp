#include"common.h"

std::string buildDate;

int theme;
bool changeTheme;
int themeCount;
std::string themes[2];

void loadThemes()
{    
    std::ifstream themeFile;
    themeFile.open("app0:/images/themes.txt"); //fix me
    std::string temp;
    int i = 0;
    while(std::getline(themeFile, temp))
    {
        themes[i] = temp;
        i++;
        themeCount++;
    }
    themeFile.close();
}

void loadImages(std::string folder)
{
  vita2d_free_texture(garyImage);
  vita2d_free_texture(karenImage);
  vita2d_free_texture(jeffImage);
  vita2d_free_texture(snakeImage1);
  vita2d_free_texture(snakeImage2);
  vita2d_free_texture(playerImage);
  vita2d_free_texture(gameBackground);
  vita2d_free_texture(bulletImage);
  vita2d_free_texture(crossImage);
  vita2d_free_texture(circleImage);
  vita2d_free_texture(triangleImage);
  vita2d_free_texture(cursorCrosshair);
  vita2d_free_texture(cursorDuck);
  vita2d_free_texture(cursorWatcher);
  vita2d_free_texture(cursor1);
  vita2d_free_texture(cursor2);

  std::string srcBase = "app0:/images/theme/";
  std::string src;
  src = srcBase;
  src += folder;
  src += "/gary.png";
  garyImage = vita2d_load_PNG_file(src.c_str());

  src = srcBase;
  src += folder;
  src += "/karen.png";
  karenImage = vita2d_load_PNG_file(src.c_str());

  src = srcBase;
  src += folder;
  src += "/jeff.png";
  jeffImage = vita2d_load_PNG_file(src.c_str());

  src = srcBase;
  src += folder;
  src += "/Grid3.png";
  gameBackground = vita2d_load_PNG_file(src.c_str());

  src = srcBase;
  src += folder;
  src += "/player.png";
  playerImage = vita2d_load_PNG_file(src.c_str());

  src = srcBase;
  src += folder;
  src += "/bullet.png";
  bulletImage = vita2d_load_PNG_file(src.c_str());

  src = srcBase;
  src += folder;
  src += "/cross.png";
  crossImage = vita2d_load_PNG_file(src.c_str());

  src = srcBase;
  src += folder;
  src += "/circle.png";
  circleImage = vita2d_load_PNG_file(src.c_str());

  src = srcBase;
  src += folder;
  src += "/triangle.png";
  triangleImage = vita2d_load_PNG_file(src.c_str());

  src = srcBase;
  src += folder;
  src += "/cursor-crosshair.png";
  cursorCrosshair = vita2d_load_PNG_file(src.c_str());

  src = srcBase;
  src += folder;
  src += "/cursor-duck.png";
  cursorDuck = vita2d_load_PNG_file(src.c_str());

  src = srcBase;
  src += folder;
  src += "/cursor-watcher.png";
  cursorWatcher = vita2d_load_PNG_file(src.c_str());

  src = srcBase;
  src += folder;
  src += "/cursor1.png";
  cursor1 = vita2d_load_PNG_file(src.c_str());

  src = srcBase;
  src += folder;
  src += "/cursor2.png";
  cursor2 = vita2d_load_PNG_file(src.c_str());

  src = srcBase;
  src += folder;
  src += "/snakeImage1.png";
  snakeImage1 = vita2d_load_PNG_file(src.c_str());

  src = srcBase;
  src += folder;
  src += "/snakeImage2.png";
  snakeImage2 = vita2d_load_PNG_file(src.c_str());

}

vita2d_texture *garyImage;
vita2d_texture *karenImage;
vita2d_texture *jeffImage;
vita2d_texture *snakeImage1;
vita2d_texture *snakeImage2;
vita2d_texture *gameBackground;
vita2d_texture *playerImage;
vita2d_texture *bulletImage;
vita2d_texture *crossImage;
vita2d_texture *circleImage;
vita2d_texture *triangleImage;
vita2d_texture *cursorCrosshair;
vita2d_texture *cursorDuck;
vita2d_texture *cursorWatcher;
vita2d_texture *cursor1;
vita2d_texture *cursor2;