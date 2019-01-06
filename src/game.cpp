#include"game.h"

void Game::init()
{
  theme = 0;
  changeTheme = false;

  themes[0] = "";
  themes[1] = "";
  themeCount = 0;

  levelWidth = 1449;
  levelHeight = 816;
  quitGame = false;
  status = 1;
	vita2d_set_clear_color(RGBA8(0,0,0,255));

	font = vita2d_load_font_file( "app0:/font/font.ttf" );

  memset(&pad, 0, sizeof(pad));

  menu.init();
  options.init();
  classic.init(levelWidth, levelHeight);
  highScores.init();
  fpsCounter.init();
  for(int i = 0; i < 15; i++)
  {
    keys[i] = false;
  }

  srand (time(NULL));

  showFps = true;
  showCursor = true;
  showBattery = true;
  cursorSetting = 1;
  deadZone = 12;

  playingGameSound = false;

  gSoloud.init(); // Initialize SoLoud

  saveScreen.init(0);

}

void Game::loadFiles()
{ 
  gWave.stop();
  exp1.stop();
  OutThere.stop();
  HeroImmortal.stop();

  vita2d_end_drawing();
  vita2d_wait_rendering_done();

  loadThemes();
  loadImages("default");

  gWave.load("app0:/sounds/blaster.wav"); // Load a wave
  exp1.load("app0:/sounds/exp1.wav");
  OutThere.load("app0:/sounds/OutThere.ogg");
  HeroImmortal.load("app0:/sounds/HeroImmortal.ogg");
  loadScores();
  loadSettings();
}

void Game::loadScores()
{
  std::string::size_type sz;   // alias of size_t
  std::ifstream loadFile;
  loadFile.open("ux0:/data/RPPHS/scores.txt");
  std::string temp;
  int index = 0;
  while(std::getline(loadFile, temp)) //get the a line and assign it to temp
  {
    if(index < 10)
    {
      scores_str[index] = temp.substr(0 , 3); //assign a str the temp value
      temp = temp.substr(temp.find(" ") + 1, 9); //assign temp the second value of the string
      scores_int[index] = std::stoi(temp.c_str(), &sz); //convert that too an int and assign it to a int var
      index++; //move the index to avoid array out of bounds.
    }
  }
  //here we check if the first score is empty eg: file was empty.
  //if so, set default scores
  if(scores_str[0].empty())
  {
    setDefaultScores();
    if(scores_str[0].empty()) //if still empty quit
    {
      quitGame = true;
    }
  }
  loadFile.close();
}

void Game::setDefaultScores()
{
  std::ofstream loadFile;
  sceIoMkdir("ux0:/data/RPPHS", 0777);
  loadFile.open("ux0:/data/RPPHS/scores.txt"); //fix me
  loadFile << "AAA 100000 \n";
  loadFile << "AAA 90000 \n";
  loadFile << "AAA 80000 \n";
  loadFile << "AAA 70000 \n";
  loadFile << "AAA 60000 \n";
  loadFile << "AAA 50000 \n";
  loadFile << "AAA 40000 \n";
  loadFile << "AAA 30000 \n";
  loadFile << "AAA 20000 \n";
  loadFile << "AAA 10000 \n";
  loadFile.close();

  //manually set the string values as to not open and read the file again.
  int tempScore = 100000;
  for(int i = 0; i < 10; i++)
  {
    scores_str[i] = "AAA";
    scores_int[i] = tempScore;
    tempScore -= 10000;
  }
}

void Game::saveScores(int newScore, std::string newStr)
{
  //check for new high score.
  for(int i = 0; i < 10; i++)
  {
    if(newScore > scores_int[i])
    {
      for(int x = 9; x > i; x--)
      {
        scores_int[x] = scores_int[x - 1];
        scores_str[x] = scores_str[x - 1];
      }
      scores_int[i] = newScore;
      scores_str[i] = newStr;
      break;
    }
  }
  //save the scores, after checking folder, and opening file.
  std::ofstream saveFile;
  sceIoMkdir("ux0:/data/RPPHS", 0777);
  saveFile.open("ux0:/data/RPPHS/scores.txt"); //fix me
  for(int i = 0; i < 10; i++)
  {
    saveFile << scores_str[i] << " " << scores_int[i] << "\n";
  }
  saveFile.close();//close
  loadScores(); //update the scores. cheap lazy way to update the string parts of the scores.
}

bool Game::checkScores(int newScore)
{
  for(int i = 0; i < 10; i++)
  {
    if(newScore > scores_int[i])
    {
      return true;
    }
  }
  return false;
}

