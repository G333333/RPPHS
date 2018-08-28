# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/rob/Projects/RPPHS

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rob/Projects/RPPHS

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/rob/Projects/RPPHS/CMakeFiles /home/rob/Projects/RPPHS/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/rob/Projects/RPPHS/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named RPPHS.self

# Build rule for target.
RPPHS.self: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 RPPHS.self
.PHONY : RPPHS.self

# fast build rule for target.
RPPHS.self/fast:
	$(MAKE) -f CMakeFiles/RPPHS.self.dir/build.make CMakeFiles/RPPHS.self.dir/build
.PHONY : RPPHS.self/fast

#=============================================================================
# Target rules for targets named RPPHS.elf

# Build rule for target.
RPPHS.elf: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 RPPHS.elf
.PHONY : RPPHS.elf

# fast build rule for target.
RPPHS.elf/fast:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/build
.PHONY : RPPHS.elf/fast

#=============================================================================
# Target rules for targets named RPPHS.vpk

# Build rule for target.
RPPHS.vpk: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 RPPHS.vpk
.PHONY : RPPHS.vpk

# fast build rule for target.
RPPHS.vpk/fast:
	$(MAKE) -f CMakeFiles/RPPHS.vpk.dir/build.make CMakeFiles/RPPHS.vpk.dir/build
.PHONY : RPPHS.vpk/fast

bullet.obj: bullet.cpp.obj

.PHONY : bullet.obj

# target to build an object file
bullet.cpp.obj:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/bullet.cpp.obj
.PHONY : bullet.cpp.obj

bullet.i: bullet.cpp.i

.PHONY : bullet.i

# target to preprocess a source file
bullet.cpp.i:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/bullet.cpp.i
.PHONY : bullet.cpp.i

bullet.s: bullet.cpp.s

.PHONY : bullet.s

# target to generate assembly for a file
bullet.cpp.s:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/bullet.cpp.s
.PHONY : bullet.cpp.s

classic.obj: classic.cpp.obj

.PHONY : classic.obj

# target to build an object file
classic.cpp.obj:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/classic.cpp.obj
.PHONY : classic.cpp.obj

classic.i: classic.cpp.i

.PHONY : classic.i

# target to preprocess a source file
classic.cpp.i:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/classic.cpp.i
.PHONY : classic.cpp.i

classic.s: classic.cpp.s

.PHONY : classic.s

# target to generate assembly for a file
classic.cpp.s:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/classic.cpp.s
.PHONY : classic.cpp.s

fpsCounter.obj: fpsCounter.cpp.obj

.PHONY : fpsCounter.obj

# target to build an object file
fpsCounter.cpp.obj:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/fpsCounter.cpp.obj
.PHONY : fpsCounter.cpp.obj

fpsCounter.i: fpsCounter.cpp.i

.PHONY : fpsCounter.i

# target to preprocess a source file
fpsCounter.cpp.i:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/fpsCounter.cpp.i
.PHONY : fpsCounter.cpp.i

fpsCounter.s: fpsCounter.cpp.s

.PHONY : fpsCounter.s

# target to generate assembly for a file
fpsCounter.cpp.s:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/fpsCounter.cpp.s
.PHONY : fpsCounter.cpp.s

functions.obj: functions.cpp.obj

.PHONY : functions.obj

# target to build an object file
functions.cpp.obj:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/functions.cpp.obj
.PHONY : functions.cpp.obj

functions.i: functions.cpp.i

.PHONY : functions.i

# target to preprocess a source file
functions.cpp.i:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/functions.cpp.i
.PHONY : functions.cpp.i

functions.s: functions.cpp.s

.PHONY : functions.s

# target to generate assembly for a file
functions.cpp.s:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/functions.cpp.s
.PHONY : functions.cpp.s

game.obj: game.cpp.obj

.PHONY : game.obj

# target to build an object file
game.cpp.obj:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/game.cpp.obj
.PHONY : game.cpp.obj

game.i: game.cpp.i

.PHONY : game.i

# target to preprocess a source file
game.cpp.i:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/game.cpp.i
.PHONY : game.cpp.i

game.s: game.cpp.s

.PHONY : game.s

# target to generate assembly for a file
game.cpp.s:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/game.cpp.s
.PHONY : game.cpp.s

gary.obj: gary.cpp.obj

.PHONY : gary.obj

# target to build an object file
gary.cpp.obj:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/gary.cpp.obj
.PHONY : gary.cpp.obj

gary.i: gary.cpp.i

.PHONY : gary.i

# target to preprocess a source file
gary.cpp.i:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/gary.cpp.i
.PHONY : gary.cpp.i

gary.s: gary.cpp.s

.PHONY : gary.s

# target to generate assembly for a file
gary.cpp.s:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/gary.cpp.s
.PHONY : gary.cpp.s

