#include"common.h"

std::string buildDate;
std::string downLoadCount;

bool quitGame;

int theme;
bool changeTheme;
int themeCount;
//std::string themes[2];
std::vector<std::string> themes(2);
void loadThemes()
{    
    std::ifstream themeFile;
    themeFile.open("ux0:/data/RPPHS/themes.txt");
    std::string temp;
    std::getline(themeFile, temp);
    themeFile.close();
    if(temp.empty())
    {
        std::ofstream tempFile;
        sceIoMkdir("ux0:/data/RPPHS", 0777);
        tempFile.open("ux0:/data/RPPHS/themes.txt");
        tempFile << "default\n";
        tempFile << "grey\n";
        tempFile << "madBlock\n";
        tempFile.close();
    }
    themeFile.open("ux0:/data/RPPHS/themes.txt");
    int i = 0;
    int size = 2;
    while(std::getline(themeFile, temp))
    {
            if(i > size -1)
            {
                themes.resize(size + 1);
                size++;
            }
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
  vita2d_free_texture(lTriggerImage);
  vita2d_free_texture(rTriggerImage);
  vita2d_free_texture(triangleImage);
  vita2d_free_texture(cursorCrosshair);
  vita2d_free_texture(cursorDuck);
  vita2d_free_texture(cursorWatcher);
  vita2d_free_texture(cursor1);
  vita2d_free_texture(cursor2);

  std::string srcBase;

  if(folder == "default" || folder == "grey" || folder == "madBlock")
  {
    srcBase = "app0:/images/theme/";
  }
  else
  {
    srcBase = "ux0:/data/RPPHS/theme/";
  }
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
  src += "/l1.png";
  lTriggerImage = vita2d_load_PNG_file(src.c_str());

  src = srcBase;
  src += folder;
  src += "/r1.png";
  rTriggerImage = vita2d_load_PNG_file(src.c_str());

  src = srcBase;
  src += folder;
  src += "/lStick.png";
  lStick = vita2d_load_PNG_file(src.c_str());

  src = srcBase;
  src += folder;
  src += "/rStick.png";
  rStick = vita2d_load_PNG_file(src.c_str());

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

  src = srcBase;
  src += folder;
  src += "/saveImage.png";
  saveImage = vita2d_load_PNG_file(src.c_str());
  loadThemeConfig(folder);
}

int mainTextR, mainTextG, mainTextB;
int helpTextR, helpTextG, helpTextB;
int menuBorderR, menuBorderG, menuBorderB;
int menuBGColorR, menuBGColorG, menuBGColorB;
int menuBarColorR, menuBarColorG, menuBarColorB;
int garyColorR, garyColorG, garyColorB;
int jeffColorR, jeffColorG, jeffColorB;
int miniColorR, miniColorG, miniColorB;
int karenColorR, karenColorG, karenColorB;
int snakeColorR, snakeColorG, snakeColorB;
int bulletPColorR, bulletPColorG, bulletPColorB;

void loadThemeConfig(std::string folder)
{
    //read the first line and assign to first variable, 
    //get line, throw away, 
    //get line, letter then number, assign number to variables r position variable = rgb
    //repeat previous step for g and b
    //get line throw, throw away. 

    //repeat for all variables

    /**
     * needed variables. all in rgb format. 
     * main text color
     * help text color
     * menu borders
     * gary colors
     * jeff colors
     * minijeff colors
     * karen colors
     * snake colors
     * 
     * 
     * */ 

    std::ifstream configFile;
    
    std::string src;

    if(folder == "default" || folder == "grey" || folder == "madBlock")
    {
      src = "app0:/images/theme/";
    }
    else
    {
      src = "ux0:/data/RPPHS/theme/";
    }
    
    src += folder;
    src += "/config.txt";

    configFile.open(src.c_str()); //fix me
    std::string::size_type sz;   // alias of size_t
    std::string var;
    std::string garbage;
    std::string line;
    int valueR = 0;
    int valueG = 0;
    int valueB = 0;
    
    while(std::getline(configFile, var))//first line = variable
    {
        std::getline(configFile, garbage);//second line = {}
        std::getline(configFile, line);

        line = line.substr(line.find(":") + 1, 3); //find substring after
        valueR = std::stoi(line.c_str(), &sz);
        std::getline(configFile, line);

        line = line.substr(line.find(":") + 1, 3); //find substring after
        valueG = std::stoi(line.c_str(), &sz);
        std::getline(configFile, line);

        line = line.substr(line.find(":") + 1, 3); //find substring after
        valueB = std::stoi(line.c_str(), &sz);

        if(var == "mainTextColor"){ 
                mainTextR = valueR;
                mainTextG = valueG;
                mainTextB = valueB;
        }
        else if(var == "helpTextColor"){ 
                helpTextR = valueR;
                helpTextG = valueG;
                helpTextB = valueB;
        }
        else if(var == "menuBorderColor"){ 
                menuBorderR = valueR;
                menuBorderG = valueG;
                menuBorderB = valueB;
        }
        else if(var == "menuBGColor"){
                menuBGColorR = valueR;
                menuBGColorG = valueG;
                menuBGColorB = valueB;
        }
        else if(var == "menuBarColor")
        {
                menuBarColorR = valueR;
                menuBarColorG = valueG;
                menuBarColorB = valueB;
        }
        else if(var == "garyColor"){ 
                garyColorR = valueR;
                garyColorG = valueG;
                garyColorB = valueB;
        }
        else if(var == "jeffColor"){ 
                jeffColorR = valueR;
                jeffColorG = valueG;
                jeffColorB = valueB;
        }
        else if(var == "miniColor"){ 
                miniColorR = valueR;
                miniColorG = valueG;
                miniColorB = valueB;
        }
        else if(var == "karenColor"){ 
                karenColorR = valueR;
                karenColorG = valueG;
                karenColorB = valueB;
        }
        else if(var == "snakeColor"){ 
                snakeColorR = valueR;
                snakeColorG = valueG;
                snakeColorB = valueB;
        }
        else if(var == "bulletPColor")
        {
                bulletPColorR = valueR;
                bulletPColorG = valueG;
                bulletPColorB = valueB;
        }

        std::getline(configFile, garbage);        
    }
    configFile.close();
    vita2d_set_clear_color(RGBA8(menuBGColorR,menuBGColorG,menuBGColorB,255));
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
vita2d_texture *lTriggerImage;
vita2d_texture *rTriggerImage;
vita2d_texture *lStick;
vita2d_texture *rStick;
vita2d_texture *triangleImage;
vita2d_texture *cursorCrosshair;
vita2d_texture *cursorDuck;
vita2d_texture *cursorWatcher;
vita2d_texture *cursor1;
vita2d_texture *cursor2;
vita2d_texture *saveImage;
vita2d_texture *charge;

vita2d_font *font;