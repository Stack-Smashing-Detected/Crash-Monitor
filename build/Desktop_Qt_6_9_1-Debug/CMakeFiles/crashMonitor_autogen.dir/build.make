# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 4.0

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
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/cmake/1468/bin/cmake

# The command to remove a file.
RM = /snap/cmake/1468/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/victor-j-wilson/projects2/crashMonitor

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/victor-j-wilson/projects2/crashMonitor/build/Desktop_Qt_6_9_1-Debug

# Utility rule file for crashMonitor_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/crashMonitor_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/crashMonitor_autogen.dir/progress.make

CMakeFiles/crashMonitor_autogen: crashMonitor_autogen/timestamp

crashMonitor_autogen/timestamp: /home/victor-j-wilson/Qt/6.9.1/gcc_64/libexec/moc
crashMonitor_autogen/timestamp: /home/victor-j-wilson/Qt/6.9.1/gcc_64/libexec/uic
crashMonitor_autogen/timestamp: CMakeFiles/crashMonitor_autogen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/victor-j-wilson/projects2/crashMonitor/build/Desktop_Qt_6_9_1-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target crashMonitor"
	/snap/cmake/1468/bin/cmake -E cmake_autogen /home/victor-j-wilson/projects2/crashMonitor/build/Desktop_Qt_6_9_1-Debug/CMakeFiles/crashMonitor_autogen.dir/AutogenInfo.json Debug
	/snap/cmake/1468/bin/cmake -E touch /home/victor-j-wilson/projects2/crashMonitor/build/Desktop_Qt_6_9_1-Debug/crashMonitor_autogen/timestamp

CMakeFiles/crashMonitor_autogen.dir/codegen:
.PHONY : CMakeFiles/crashMonitor_autogen.dir/codegen

crashMonitor_autogen: CMakeFiles/crashMonitor_autogen
crashMonitor_autogen: crashMonitor_autogen/timestamp
crashMonitor_autogen: CMakeFiles/crashMonitor_autogen.dir/build.make
.PHONY : crashMonitor_autogen

# Rule to build all files generated by this target.
CMakeFiles/crashMonitor_autogen.dir/build: crashMonitor_autogen
.PHONY : CMakeFiles/crashMonitor_autogen.dir/build

CMakeFiles/crashMonitor_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/crashMonitor_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/crashMonitor_autogen.dir/clean

CMakeFiles/crashMonitor_autogen.dir/depend:
	cd /home/victor-j-wilson/projects2/crashMonitor/build/Desktop_Qt_6_9_1-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/victor-j-wilson/projects2/crashMonitor /home/victor-j-wilson/projects2/crashMonitor /home/victor-j-wilson/projects2/crashMonitor/build/Desktop_Qt_6_9_1-Debug /home/victor-j-wilson/projects2/crashMonitor/build/Desktop_Qt_6_9_1-Debug /home/victor-j-wilson/projects2/crashMonitor/build/Desktop_Qt_6_9_1-Debug/CMakeFiles/crashMonitor_autogen.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/crashMonitor_autogen.dir/depend

