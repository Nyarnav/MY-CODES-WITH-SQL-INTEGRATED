# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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

# The shell in which to execute make rules.

# The CMake executable.
CMAKE_COMMAND = /data/data/ru.iiec.cxxdroid/files/bin/cmake

# The command to remove a file.
RM = /data/data/ru.iiec.cxxdroid/files/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/storage/emulated/0/my-FIRST PROJECT WITH DB"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/storage/emulated/0/my-FIRST PROJECT WITH DB"

# Include any dependencies generated for this target.
include CMakeFiles/HelloSQLite.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/HelloSQLite.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/HelloSQLite.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HelloSQLite.dir/flags.make

CMakeFiles/HelloSQLite.dir/src/Base64.cpp.o: CMakeFiles/HelloSQLite.dir/flags.make
CMakeFiles/HelloSQLite.dir/src/Base64.cpp.o: src/Base64.cpp
CMakeFiles/HelloSQLite.dir/src/Base64.cpp.o: CMakeFiles/HelloSQLite.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/storage/emulated/0/my-FIRST PROJECT WITH DB/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/HelloSQLite.dir/src/Base64.cpp.o"
	/data/user/0/ru.iiec.cxxdroid/files/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/HelloSQLite.dir/src/Base64.cpp.o -MF CMakeFiles/HelloSQLite.dir/src/Base64.cpp.o.d -o CMakeFiles/HelloSQLite.dir/src/Base64.cpp.o -c "/storage/emulated/0/my-FIRST PROJECT WITH DB/src/Base64.cpp"

CMakeFiles/HelloSQLite.dir/src/Base64.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HelloSQLite.dir/src/Base64.cpp.i"
	/data/user/0/ru.iiec.cxxdroid/files/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/storage/emulated/0/my-FIRST PROJECT WITH DB/src/Base64.cpp" > CMakeFiles/HelloSQLite.dir/src/Base64.cpp.i

CMakeFiles/HelloSQLite.dir/src/Base64.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HelloSQLite.dir/src/Base64.cpp.s"
	/data/user/0/ru.iiec.cxxdroid/files/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/storage/emulated/0/my-FIRST PROJECT WITH DB/src/Base64.cpp" -o CMakeFiles/HelloSQLite.dir/src/Base64.cpp.s

CMakeFiles/HelloSQLite.dir/src/main.cpp.o: CMakeFiles/HelloSQLite.dir/flags.make
CMakeFiles/HelloSQLite.dir/src/main.cpp.o: src/main.cpp
CMakeFiles/HelloSQLite.dir/src/main.cpp.o: CMakeFiles/HelloSQLite.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/storage/emulated/0/my-FIRST PROJECT WITH DB/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/HelloSQLite.dir/src/main.cpp.o"
	/data/user/0/ru.iiec.cxxdroid/files/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/HelloSQLite.dir/src/main.cpp.o -MF CMakeFiles/HelloSQLite.dir/src/main.cpp.o.d -o CMakeFiles/HelloSQLite.dir/src/main.cpp.o -c "/storage/emulated/0/my-FIRST PROJECT WITH DB/src/main.cpp"

CMakeFiles/HelloSQLite.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HelloSQLite.dir/src/main.cpp.i"
	/data/user/0/ru.iiec.cxxdroid/files/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/storage/emulated/0/my-FIRST PROJECT WITH DB/src/main.cpp" > CMakeFiles/HelloSQLite.dir/src/main.cpp.i

CMakeFiles/HelloSQLite.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HelloSQLite.dir/src/main.cpp.s"
	/data/user/0/ru.iiec.cxxdroid/files/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/storage/emulated/0/my-FIRST PROJECT WITH DB/src/main.cpp" -o CMakeFiles/HelloSQLite.dir/src/main.cpp.s

# Object files for target HelloSQLite
HelloSQLite_OBJECTS = \
"CMakeFiles/HelloSQLite.dir/src/Base64.cpp.o" \
"CMakeFiles/HelloSQLite.dir/src/main.cpp.o"

# External object files for target HelloSQLite
HelloSQLite_EXTERNAL_OBJECTS =

HelloSQLite: CMakeFiles/HelloSQLite.dir/src/Base64.cpp.o
HelloSQLite: CMakeFiles/HelloSQLite.dir/src/main.cpp.o
HelloSQLite: CMakeFiles/HelloSQLite.dir/build.make
HelloSQLite: /data/user/0/ru.iiec.cxxdroid/files/sysroot/lib/libsqlite3.a
HelloSQLite: CMakeFiles/HelloSQLite.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/storage/emulated/0/my-FIRST PROJECT WITH DB/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable HelloSQLite"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HelloSQLite.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/HelloSQLite.dir/build: HelloSQLite
.PHONY : CMakeFiles/HelloSQLite.dir/build

CMakeFiles/HelloSQLite.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/HelloSQLite.dir/cmake_clean.cmake
.PHONY : CMakeFiles/HelloSQLite.dir/clean

CMakeFiles/HelloSQLite.dir/depend:
	cd "/storage/emulated/0/my-FIRST PROJECT WITH DB" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/storage/emulated/0/my-FIRST PROJECT WITH DB" "/storage/emulated/0/my-FIRST PROJECT WITH DB" "/storage/emulated/0/my-FIRST PROJECT WITH DB" "/storage/emulated/0/my-FIRST PROJECT WITH DB" "/storage/emulated/0/my-FIRST PROJECT WITH DB/CMakeFiles/HelloSQLite.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/HelloSQLite.dir/depend

