# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /home/zhao/software/clion-2018.2.5/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/zhao/software/clion-2018.2.5/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zhao/work/project/circle

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zhao/work/project/circle/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/circle.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/circle.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/circle.dir/flags.make

CMakeFiles/circle.dir/main.cpp.o: CMakeFiles/circle.dir/flags.make
CMakeFiles/circle.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhao/work/project/circle/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/circle.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/circle.dir/main.cpp.o -c /home/zhao/work/project/circle/main.cpp

CMakeFiles/circle.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/circle.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhao/work/project/circle/main.cpp > CMakeFiles/circle.dir/main.cpp.i

CMakeFiles/circle.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/circle.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhao/work/project/circle/main.cpp -o CMakeFiles/circle.dir/main.cpp.s

# Object files for target circle
circle_OBJECTS = \
"CMakeFiles/circle.dir/main.cpp.o"

# External object files for target circle
circle_EXTERNAL_OBJECTS =

circle: CMakeFiles/circle.dir/main.cpp.o
circle: CMakeFiles/circle.dir/build.make
circle: /usr/local/lib/libopencv_stitching.so.4.0.0
circle: /usr/local/lib/libopencv_gapi.so.4.0.0
circle: /usr/local/lib/libopencv_videostab.so.4.0.0
circle: /usr/local/lib/libopencv_optflow.so.4.0.0
circle: /usr/local/lib/libopencv_rgbd.so.4.0.0
circle: /usr/local/lib/libopencv_bioinspired.so.4.0.0
circle: /usr/local/lib/libopencv_cudaobjdetect.so.4.0.0
circle: /usr/local/lib/libopencv_hfs.so.4.0.0
circle: /usr/local/lib/libopencv_dpm.so.4.0.0
circle: /usr/local/lib/libopencv_tracking.so.4.0.0
circle: /usr/local/lib/libopencv_datasets.so.4.0.0
circle: /usr/local/lib/libopencv_aruco.so.4.0.0
circle: /usr/local/lib/libopencv_dnn_objdetect.so.4.0.0
circle: /usr/local/lib/libopencv_img_hash.so.4.0.0
circle: /usr/local/lib/libopencv_freetype.so.4.0.0
circle: /usr/local/lib/libopencv_hdf.so.4.0.0
circle: /usr/local/lib/libopencv_cudabgsegm.so.4.0.0
circle: /usr/local/lib/libopencv_stereo.so.4.0.0
circle: /usr/local/lib/libopencv_fuzzy.so.4.0.0
circle: /usr/local/lib/libopencv_ximgproc.so.4.0.0
circle: /usr/local/lib/libopencv_cudastereo.so.4.0.0
circle: /usr/local/lib/libopencv_xphoto.so.4.0.0
circle: /usr/local/lib/libopencv_ccalib.so.4.0.0
circle: /usr/local/lib/libopencv_xobjdetect.so.4.0.0
circle: /usr/local/lib/libopencv_superres.so.4.0.0
circle: /usr/local/lib/libopencv_plot.so.4.0.0
circle: /usr/local/lib/libopencv_bgsegm.so.4.0.0
circle: /usr/local/lib/libopencv_line_descriptor.so.4.0.0
circle: /usr/local/lib/libopencv_reg.so.4.0.0
circle: /usr/local/lib/libopencv_saliency.so.4.0.0
circle: /usr/local/lib/libopencv_surface_matching.so.4.0.0
circle: /usr/local/lib/libopencv_cudacodec.so.4.0.0
circle: /usr/local/lib/libopencv_face.so.4.0.0
circle: /usr/local/lib/libopencv_xfeatures2d.so.4.0.0
circle: /usr/local/lib/libopencv_shape.so.4.0.0
circle: /usr/local/lib/libopencv_structured_light.so.4.0.0
circle: /usr/local/lib/libopencv_cudafeatures2d.so.4.0.0
circle: /usr/local/lib/libopencv_text.so.4.0.0
circle: /usr/local/lib/libopencv_ml.so.4.0.0
circle: /usr/local/lib/libopencv_dnn.so.4.0.0
circle: /usr/local/lib/libopencv_cudaoptflow.so.4.0.0
circle: /usr/local/lib/libopencv_cudawarping.so.4.0.0
circle: /usr/local/lib/libopencv_video.so.4.0.0
circle: /usr/local/lib/libopencv_photo.so.4.0.0
circle: /usr/local/lib/libopencv_objdetect.so.4.0.0
circle: /usr/local/lib/libopencv_cudaimgproc.so.4.0.0
circle: /usr/local/lib/libopencv_cudafilters.so.4.0.0
circle: /usr/local/lib/libopencv_cudaarithm.so.4.0.0
circle: /usr/local/lib/libopencv_calib3d.so.4.0.0
circle: /usr/local/lib/libopencv_features2d.so.4.0.0
circle: /usr/local/lib/libopencv_flann.so.4.0.0
circle: /usr/local/lib/libopencv_highgui.so.4.0.0
circle: /usr/local/lib/libopencv_videoio.so.4.0.0
circle: /usr/local/lib/libopencv_imgcodecs.so.4.0.0
circle: /usr/local/lib/libopencv_phase_unwrapping.so.4.0.0
circle: /usr/local/lib/libopencv_imgproc.so.4.0.0
circle: /usr/local/lib/libopencv_core.so.4.0.0
circle: /usr/local/lib/libopencv_cudev.so.4.0.0
circle: CMakeFiles/circle.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zhao/work/project/circle/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable circle"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/circle.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/circle.dir/build: circle

.PHONY : CMakeFiles/circle.dir/build

CMakeFiles/circle.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/circle.dir/cmake_clean.cmake
.PHONY : CMakeFiles/circle.dir/clean

CMakeFiles/circle.dir/depend:
	cd /home/zhao/work/project/circle/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zhao/work/project/circle /home/zhao/work/project/circle /home/zhao/work/project/circle/cmake-build-debug /home/zhao/work/project/circle/cmake-build-debug /home/zhao/work/project/circle/cmake-build-debug/CMakeFiles/circle.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/circle.dir/depend
