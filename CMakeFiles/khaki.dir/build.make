# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/khaki/item/khaki

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/khaki/item/khaki

# Include any dependencies generated for this target.
include CMakeFiles/khaki.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/khaki.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/khaki.dir/flags.make

CMakeFiles/khaki.dir/EventLoop.o: CMakeFiles/khaki.dir/flags.make
CMakeFiles/khaki.dir/EventLoop.o: EventLoop.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/khaki/item/khaki/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/khaki.dir/EventLoop.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/khaki.dir/EventLoop.o -c /home/khaki/item/khaki/EventLoop.cpp

CMakeFiles/khaki.dir/EventLoop.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/khaki.dir/EventLoop.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/khaki/item/khaki/EventLoop.cpp > CMakeFiles/khaki.dir/EventLoop.i

CMakeFiles/khaki.dir/EventLoop.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/khaki.dir/EventLoop.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/khaki/item/khaki/EventLoop.cpp -o CMakeFiles/khaki.dir/EventLoop.s

CMakeFiles/khaki.dir/EventLoop.o.requires:
.PHONY : CMakeFiles/khaki.dir/EventLoop.o.requires

CMakeFiles/khaki.dir/EventLoop.o.provides: CMakeFiles/khaki.dir/EventLoop.o.requires
	$(MAKE) -f CMakeFiles/khaki.dir/build.make CMakeFiles/khaki.dir/EventLoop.o.provides.build
.PHONY : CMakeFiles/khaki.dir/EventLoop.o.provides

CMakeFiles/khaki.dir/EventLoop.o.provides.build: CMakeFiles/khaki.dir/EventLoop.o

CMakeFiles/khaki.dir/channel.o: CMakeFiles/khaki.dir/flags.make
CMakeFiles/khaki.dir/channel.o: channel.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/khaki/item/khaki/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/khaki.dir/channel.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/khaki.dir/channel.o -c /home/khaki/item/khaki/channel.cpp

CMakeFiles/khaki.dir/channel.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/khaki.dir/channel.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/khaki/item/khaki/channel.cpp > CMakeFiles/khaki.dir/channel.i

CMakeFiles/khaki.dir/channel.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/khaki.dir/channel.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/khaki/item/khaki/channel.cpp -o CMakeFiles/khaki.dir/channel.s

CMakeFiles/khaki.dir/channel.o.requires:
.PHONY : CMakeFiles/khaki.dir/channel.o.requires

CMakeFiles/khaki.dir/channel.o.provides: CMakeFiles/khaki.dir/channel.o.requires
	$(MAKE) -f CMakeFiles/khaki.dir/build.make CMakeFiles/khaki.dir/channel.o.provides.build
.PHONY : CMakeFiles/khaki.dir/channel.o.provides

CMakeFiles/khaki.dir/channel.o.provides.build: CMakeFiles/khaki.dir/channel.o

CMakeFiles/khaki.dir/EventLoopThread.o: CMakeFiles/khaki.dir/flags.make
CMakeFiles/khaki.dir/EventLoopThread.o: EventLoopThread.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/khaki/item/khaki/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/khaki.dir/EventLoopThread.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/khaki.dir/EventLoopThread.o -c /home/khaki/item/khaki/EventLoopThread.cpp

CMakeFiles/khaki.dir/EventLoopThread.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/khaki.dir/EventLoopThread.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/khaki/item/khaki/EventLoopThread.cpp > CMakeFiles/khaki.dir/EventLoopThread.i

CMakeFiles/khaki.dir/EventLoopThread.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/khaki.dir/EventLoopThread.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/khaki/item/khaki/EventLoopThread.cpp -o CMakeFiles/khaki.dir/EventLoopThread.s

CMakeFiles/khaki.dir/EventLoopThread.o.requires:
.PHONY : CMakeFiles/khaki.dir/EventLoopThread.o.requires

CMakeFiles/khaki.dir/EventLoopThread.o.provides: CMakeFiles/khaki.dir/EventLoopThread.o.requires
	$(MAKE) -f CMakeFiles/khaki.dir/build.make CMakeFiles/khaki.dir/EventLoopThread.o.provides.build
.PHONY : CMakeFiles/khaki.dir/EventLoopThread.o.provides

CMakeFiles/khaki.dir/EventLoopThread.o.provides.build: CMakeFiles/khaki.dir/EventLoopThread.o

