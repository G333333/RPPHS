#include"common.h"

std::string buildDate;

int theme;
bool changeTheme;
int themeCount;
std::string themes[2];

void loadThemes(){
    const char* PATH = "app0:/images/theme";

    SceUID dir = sceIoDopen(PATH);
    SceIoDirent *subDir;

    int i = 0;
    int entry = sceIoDread (dir, subDir);
    while (entry > 0)
    {
        themes[i] = subDir->d_name;
        i++;
        themeCount++;
        entry = sceIoDread (dir, subDir);
    }

    sceIoDclose(dir);

    std::ifstream themeFile;
    themeFile.open("app0:/images/themes.txt"); //fix me
    std::string temp;
    i = 0;
    while(std::getline(themeFile, temp))
    {
        themes[i] = temp;
        i++;
        themeCount++;
    }
    themeFile.close();
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