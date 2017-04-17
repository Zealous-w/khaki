# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

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

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running interactive CMake command-line interface..."
	/usr/local/bin/cmake -i .
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/local/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/khaki/item/khaki/CMakeFiles /home/khaki/item/khaki/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/khaki/item/khaki/CMakeFiles 0
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
# Target rules for targets named khaki

# Build rule for target.
khaki: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 khaki
.PHONY : khaki

# fast build rule for target.
khaki/fast:
	$(MAKE) -f CMakeFiles/khaki.dir/build.make CMakeFiles/khaki.dir/build
.PHONY : khaki/fast

# target to build an object file
EventLoop.o:
	$(MAKE) -f CMakeFiles/khaki.dir/build.make CMakeFiles/khaki.dir/EventLoop.o
.PHONY : EventLoop.o

# target to preprocess a source file
EventLoop.i:
	$(MAKE) -f CMakeFiles/khaki.dir/build.make CMakeFiles/khaki.dir/EventLoop.i
.PHONY : EventLoop.i

# target to generate assembly for a file
EventLoop.s:
	$(MAKE) -f CMakeFiles/khaki.dir/build.make CMakeFiles/khaki.dir/EventLoop.s
.PHONY : EventLoop.s

# target to build an object file
EventLoopThread.o:
	$(MAKE) -f CMakeFiles/khaki.dir/build.make CMakeFiles/khaki.dir/EventLoopThread.o
.PHONY : EventLoopThread.o

# target to preprocess a source file
EventLoopThread.i:
	$(MAKE) -f CMakeFiles/khaki.dir/build.make CMakeFiles/khaki.dir/EventLoopThread.i
.PHONY : EventLoopThread.i

# target to generate assembly for a file
EventLoopThread.s:
	$(MAKE) -f CMakeFiles/khaki.dir/build.make CMakeFiles/khaki.dir/EventLoopThread.s
.PHONY : EventLoopThread.s

# target to build an object file
buffer.o:
	$(MAKE) -f CMakeFiles/khaki.dir/build.make CMakeFiles/khaki.dir/buffer.o
.PHONY : buffer.o

# target to preprocess a source file
buffer.i:
	$(MAKE) -f CMakeFiles/khaki.dir/build.make CMakeFiles/khaki.dir/buffer.i
.PHONY : buffer.i

# target to generate assembly for a file
buffer.s:
	$(MAKE) -f CMakeFiles/khaki.dir/build.make CMakeFiles/khaki.dir/buffer.s
.PHONY : buffer.s

# target to build an object file
channel.o:
	$(MAKE) -f CMakeFiles/khaki.dir/build.make CMakeFiles/khaki.dir/channel.o
.PHONY : channel.o

# target to preprocess a source file
channel.i:
	$(MAKE) -f CMakeFiles/khaki.dir/build.make CMakeFiles/khaki.dir/channel.i
.PHONY : channel.i

# target to generate assembly for a file
channel.s:
	$(MAKE) -f CMakeFiles/khaki.dir/build.make CMakeFiles/khaki.dir/channel.s
.PHONY : channel.s

# target to build an object file
net.o:
	$(MAKE) -f CMakeFiles/khaki.dir/build.make CMakeFiles/khaki.dir/net.o
.PHONY : net.o

# target to preprocess a source file
net.i:
	$(MAKE) -f CMakeFiles/khaki.dir/build.make CMakeFiles/khaki.dir/net.i
.PHONY : net.i

# target to generate assembly for a file
net.s:
	$(MAKE) -f CMakeFiles/khaki.dir/build.make CMakeFiles/khaki.dir/net.s
.PHONY : net.s

# target to build an object file
poll.o:
	$(MAKE) -f CMakeFiles/khaki.dir/build.make CMakeFiles/khaki.dir/poll.o
.PHONY : poll.o

# target to preprocess a source file
poll.i:
	$(MAKE) -f CMakeFiles/khaki.dir/build.make CMakeFiles/khaki.dir/poll.i
.PHONY : poll.i

# target to generate assembly for a file
poll.s:
	$(MAKE) -f CMakeFiles/khaki.dir/build.make CMakeFiles/khaki.dir/poll.s
.PHONY : poll.s

# target to build an object file
time_wheel.o:
	$(MAKE) -f CMakeFiles/khaki.dir/build.make CMakeFiles/khaki.dir/time_wheel.o
.PHONY : time_wheel.o

# target to preprocess a source file
time_wheel.i:
	$(MAKE) -f CMakeFiles/khaki.dir/build.make CMakeFiles/khaki.dir/time_wheel.i
.PHONY : time_wheel.i

# target to generate assembly for a file
time_wheel.s:
	$(MAKE) -f CMakeFiles/khaki.dir/build.make CMakeFiles/khaki.dir/time_wheel.s
.PHONY : time_wheel.s

# target to build an object file
util.o:
	$(MAKE) -f CMakeFiles/khaki.dir/build.make CMakeFiles/khaki.dir/util.o
.PHONY : util.o

# target to preprocess a source file
util.i:
	$(MAKE) -f CMakeFiles/khaki.dir/build.make CMakeFiles/khaki.dir/util.i
.PHONY : util.i

# target to generate assembly for a file
util.s:
	$(MAKE) -f CMakeFiles/khaki.dir/build.make CMakeFiles/khaki.dir/util.s
.PHONY : util.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... khaki"
	@echo "... rebuild_cache"
	@echo "... EventLoop.o"
	@echo "... EventLoop.i"
	@echo "... EventLoop.s"
	@echo "... EventLoopThread.o"
	@echo "... EventLoopThread.i"
	@echo "... EventLoopThread.s"
	@echo "... buffer.o"
	@echo "... buffer.i"
	@echo "... buffer.s"
	@echo "... channel.o"
	@echo "... channel.i"
	@echo "... channel.s"
	@echo "... net.o"
	@echo "... net.i"
	@echo "... net.s"
	@echo "... poll.o"
	@echo "... poll.i"
	@echo "... poll.s"
	@echo "... time_wheel.o"
	@echo "... time_wheel.i"
	@echo "... time_wheel.s"
	@echo "... util.o"
	@echo "... util.i"
	@echo "... util.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