CMakeFiles/khaki.dir/time_wheel.o: CMakeFiles/khaki.dir/flags.make
CMakeFiles/khaki.dir/time_wheel.o: time_wheel.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/khaki/item/khaki/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/khaki.dir/time_wheel.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/khaki.dir/time_wheel.o -c /home/khaki/item/khaki/time_wheel.cpp

CMakeFiles/khaki.dir/time_wheel.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/khaki.dir/time_wheel.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/khaki/item/khaki/time_wheel.cpp > CMakeFiles/khaki.dir/time_wheel.i

CMakeFiles/khaki.dir/time_wheel.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/khaki.dir/time_wheel.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/khaki/item/khaki/time_wheel.cpp -o CMakeFiles/khaki.dir/time_wheel.s

CMakeFiles/khaki.dir/time_wheel.o.requires:
.PHONY : CMakeFiles/khaki.dir/time_wheel.o.requires

CMakeFiles/khaki.dir/time_wheel.o.provides: CMakeFiles/khaki.dir/time_wheel.o.requires
	$(MAKE) -f CMakeFiles/khaki.dir/build.make CMakeFiles/khaki.dir/time_wheel.o.provides.build
.PHONY : CMakeFiles/khaki.dir/time_wheel.o.provides

CMakeFiles/khaki.dir/time_wheel.o.provides.build: CMakeFiles/khaki.dir/time_wheel.o

CMakeFiles/khaki.dir/net.o: CMakeFiles/khaki.dir/flags.make
CMakeFiles/khaki.dir/net.o: net.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/khaki/item/khaki/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/khaki.dir/net.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/khaki.dir/net.o -c /home/khaki/item/khaki/net.cpp

CMakeFiles/khaki.dir/net.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/khaki.dir/net.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/khaki/item/khaki/net.cpp > CMakeFiles/khaki.dir/net.i

CMakeFiles/khaki.dir/net.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/khaki.dir/net.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/khaki/item/khaki/net.cpp -o CMakeFiles/khaki.dir/net.s

CMakeFiles/khaki.dir/net.o.requires:
.PHONY : CMakeFiles/khaki.dir/net.o.requires

CMakeFiles/khaki.dir/net.o.provides: CMakeFiles/khaki.dir/net.o.requires
	$(MAKE) -f CMakeFiles/khaki.dir/build.make CMakeFiles/khaki.dir/net.o.provides.build
.PHONY : CMakeFiles/khaki.dir/net.o.provides

CMakeFiles/khaki.dir/net.o.provides.build: CMakeFiles/khaki.dir/net.o

CMakeFiles/khaki.dir/buffer.o: CMakeFiles/khaki.dir/flags.make
CMakeFiles/khaki.dir/buffer.o: buffer.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/khaki/item/khaki/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/khaki.dir/buffer.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/khaki.dir/buffer.o -c /home/khaki/item/khaki/buffer.cpp

CMakeFiles/khaki.dir/buffer.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/khaki.dir/buffer.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/khaki/item/khaki/buffer.cpp > CMakeFiles/khaki.dir/buffer.i

CMakeFiles/khaki.dir/buffer.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/khaki.dir/buffer.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/khaki/item/khaki/buffer.cpp -o CMakeFiles/khaki.dir/buffer.s

CMakeFiles/khaki.dir/buffer.o.requires:
.PHONY : CMakeFiles/khaki.dir/buffer.o.requires

CMakeFiles/khaki.dir/buffer.o.provides: CMakeFiles/khaki.dir/buffer.o.requires
	$(MAKE) -f CMakeFiles/khaki.dir/build.make CMakeFiles/khaki.dir/buffer.o.provides.build
.PHONY : CMakeFiles/khaki.dir/buffer.o.provides

CMakeFiles/khaki.dir/buffer.o.provides.build: CMakeFiles/khaki.dir/buffer.o

CMakeFiles/khaki.dir/util.o: CMakeFiles/khaki.dir/flags.make
CMakeFiles/khaki.dir/util.o: util.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/khaki/item/khaki/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/khaki.dir/util.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/khaki.dir/util.o -c /home/khaki/item/khaki/util.cpp

CMakeFiles/khaki.dir/util.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/khaki.dir/util.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/khaki/item/khaki/util.cpp > CMakeFiles/khaki.dir/util.i

CMakeFiles/khaki.dir/util.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/khaki.dir/util.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/khaki/item/khaki/util.cpp -o CMakeFiles/khaki.dir/util.s

CMakeFiles/khaki.dir/util.o.requires:
.PHONY : CMakeFiles/khaki.dir/util.o.requires

