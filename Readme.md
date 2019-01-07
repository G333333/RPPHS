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
- After installing the game you will have a folder called "images" within the games folder. 
- Within this folder is a themes.txt file. Edit this and add your theme's name to the bottom of the file. 
- Within this folder is also a folder called "theme" the default themes installed in the theme folder are called "default" and "grey". Copy the folder titled "default" to your computer. This is a theme and contains everything needed besides the text file that was edited earlier. 
- Rename the folder on your pc to the name that you added to the themes.txt file earlier. 
- Replace the images in this folder with images for your theme. New image files need to have the exact same name as the one they are replacing. New image files also need to have the same dimensions as the ones they are replacing. 
- Images should have a transparent backgrounds if they do not fill the entire image dimensions. 
- Next open the config.txt file located in your theme folder on your desktop.
- This file contains the colors for things like menu borders, text color, enemy particle/bakground color. 
- Here is the basic format of the config file for a theme
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
- Once you have replaced the images with custom images and modified the config.txt file place your theme folder back in the games folder in "images/theme/" with the "default" and "grey" themes

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
