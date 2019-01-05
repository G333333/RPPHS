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
  FILE images/gary.png images/gary.png
  FILE images/karen.png images/karen.png
  FILE images/jeff.png images/jeff.png
  FILE images/player.png images/player.png
  FILE images/Grid3.png images/Grid3.png
  FILE images/bullet.png images/bullet.png
  FILE images/cross.png images/cross.png
  FILE images/circle.png images/circle.png
  FILE images/triangle.png images/triangle.png
  FILE images/cursor-crosshair.png images/cursor-crosshair.png
  FILE images/cursor-duck.png images/cursor-duck.png
  FILE images/cursor-watcher.png images/cursor-watcher.png
  FILE images/cursor1.png images/cursor1.png
  FILE images/cursor2.png images/cursor2.png
  FILE images/saveImage.png images/saveImage.png
  FILE images/snakeImage1.png images/snakeImage1.png
  FILE images/snakeImage2.png images/snakeImage2.png
  FILE images/motoSplash.png images/motoSplash.png

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
)
