# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\Program Files\JetBrains\CLion 2021.2.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Program Files\JetBrains\CLion 2021.2.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Coding\C\bigproject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Coding\C\bigproject\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/bigproject.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/bigproject.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bigproject.dir/flags.make

CMakeFiles/bigproject.dir/main.c.obj: CMakeFiles/bigproject.dir/flags.make
CMakeFiles/bigproject.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Coding\C\bigproject\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/bigproject.dir/main.c.obj"
	C:\PROGRA~1\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\bigproject.dir\main.c.obj -c D:\Coding\C\bigproject\main.c

CMakeFiles/bigproject.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/bigproject.dir/main.c.i"
	C:\PROGRA~1\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\Coding\C\bigproject\main.c > CMakeFiles\bigproject.dir\main.c.i

CMakeFiles/bigproject.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/bigproject.dir/main.c.s"
	C:\PROGRA~1\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\Coding\C\bigproject\main.c -o CMakeFiles\bigproject.dir\main.c.s

CMakeFiles/bigproject.dir/pageGuessNumber.c.obj: CMakeFiles/bigproject.dir/flags.make
CMakeFiles/bigproject.dir/pageGuessNumber.c.obj: ../pageGuessNumber.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Coding\C\bigproject\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/bigproject.dir/pageGuessNumber.c.obj"
	C:\PROGRA~1\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\bigproject.dir\pageGuessNumber.c.obj -c D:\Coding\C\bigproject\pageGuessNumber.c

CMakeFiles/bigproject.dir/pageGuessNumber.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/bigproject.dir/pageGuessNumber.c.i"
	C:\PROGRA~1\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\Coding\C\bigproject\pageGuessNumber.c > CMakeFiles\bigproject.dir\pageGuessNumber.c.i

CMakeFiles/bigproject.dir/pageGuessNumber.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/bigproject.dir/pageGuessNumber.c.s"
	C:\PROGRA~1\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\Coding\C\bigproject\pageGuessNumber.c -o CMakeFiles\bigproject.dir\pageGuessNumber.c.s

CMakeFiles/bigproject.dir/pageGluttonousSnake.c.obj: CMakeFiles/bigproject.dir/flags.make
CMakeFiles/bigproject.dir/pageGluttonousSnake.c.obj: ../pageGluttonousSnake.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Coding\C\bigproject\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/bigproject.dir/pageGluttonousSnake.c.obj"
	C:\PROGRA~1\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\bigproject.dir\pageGluttonousSnake.c.obj -c D:\Coding\C\bigproject\pageGluttonousSnake.c

CMakeFiles/bigproject.dir/pageGluttonousSnake.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/bigproject.dir/pageGluttonousSnake.c.i"
	C:\PROGRA~1\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\Coding\C\bigproject\pageGluttonousSnake.c > CMakeFiles\bigproject.dir\pageGluttonousSnake.c.i

CMakeFiles/bigproject.dir/pageGluttonousSnake.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/bigproject.dir/pageGluttonousSnake.c.s"
	C:\PROGRA~1\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\Coding\C\bigproject\pageGluttonousSnake.c -o CMakeFiles\bigproject.dir\pageGluttonousSnake.c.s

# Object files for target bigproject
bigproject_OBJECTS = \
"CMakeFiles/bigproject.dir/main.c.obj" \
"CMakeFiles/bigproject.dir/pageGuessNumber.c.obj" \
"CMakeFiles/bigproject.dir/pageGluttonousSnake.c.obj"

# External object files for target bigproject
bigproject_EXTERNAL_OBJECTS =

bigproject.exe: CMakeFiles/bigproject.dir/main.c.obj
bigproject.exe: CMakeFiles/bigproject.dir/pageGuessNumber.c.obj
bigproject.exe: CMakeFiles/bigproject.dir/pageGluttonousSnake.c.obj
bigproject.exe: CMakeFiles/bigproject.dir/build.make
bigproject.exe: CMakeFiles/bigproject.dir/linklibs.rsp
bigproject.exe: CMakeFiles/bigproject.dir/objects1.rsp
bigproject.exe: CMakeFiles/bigproject.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Coding\C\bigproject\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable bigproject.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\bigproject.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bigproject.dir/build: bigproject.exe
.PHONY : CMakeFiles/bigproject.dir/build

CMakeFiles/bigproject.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\bigproject.dir\cmake_clean.cmake
.PHONY : CMakeFiles/bigproject.dir/clean

CMakeFiles/bigproject.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Coding\C\bigproject D:\Coding\C\bigproject D:\Coding\C\bigproject\cmake-build-debug D:\Coding\C\bigproject\cmake-build-debug D:\Coding\C\bigproject\cmake-build-debug\CMakeFiles\bigproject.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bigproject.dir/depend