void Game::loadSettings()
{
  std::string::size_type sz;   // alias of size_t
  std::ifstream loadFile;
  loadFile.open("ux0:/data/RPPHS/config.txt");
  std::string temp;
  int index = 0;
  int settings[7];
  std::getline(loadFile, temp);
  loadFile.close();
  if(temp.empty())
  {
    setSettings();
  }
  else
  {
    //sceClibPrintf("temp was Not empty");
    loadFile.open("ux0:/data/RPPHS/config.txt");
    while(std::getline(loadFile, temp)) //get the a line and assign it to temp
    {
      if(index < 7 && !temp.empty())
      {
         //convert that too an int and assign it to a int var
        settings[index] = std::stoi(temp.c_str(), &sz);
        index++; //move the index to avoid array out of bounds.
      }
    }

    showFps = settings[0];
    showCursor = settings[1];
    showBattery = settings[2];
    cursorSetting = settings[3];
    deadZone = settings[4];
    musicVol = settings[5];
    soundVol = settings[6];

    options.setAll(showFps, showCursor, showBattery, cursorSetting, deadZone, musicVol, soundVol);
    loadFile.close();

    std::ifstream loadFile;
    loadFile.open("app0:/buildDate.txt");
    std::getline(loadFile, buildDate);
    loadFile.close();

  }
}

void Game::setSettings() //set the default settings.
{

  showFps = 1;
  showCursor = 1;
  showBattery = 1;
  cursorSetting = 4;
  deadZone = 12;
  musicVol = 5;
  soundVol = 1;

  options.setAll(showFps, showCursor, showBattery, cursorSetting, deadZone, musicVol, soundVol);

  std::ofstream loadFile;
  sceIoMkdir("ux0:/data/RPPHS", 0777);
  loadFile.open("ux0:/data/RPPHS/config.txt");
  loadFile << "1 \n";
  loadFile << "1 \n";
  loadFile << "1 \n";
  loadFile << "4 \n";
  loadFile << "12 \n";
  loadFile << "5 \n";
  loadFile << "1 \n";
  loadFile.close();
}

void Game::saveSettings()
{
  std::ofstream loadFile;
  sceIoMkdir("ux0:/data/RPPHS", 0777);
  loadFile.open("ux0:/data/RPPHS/config.txt"); //fix me
  loadFile << showFps << "\n";
  loadFile << showCursor << "\n";
  loadFile << showBattery << "\n";
  loadFile << cursorSetting << "\n";
  loadFile << deadZone << "\n";
  double tempM = musicVol * 10;
  double tempS = soundVol * 10;
  loadFile << tempM << "\n";
  loadFile << tempS << "\n";
  loadFile.close();

  /**sceClibPrintf("%d\n", showFps);
  sceClibPrintf("%d\n", showCursor);
  sceClibPrintf("%d\n", showBattery);
  sceClibPrintf("%d\n", cursorSetting);
  sceClibPrintf("%d\n", deadZone);
  sceClibPrintf("%f\n", tempM);
  sceClibPrintf("%f\n", tempS);***/
}


