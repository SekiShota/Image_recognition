# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.24.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.24.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Shota-0128/Desktop/OpenCV_for_Cpp/capture_keyboard

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Shota-0128/Desktop/OpenCV_for_Cpp/capture_keyboard/build

# Include any dependencies generated for this target.
include CMakeFiles/Main.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Main.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Main.dir/flags.make

CMakeFiles/Main.dir/cap_key.cpp.o: CMakeFiles/Main.dir/flags.make
CMakeFiles/Main.dir/cap_key.cpp.o: /Users/Shota-0128/Desktop/OpenCV_for_Cpp/capture_keyboard/cap_key.cpp
CMakeFiles/Main.dir/cap_key.cpp.o: CMakeFiles/Main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Shota-0128/Desktop/OpenCV_for_Cpp/capture_keyboard/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Main.dir/cap_key.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Main.dir/cap_key.cpp.o -MF CMakeFiles/Main.dir/cap_key.cpp.o.d -o CMakeFiles/Main.dir/cap_key.cpp.o -c /Users/Shota-0128/Desktop/OpenCV_for_Cpp/capture_keyboard/cap_key.cpp

CMakeFiles/Main.dir/cap_key.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Main.dir/cap_key.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Shota-0128/Desktop/OpenCV_for_Cpp/capture_keyboard/cap_key.cpp > CMakeFiles/Main.dir/cap_key.cpp.i

CMakeFiles/Main.dir/cap_key.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Main.dir/cap_key.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Shota-0128/Desktop/OpenCV_for_Cpp/capture_keyboard/cap_key.cpp -o CMakeFiles/Main.dir/cap_key.cpp.s

# Object files for target Main
Main_OBJECTS = \
"CMakeFiles/Main.dir/cap_key.cpp.o"

# External object files for target Main
Main_EXTERNAL_OBJECTS =

Main: CMakeFiles/Main.dir/cap_key.cpp.o
Main: CMakeFiles/Main.dir/build.make
Main: /usr/local/lib/libopencv_gapi.4.6.0.dylib
Main: /usr/local/lib/libopencv_stitching.4.6.0.dylib
Main: /usr/local/lib/libopencv_alphamat.4.6.0.dylib
Main: /usr/local/lib/libopencv_aruco.4.6.0.dylib
Main: /usr/local/lib/libopencv_barcode.4.6.0.dylib
Main: /usr/local/lib/libopencv_bgsegm.4.6.0.dylib
Main: /usr/local/lib/libopencv_bioinspired.4.6.0.dylib
Main: /usr/local/lib/libopencv_ccalib.4.6.0.dylib
Main: /usr/local/lib/libopencv_dnn_objdetect.4.6.0.dylib
Main: /usr/local/lib/libopencv_dnn_superres.4.6.0.dylib
Main: /usr/local/lib/libopencv_dpm.4.6.0.dylib
Main: /usr/local/lib/libopencv_face.4.6.0.dylib
Main: /usr/local/lib/libopencv_freetype.4.6.0.dylib
Main: /usr/local/lib/libopencv_fuzzy.4.6.0.dylib
Main: /usr/local/lib/libopencv_hfs.4.6.0.dylib
Main: /usr/local/lib/libopencv_img_hash.4.6.0.dylib
Main: /usr/local/lib/libopencv_intensity_transform.4.6.0.dylib
Main: /usr/local/lib/libopencv_line_descriptor.4.6.0.dylib
Main: /usr/local/lib/libopencv_mcc.4.6.0.dylib
Main: /usr/local/lib/libopencv_quality.4.6.0.dylib
Main: /usr/local/lib/libopencv_rapid.4.6.0.dylib
Main: /usr/local/lib/libopencv_reg.4.6.0.dylib
Main: /usr/local/lib/libopencv_rgbd.4.6.0.dylib
Main: /usr/local/lib/libopencv_saliency.4.6.0.dylib
Main: /usr/local/lib/libopencv_sfm.4.6.0.dylib
Main: /usr/local/lib/libopencv_stereo.4.6.0.dylib
Main: /usr/local/lib/libopencv_structured_light.4.6.0.dylib
Main: /usr/local/lib/libopencv_superres.4.6.0.dylib
Main: /usr/local/lib/libopencv_surface_matching.4.6.0.dylib
Main: /usr/local/lib/libopencv_tracking.4.6.0.dylib
Main: /usr/local/lib/libopencv_videostab.4.6.0.dylib
Main: /usr/local/lib/libopencv_viz.4.6.0.dylib
Main: /usr/local/lib/libopencv_wechat_qrcode.4.6.0.dylib
Main: /usr/local/lib/libopencv_xfeatures2d.4.6.0.dylib
Main: /usr/local/lib/libopencv_xobjdetect.4.6.0.dylib
Main: /usr/local/lib/libopencv_xphoto.4.6.0.dylib
Main: /usr/local/lib/libopencv_shape.4.6.0.dylib
Main: /usr/local/lib/libopencv_highgui.4.6.0.dylib
Main: /usr/local/lib/libopencv_datasets.4.6.0.dylib
Main: /usr/local/lib/libopencv_plot.4.6.0.dylib
Main: /usr/local/lib/libopencv_text.4.6.0.dylib
Main: /usr/local/lib/libopencv_ml.4.6.0.dylib
Main: /usr/local/lib/libopencv_phase_unwrapping.4.6.0.dylib
Main: /usr/local/lib/libopencv_optflow.4.6.0.dylib
Main: /usr/local/lib/libopencv_ximgproc.4.6.0.dylib
Main: /usr/local/lib/libopencv_video.4.6.0.dylib
Main: /usr/local/lib/libopencv_videoio.4.6.0.dylib
Main: /usr/local/lib/libopencv_imgcodecs.4.6.0.dylib
Main: /usr/local/lib/libopencv_objdetect.4.6.0.dylib
Main: /usr/local/lib/libopencv_calib3d.4.6.0.dylib
Main: /usr/local/lib/libopencv_dnn.4.6.0.dylib
Main: /usr/local/lib/libopencv_features2d.4.6.0.dylib
Main: /usr/local/lib/libopencv_flann.4.6.0.dylib
Main: /usr/local/lib/libopencv_photo.4.6.0.dylib
Main: /usr/local/lib/libopencv_imgproc.4.6.0.dylib
Main: /usr/local/lib/libopencv_core.4.6.0.dylib
Main: CMakeFiles/Main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Shota-0128/Desktop/OpenCV_for_Cpp/capture_keyboard/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Main.dir/build: Main
.PHONY : CMakeFiles/Main.dir/build

CMakeFiles/Main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Main.dir/clean

CMakeFiles/Main.dir/depend:
	cd /Users/Shota-0128/Desktop/OpenCV_for_Cpp/capture_keyboard/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Shota-0128/Desktop/OpenCV_for_Cpp/capture_keyboard /Users/Shota-0128/Desktop/OpenCV_for_Cpp/capture_keyboard /Users/Shota-0128/Desktop/OpenCV_for_Cpp/capture_keyboard/build /Users/Shota-0128/Desktop/OpenCV_for_Cpp/capture_keyboard/build /Users/Shota-0128/Desktop/OpenCV_for_Cpp/capture_keyboard/build/CMakeFiles/Main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Main.dir/depend