highScores.obj: highScores.cpp.obj

.PHONY : highScores.obj

# target to build an object file
highScores.cpp.obj:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/highScores.cpp.obj
.PHONY : highScores.cpp.obj

highScores.i: highScores.cpp.i

.PHONY : highScores.i

# target to preprocess a source file
highScores.cpp.i:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/highScores.cpp.i
.PHONY : highScores.cpp.i

highScores.s: highScores.cpp.s

.PHONY : highScores.s

# target to generate assembly for a file
highScores.cpp.s:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/highScores.cpp.s
.PHONY : highScores.cpp.s

intro.obj: intro.cpp.obj

.PHONY : intro.obj

# target to build an object file
intro.cpp.obj:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/intro.cpp.obj
.PHONY : intro.cpp.obj

intro.i: intro.cpp.i

.PHONY : intro.i

# target to preprocess a source file
intro.cpp.i:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/intro.cpp.i
.PHONY : intro.cpp.i

intro.s: intro.cpp.s

.PHONY : intro.s

# target to generate assembly for a file
intro.cpp.s:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/intro.cpp.s
.PHONY : intro.cpp.s

jeff.obj: jeff.cpp.obj

.PHONY : jeff.obj

# target to build an object file
jeff.cpp.obj:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/jeff.cpp.obj
.PHONY : jeff.cpp.obj

jeff.i: jeff.cpp.i

.PHONY : jeff.i

# target to preprocess a source file
jeff.cpp.i:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/jeff.cpp.i
.PHONY : jeff.cpp.i

jeff.s: jeff.cpp.s

.PHONY : jeff.s

# target to generate assembly for a file
jeff.cpp.s:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/jeff.cpp.s
.PHONY : jeff.cpp.s

karen.obj: karen.cpp.obj

.PHONY : karen.obj

# target to build an object file
karen.cpp.obj:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/karen.cpp.obj
.PHONY : karen.cpp.obj

karen.i: karen.cpp.i

.PHONY : karen.i

# target to preprocess a source file
karen.cpp.i:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/karen.cpp.i
.PHONY : karen.cpp.i

karen.s: karen.cpp.s

.PHONY : karen.s

# target to generate assembly for a file
karen.cpp.s:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/karen.cpp.s
.PHONY : karen.cpp.s

main.obj: main.cpp.obj

.PHONY : main.obj

# target to build an object file
main.cpp.obj:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/main.cpp.obj
.PHONY : main.cpp.obj

main.i: main.cpp.i

.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s

.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/main.cpp.s
.PHONY : main.cpp.s

menu.obj: menu.cpp.obj

.PHONY : menu.obj

# target to build an object file
menu.cpp.obj:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/menu.cpp.obj
.PHONY : menu.cpp.obj

menu.i: menu.cpp.i

.PHONY : menu.i

# target to preprocess a source file
menu.cpp.i:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/menu.cpp.i
.PHONY : menu.cpp.i

menu.s: menu.cpp.s

.PHONY : menu.s

# target to generate assembly for a file
menu.cpp.s:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/menu.cpp.s
.PHONY : menu.cpp.s

miniJeff.obj: miniJeff.cpp.obj

.PHONY : miniJeff.obj

# target to build an object file
miniJeff.cpp.obj:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/miniJeff.cpp.obj
.PHONY : miniJeff.cpp.obj

miniJeff.i: miniJeff.cpp.i

.PHONY : miniJeff.i

# target to preprocess a source file
miniJeff.cpp.i:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/miniJeff.cpp.i
.PHONY : miniJeff.cpp.i

miniJeff.s: miniJeff.cpp.s

.PHONY : miniJeff.s

# target to generate assembly for a file
miniJeff.cpp.s:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/miniJeff.cpp.s
.PHONY : miniJeff.cpp.s

options.obj: options.cpp.obj

.PHONY : options.obj

# target to build an object file
options.cpp.obj:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/options.cpp.obj
.PHONY : options.cpp.obj

options.i: options.cpp.i

.PHONY : options.i

# target to preprocess a source file
options.cpp.i:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/options.cpp.i
.PHONY : options.cpp.i

options.s: options.cpp.s

.PHONY : options.s

# target to generate assembly for a file
options.cpp.s:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/options.cpp.s
.PHONY : options.cpp.s

particle.obj: particle.cpp.obj

.PHONY : particle.obj

# target to build an object file
particle.cpp.obj:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/particle.cpp.obj
.PHONY : particle.cpp.obj

particle.i: particle.cpp.i

.PHONY : particle.i

# target to preprocess a source file
particle.cpp.i:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/particle.cpp.i
.PHONY : particle.cpp.i

particle.s: particle.cpp.s

.PHONY : particle.s

