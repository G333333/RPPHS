## About
Blast your way through those shapes in this Geometry Wars-inspired twin stick shooter for the PlayStation Vita! Enter your initials for the offline leaderboards, customize your crosshair, and mess with our super-cool settings menu.. or don't, that's entirely up to you. 

## Controls
  #### Movement: Left stick. 
  #### Aiming: Right Stick.
  #### Bombs: Left or Right trigger.
  #### Pause: Start.
  
## Install
<a href="https://github.com/G333333/RPPHS/releases/download/v1.0/RPPHS.vpk">Get the latest version here</a> and install using vitashell. If you would like to test the latest latest changes see the build instructions below. 

## Build instructions (Linux)
- Clone or download the project
- run the following from a terminal `cd build && cmake ../ && ./make.sh`
- .vpk is output to the build folder
- install with vitashell 

## Creating custom themes
- Download the default theme zip file from [images/theme/default.zip](https://github.com/G333333/RPPHS/raw/master/images/theme/default.zip) and unzip it to your pc somewhere. 
- The folder you have downloaded and unzipped is the default theme and contains almost everything needed to create custom themes
- Rename the folder to the name of your theme
- Replace the images with images for your theme. (Images need to have the same names and dimensions as the ones being replaced)
- Edit the config.txt file within your themes folder. 
- The data in this file represents the colors for things in game. The format is:
```
mainTextColor
{
  Red:255
  Green:0
  blue:0
}
```
- the first line is the variable name and the lines inside the quoutes are the values that will be assigned to that variables color values. 
- Your themes config.txt file needs to follow this format and copying the original version and only modifing the color values is strongly suggested.
- Copy your theme folder to `ux0:/data/RPPHS/theme/`
- Finally Edit the file located at `ux0:/data/RPPHS/themes.txt` and add the name of your theme to the bottom of the file.

## Credits
- G33 Programming, Design
- MotoLegacy: Live Area, Player/Enemies, Programming, Design

#### Special Thanks
- Xerpi libVita2s
- Xyz SoLoud Vita Port
- Rinnegatamante: Fps Counter code
- VitaSDK Contributors
- Ivan voiro @ OpenGameArt: Background Grid
- yd @ openGameArt: Menu Music
- Trevor Lentz @OpenGameArt: Game Music

## Screenshots

![Game Menu](screenshots/screen2.jpg?raw=true "Game Menu")

![In Game](screenshots/screen.jpg?raw=true "Game Play")

![High Scores](screenshots/screen1.jpg?raw=true "High Scores")

![Credits](screenshots/screen3.jpg?raw=true "Credits")
