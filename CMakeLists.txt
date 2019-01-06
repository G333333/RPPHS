cmake_minimum_required(VERSION 2.8)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

OPTION(DEFINE_DEBUG
  "Build the project using debugging code"
  OFF)
IF(DEFINE_DEBUG)
  MESSAGE("Adding Debug flag...")
  ADD_DEFINITIONS(-DDEFINE_DEBUG)
  #SET(CMAKE_BUILD_TYPE Debug)
  MESSAGE("Build type is " ${CMAKE_BUILD_TYPE})
ENDIF(DEFINE_DEBUG)


set(SHORT_NAME RPPHS)
project(${SHORT_NAME})
include("${VITASDK}/share/vita.cmake" REQUIRED)

set(VITA_APP_NAME "RPPHS")
set(VITA_TITLEID  "VGEE00001")
set(VITA_VERSION  "02.50")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -std=gnu14 -Wall ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++14 -Wall ")


include_directories(
  ../common
)

add_executable(${SHORT_NAME}.elf
src/main.cpp
src/common.cpp
src/intro.cpp
src/game.cpp
src/functions.cpp
src/menu.cpp
src/options.cpp
src/classic.cpp
src/player.cpp
src/bullet.cpp
src/gary.cpp
src/karen.cpp
src/particle.cpp
src/fpsCounter.cpp
src/jeff.cpp
src/miniJeff.cpp
src/snakeGuy.cpp
src/saveScreen.cpp
src/saveIcon.cpp
src/highScores.cpp
)

target_link_libraries(${SHORT_NAME}.elf


  debugnet
  vita2d
  soloud
  pthread
  ScePgf_stub
  ScePvf_stub
  SceGxm_stub
  SceCtrl_stub
  SceTouch_stub
  SceAppUtil_stub
  SceDisplay_stub
  SceLibKernel_stub
  SceSysmodule_stub
  ScePower_stub
  SceCommonDialog_stub
  SceRegistryMgr_stub
  SceHid_stub
  freetype
  png
  jpeg
  z
  m
  SceAudio_stub
)


vita_create_self(${SHORT_NAME}.self ${SHORT_NAME}.elf)

vita_create_vpk(${SHORT_NAME}.vpk ${VITA_TITLEID} ${SHORT_NAME}.self
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}
  FILE images/theme/default/gary.png images/theme/default/gary.png
  FILE images/theme/default/karen.png images/theme/default/karen.png
  FILE images/theme/default/jeff.png images/theme/default/jeff.png
  FILE images/theme/default/player.png images/theme/default/player.png
  FILE images/theme/default/Grid3.png images/theme/default/Grid3.png
  FILE images/theme/default/bullet.png images/theme/default/bullet.png
  FILE images/theme/default/cross.png images/theme/default/cross.png
  FILE images/theme/default/circle.png images/theme/default/circle.png
  FILE images/theme/default/triangle.png images/theme/default/triangle.png
  FILE images/theme/default/cursor-crosshair.png images/theme/default/cursor-crosshair.png
  FILE images/theme/default/cursor-duck.png images/theme/default/cursor-duck.png
  FILE images/theme/default/cursor-watcher.png images/theme/default/cursor-watcher.png
  FILE images/theme/default/cursor1.png images/theme/default/cursor1.png
  FILE images/theme/default/cursor2.png images/theme/default/cursor2.png
  FILE images/theme/default/saveImage.png images/theme/default/saveImage.png
  FILE images/theme/default/snakeImage1.png images/theme/default/snakeImage1.png
  FILE images/theme/default/snakeImage2.png images/theme/default/snakeImage2.png

  FILE images/theme/grey/gary.png images/theme/grey/gary.png
  FILE images/theme/grey/karen.png images/theme/grey/karen.png
  FILE images/theme/grey/jeff.png images/theme/grey/jeff.png
  FILE images/theme/grey/player.png images/theme/grey/player.png
  FILE images/theme/grey/Grid3.png images/theme/grey/Grid3.png
  FILE images/theme/grey/bullet.png images/theme/grey/bullet.png
  FILE images/theme/grey/cross.png images/theme/grey/cross.png
  FILE images/theme/grey/circle.png images/theme/grey/circle.png
  FILE images/theme/grey/triangle.png images/theme/grey/triangle.png
  FILE images/theme/grey/cursor-crosshair.png images/theme/grey/cursor-crosshair.png
  FILE images/theme/grey/cursor-duck.png images/theme/grey/cursor-duck.png
  FILE images/theme/grey/cursor-watcher.png images/theme/grey/cursor-watcher.png
  FILE images/theme/grey/cursor1.png images/theme/grey/cursor1.png
  FILE images/theme/grey/cursor2.png images/theme/grey/cursor2.png
  FILE images/theme/grey/saveImage.png images/theme/grey/saveImage.png
  FILE images/theme/grey/snakeImage1.png images/theme/grey/snakeImage1.png
  FILE images/theme/grey/snakeImage2.png images/theme/grey/snakeImage2.png
  
  FILE images/motoSplash.png images/motoSplash.png
  FILE images/theme/default/saveImage.png images/saveImage.png

  FILE images/themes.txt images/themes.txt

  FILE sounds/blaster.wav sounds/blaster.wav
  FILE sounds/exp.wav sounds/exp1.wav
  FILE sounds/OutThere.ogg sounds/OutThere.ogg
  FILE sounds/HeroImmortal.ogg sounds/HeroImmortal.ogg

  FILE sce_sys/icon0.png sce_sys/icon0.png
  FILE sce_sys/pic0.png sce_sys/pic0.png
  FILE sce_sys/livearea/contents/bg.png sce_sys/livearea/contents/bg.png
  FILE sce_sys/livearea/contents/startup.png sce_sys/livearea/contents/startup.png
  FILE sce_sys/livearea/contents/template.xml sce_sys/livearea/contents/template.xml

  FILE font/font.ttf font/font.ttf

  FILE build/buildDate.txt buildDate.txt
)