void Game::doGame()
{
  intro.doIntro(font);

  OutThere.setLooping(1);
  gSoloud.play(OutThere);

  vita2d_set_vblank_wait(1);

  while (!quitGame) {
		sceCtrlPeekBufferPositive(0, &pad, 1);
    sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);

    /**quick reference:
      keys[0] = up;
      keys[1] = down;
      keys[2] = left;
      keys[3] = right;
      keys[4] = cross;
      keys[7] = square;
      keys[6] = triangle;
      keys[5] = circle;
      keys[8] = ly Up
      keys[9] = ly Down; **/
    if (pad.buttons & SCE_CTRL_UP)
    {
      keys[0] = true;
    }
    else
    {
      keys[0] = false;
    }
    if(pad.buttons & SCE_CTRL_DOWN)
    {
      keys[1] = true;
    }
    else
    {
      keys[1] = false;
    }
    if(pad.buttons & SCE_CTRL_LEFT)
    {
      keys[2] = true;
    }
    else
    {
      keys[2] = false;
    }
    if(pad.buttons & SCE_CTRL_RIGHT)
    {
      keys[3] = true;
    }
    else
    {
      keys[3] = false;
    }
    if(pad.buttons & SCE_CTRL_CROSS)
    {
      keys[4] = true;
    }
    else
    {
      keys[4] = false;
    }
    if(pad.buttons & SCE_CTRL_CIRCLE)
    {
      keys[5] = true;
    }
    else
    {
      keys[5] = false;
    }
    if(pad.buttons & SCE_CTRL_TRIANGLE)
    {
      keys[6] = true;
    }
    else
    {
      keys[6] = false;
    }
    if(pad.buttons & SCE_CTRL_SQUARE)
    {
      keys[7] = true;
    }
    else
    {
      keys[7] = false;
    }
    if(pad.ly > 177.5)
    {
      keys[8] = true;
    }
    else
    {
      keys[8] = false;
    }
    if(pad.ly < 77.5)
    {
      keys[9] = true;
    }
    else
    {
      keys[9] = false;
    }
    if(pad.buttons & SCE_CTRL_START)
    {
      keys[10] = true;
    }
    else
    {
      keys[10] = false;
    }
    if(pad.lx < 77.5)
    {
      keys[11] = true;
    }
    else
    {
      keys[11] = false;
    }
    if(pad.lx > 177.5)
    {
      keys[12] = true;
    }
    else
    {
      keys[12] = false;
    }
    if(pad.buttons & SCE_CTRL_LTRIGGER)
    {
      keys[13] = true;
    }
    else
    {
      keys[13] = false;
    }
    if(pad.buttons & SCE_CTRL_RTRIGGER)
    {
      keys[14] = true;
    }
    else
    {
      keys[14] = false;
    }

		vita2d_start_drawing();
		vita2d_clear_screen();

    switch (status) {
      case 1:
        menu.doStuff(font, keys, scePowerGetBatteryLifePercent(), showBattery);
        status = menu.getStatus();
        quitGame = menu.getQuit();
        classic.setStatus(status);
        options.setStatus(status);
        saveScreen.setStatus(status);
        highScores.setStatus(status);
        options.menuPartial(font);
        if(status == 2)
        {
          status = 5;
          highScores.start();
        }
        classic.setStatus(status);
        options.setStatus(status);
        saveScreen.setStatus(status);
        highScores.setStatus(status);
        if(status == 3)
        {
          options.start();
        }
        break;
      case 2:
        classic.doStuff(font,
        keys,
        pad.lx,
        pad.ly,
        pad.rx,
        pad.ry,
        scePowerGetBatteryLifePercent(),
        showFps,
        showCursor,
        showBattery,
        cursorSetting,
        deadZone);
        status = classic.getStatus();
        quitGame = classic.getQuit();
        menu.setStatus(status);
        options.setStatus(status);
        saveScreen.setStatus(status);
        if(classic.getPoints() > 10000 && !playingGameSound)
        {
          HeroImmortal.setLooping(1);
          gSoloud.play(HeroImmortal);
          playingGameSound = true;
        }
        if(status == 1)
        {
          OutThere.setLooping(1);
          gSoloud.play(OutThere);
          HeroImmortal.stop();

          if(checkScores(classic.getPoints()))
          {
            status = 4;
            menu.setStatus(status);
            options.setStatus(status);
            saveScreen.setStatus(status);
            saveScreen.start(classic.getPoints());
          }
          else
          {
            menu.start();
          }
        }
        break;
      case 3:
        options.doStuff(font, keys, scePowerGetBatteryLifePercent());
        status = options.getStatus();
        quitGame = options.getQuit();
        classic.setStatus(status);
        menu.setStatus(status);
        saveScreen.setStatus(status);
        menu.menuPartial(font);
        showFps = options.getShowFps();
        showCursor = options.getShowCursor();
        showBattery = options.getShowBattery();
        cursorSetting = options.getCursorSetting();
        deadZone = options.getDeadZone();
        musicVol = options.getMusicLevel();
        soundVol = options.getSoundsLevel();
        gWave.setVolume(options.getSoundsLevel());
        exp1.setVolume(options.getSoundsLevel());
        OutThere.setVolume(options.getMusicLevel());
        HeroImmortal.setVolume(options.getMusicLevel());
        saveIcon.start();
        if(status == 1)
        {
          menu.start();
          saveSettings();
        }
        break;
      case 4:
        saveScreen.doStuff(font, keys, scePowerGetBatteryLifePercent(), showBattery);
        status = saveScreen.getStatus();
        classic.setStatus(status);
        options.setStatus(status);
        menu.setStatus(status);
        highScores.setStatus(status);
        saveIcon.start();
        if(status == 5)
        {
          highScores.start();

          saveScores(saveScreen.getPoints(), saveScreen.getFinalInput());
        }
        break;
      case 5:
        highScores.doStuff(font, keys, scePowerGetBatteryLifePercent(), showBattery, scores_int, scores_str, classic.getPoints());
        status = highScores.getStatus();
        classic.setStatus(status);
        options.setStatus(status);
        saveScreen.setStatus(status);
        menu.setStatus(status);
        menu.menuPartial(font);
        options.menuPartial(font);


        if(status == 1)
        {
          menu.start();
          classic.init(levelWidth, levelHeight);// only needed here to set score to zero, after getting a new score and leaving this screen
        }

        if(status == 2)
        {
          classic.init(levelWidth, levelHeight);
          OutThere.stop();
          playingGameSound = false;
        }
        classic.setStatus(status);
        break;
    }

    if(saveIcon.getTimer() < 180)
    {
      saveIcon.doStuff(960 - 30, 544 - 30);
    }

    if(classic.playGun())
    {
      gWave.stop();
      gSoloud.play(gWave); // Play the wave
    }
    if(classic.getPlayExp())
    {
      exp1.stop();
      gSoloud.play(exp1);
    }

    fpsCounter.update();
    if(showFps)
    {
      vita2d_font_draw_textf(font, 856, 30, RGBA8(mainTextR,mainTextG,mainTextB,255), 20.0f, "FPS:%d", fpsCounter.getFps());
    }

    if(changeTheme)
    {
      //if(theme == 0) loadFiles(); //default theme
      loadImages(themes[theme].c_str());
      changeTheme = false;
    }

		vita2d_end_drawing();
		vita2d_swap_buffers();
    vita2d_wait_rendering_done();

	}
}

void Game::quit()
{
  vita2d_fini();
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
  vita2d_free_font(font);
  vita2d_free_texture(saveImage);

  saveIcon.cleanUp();

  gSoloud.deinit(); // Clean up!

}
