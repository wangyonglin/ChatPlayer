# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/wangyonglin/QTestExamples/QEngineExamples/vendor/sherpa-ncnn

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wangyonglin/QTestExamples/QEngineExamples/vendor/sherpa-ncnn/build

# Utility rule file for ncnn-generate-spirv.

# Include any custom commands dependencies for this target.
include _deps/ncnn-build/src/CMakeFiles/ncnn-generate-spirv.dir/compiler_depend.make

# Include the progress variables for this target.
include _deps/ncnn-build/src/CMakeFiles/ncnn-generate-spirv.dir/progress.make

ncnn-generate-spirv: _deps/ncnn-build/src/CMakeFiles/ncnn-generate-spirv.dir/build.make
.PHONY : ncnn-generate-spirv

# Rule to build all files generated by this target.
_deps/ncnn-build/src/CMakeFiles/ncnn-generate-spirv.dir/build: ncnn-generate-spirv
.PHONY : _deps/ncnn-build/src/CMakeFiles/ncnn-generate-spirv.dir/build

_deps/ncnn-build/src/CMakeFiles/ncnn-generate-spirv.dir/clean:
	cd /home/wangyonglin/QTestExamples/QEngineExamples/vendor/sherpa-ncnn/build/_deps/ncnn-build/src && $(CMAKE_COMMAND) -P CMakeFiles/ncnn-generate-spirv.dir/cmake_clean.cmake
.PHONY : _deps/ncnn-build/src/CMakeFiles/ncnn-generate-spirv.dir/clean

_deps/ncnn-build/src/CMakeFiles/ncnn-generate-spirv.dir/depend:
	cd /home/wangyonglin/QTestExamples/QEngineExamples/vendor/sherpa-ncnn/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wangyonglin/QTestExamples/QEngineExamples/vendor/sherpa-ncnn /home/wangyonglin/QTestExamples/QEngineExamples/vendor/sherpa-ncnn/build/_deps/ncnn-src/src /home/wangyonglin/QTestExamples/QEngineExamples/vendor/sherpa-ncnn/build /home/wangyonglin/QTestExamples/QEngineExamples/vendor/sherpa-ncnn/build/_deps/ncnn-build/src /home/wangyonglin/QTestExamples/QEngineExamples/vendor/sherpa-ncnn/build/_deps/ncnn-build/src/CMakeFiles/ncnn-generate-spirv.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : _deps/ncnn-build/src/CMakeFiles/ncnn-generate-spirv.dir/depend