CMakeFiles/khaki.dir/util.o.provides: CMakeFiles/khaki.dir/util.o.requires
	$(MAKE) -f CMakeFiles/khaki.dir/build.make CMakeFiles/khaki.dir/util.o.provides.build
.PHONY : CMakeFiles/khaki.dir/util.o.provides

CMakeFiles/khaki.dir/util.o.provides.build: CMakeFiles/khaki.dir/util.o

CMakeFiles/khaki.dir/poll.o: CMakeFiles/khaki.dir/flags.make
CMakeFiles/khaki.dir/poll.o: poll.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/khaki/item/khaki/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/khaki.dir/poll.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/khaki.dir/poll.o -c /home/khaki/item/khaki/poll.cpp

CMakeFiles/khaki.dir/poll.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/khaki.dir/poll.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/khaki/item/khaki/poll.cpp > CMakeFiles/khaki.dir/poll.i

CMakeFiles/khaki.dir/poll.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/khaki.dir/poll.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/khaki/item/khaki/poll.cpp -o CMakeFiles/khaki.dir/poll.s

CMakeFiles/khaki.dir/poll.o.requires:
.PHONY : CMakeFiles/khaki.dir/poll.o.requires

CMakeFiles/khaki.dir/poll.o.provides: CMakeFiles/khaki.dir/poll.o.requires
	$(MAKE) -f CMakeFiles/khaki.dir/build.make CMakeFiles/khaki.dir/poll.o.provides.build
.PHONY : CMakeFiles/khaki.dir/poll.o.provides

CMakeFiles/khaki.dir/poll.o.provides.build: CMakeFiles/khaki.dir/poll.o

# Object files for target khaki
khaki_OBJECTS = \
"CMakeFiles/khaki.dir/EventLoop.o" \
"CMakeFiles/khaki.dir/channel.o" \
"CMakeFiles/khaki.dir/EventLoopThread.o" \
"CMakeFiles/khaki.dir/time_wheel.o" \
"CMakeFiles/khaki.dir/net.o" \
"CMakeFiles/khaki.dir/buffer.o" \
"CMakeFiles/khaki.dir/util.o" \
"CMakeFiles/khaki.dir/poll.o"

# External object files for target khaki
khaki_EXTERNAL_OBJECTS =

libkhaki.a: CMakeFiles/khaki.dir/EventLoop.o
libkhaki.a: CMakeFiles/khaki.dir/channel.o
libkhaki.a: CMakeFiles/khaki.dir/EventLoopThread.o
libkhaki.a: CMakeFiles/khaki.dir/time_wheel.o
libkhaki.a: CMakeFiles/khaki.dir/net.o
libkhaki.a: CMakeFiles/khaki.dir/buffer.o
libkhaki.a: CMakeFiles/khaki.dir/util.o
libkhaki.a: CMakeFiles/khaki.dir/poll.o
libkhaki.a: CMakeFiles/khaki.dir/build.make
libkhaki.a: CMakeFiles/khaki.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libkhaki.a"
	$(CMAKE_COMMAND) -P CMakeFiles/khaki.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/khaki.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/khaki.dir/build: libkhaki.a
.PHONY : CMakeFiles/khaki.dir/build

CMakeFiles/khaki.dir/requires: CMakeFiles/khaki.dir/EventLoop.o.requires
CMakeFiles/khaki.dir/requires: CMakeFiles/khaki.dir/channel.o.requires
CMakeFiles/khaki.dir/requires: CMakeFiles/khaki.dir/EventLoopThread.o.requires
CMakeFiles/khaki.dir/requires: CMakeFiles/khaki.dir/time_wheel.o.requires
CMakeFiles/khaki.dir/requires: CMakeFiles/khaki.dir/net.o.requires
CMakeFiles/khaki.dir/requires: CMakeFiles/khaki.dir/buffer.o.requires
CMakeFiles/khaki.dir/requires: CMakeFiles/khaki.dir/util.o.requires
CMakeFiles/khaki.dir/requires: CMakeFiles/khaki.dir/poll.o.requires
.PHONY : CMakeFiles/khaki.dir/requires

CMakeFiles/khaki.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/khaki.dir/cmake_clean.cmake
.PHONY : CMakeFiles/khaki.dir/clean

CMakeFiles/khaki.dir/depend:
	cd /home/khaki/item/khaki && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/khaki/item/khaki /home/khaki/item/khaki /home/khaki/item/khaki /home/khaki/item/khaki /home/khaki/item/khaki/CMakeFiles/khaki.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/khaki.dir/depend