# target to generate assembly for a file
particle.cpp.s:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/particle.cpp.s
.PHONY : particle.cpp.s

player.obj: player.cpp.obj

.PHONY : player.obj

# target to build an object file
player.cpp.obj:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/player.cpp.obj
.PHONY : player.cpp.obj

player.i: player.cpp.i

.PHONY : player.i

# target to preprocess a source file
player.cpp.i:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/player.cpp.i
.PHONY : player.cpp.i

player.s: player.cpp.s

.PHONY : player.s

# target to generate assembly for a file
player.cpp.s:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/player.cpp.s
.PHONY : player.cpp.s

saveIcon.obj: saveIcon.cpp.obj

.PHONY : saveIcon.obj

# target to build an object file
saveIcon.cpp.obj:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/saveIcon.cpp.obj
.PHONY : saveIcon.cpp.obj

saveIcon.i: saveIcon.cpp.i

.PHONY : saveIcon.i

# target to preprocess a source file
saveIcon.cpp.i:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/saveIcon.cpp.i
.PHONY : saveIcon.cpp.i

saveIcon.s: saveIcon.cpp.s

.PHONY : saveIcon.s

# target to generate assembly for a file
saveIcon.cpp.s:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/saveIcon.cpp.s
.PHONY : saveIcon.cpp.s

saveScreen.obj: saveScreen.cpp.obj

.PHONY : saveScreen.obj

# target to build an object file
saveScreen.cpp.obj:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/saveScreen.cpp.obj
.PHONY : saveScreen.cpp.obj

saveScreen.i: saveScreen.cpp.i

.PHONY : saveScreen.i

# target to preprocess a source file
saveScreen.cpp.i:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/saveScreen.cpp.i
.PHONY : saveScreen.cpp.i

saveScreen.s: saveScreen.cpp.s

.PHONY : saveScreen.s

# target to generate assembly for a file
saveScreen.cpp.s:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/saveScreen.cpp.s
.PHONY : saveScreen.cpp.s

snakeGuy.obj: snakeGuy.cpp.obj

.PHONY : snakeGuy.obj

# target to build an object file
snakeGuy.cpp.obj:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/snakeGuy.cpp.obj
.PHONY : snakeGuy.cpp.obj

snakeGuy.i: snakeGuy.cpp.i

.PHONY : snakeGuy.i

# target to preprocess a source file
snakeGuy.cpp.i:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/snakeGuy.cpp.i
.PHONY : snakeGuy.cpp.i

snakeGuy.s: snakeGuy.cpp.s

.PHONY : snakeGuy.s

# target to generate assembly for a file
snakeGuy.cpp.s:
	$(MAKE) -f CMakeFiles/RPPHS.elf.dir/build.make CMakeFiles/RPPHS.elf.dir/snakeGuy.cpp.s
.PHONY : snakeGuy.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... RPPHS.self"
	@echo "... RPPHS.elf"
	@echo "... RPPHS.vpk"
	@echo "... rebuild_cache"
	@echo "... bullet.obj"
	@echo "... bullet.i"
	@echo "... bullet.s"
	@echo "... classic.obj"
	@echo "... classic.i"
	@echo "... classic.s"
	@echo "... fpsCounter.obj"
	@echo "... fpsCounter.i"
	@echo "... fpsCounter.s"
	@echo "... functions.obj"
	@echo "... functions.i"
	@echo "... functions.s"
	@echo "... game.obj"
	@echo "... game.i"
	@echo "... game.s"
	@echo "... gary.obj"
	@echo "... gary.i"
	@echo "... gary.s"
	@echo "... highScores.obj"
	@echo "... highScores.i"
	@echo "... highScores.s"
	@echo "... intro.obj"
	@echo "... intro.i"
	@echo "... intro.s"
	@echo "... jeff.obj"
	@echo "... jeff.i"
	@echo "... jeff.s"
	@echo "... karen.obj"
	@echo "... karen.i"
	@echo "... karen.s"
	@echo "... main.obj"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... menu.obj"
	@echo "... menu.i"
	@echo "... menu.s"
	@echo "... miniJeff.obj"
	@echo "... miniJeff.i"
	@echo "... miniJeff.s"
	@echo "... options.obj"
	@echo "... options.i"
	@echo "... options.s"
	@echo "... particle.obj"
	@echo "... particle.i"
	@echo "... particle.s"
	@echo "... player.obj"
	@echo "... player.i"
	@echo "... player.s"
	@echo "... saveIcon.obj"
	@echo "... saveIcon.i"
	@echo "... saveIcon.s"
	@echo "... saveScreen.obj"
	@echo "... saveScreen.i"
	@echo "... saveScreen.s"
	@echo "... snakeGuy.obj"
	@echo "... snakeGuy.i"
	@echo "... snakeGuy.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

