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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/liu/openairinterface5g/cmake_targets/oaisim_build_oai

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/liu/openairinterface5g/cmake_targets/oaisim_build_oai/build

# Utility rule file for ue_ip.

# Include the progress variables for this target.
include CMakeFiles/ue_ip.dir/progress.make

CMakeFiles/ue_ip: ue_ip.ko

ue_ip.ko:
	$(CMAKE_COMMAND) -E cmake_progress_report /home/liu/openairinterface5g/cmake_targets/oaisim_build_oai/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold /home/liu/openairinterface5g/openair2/NETWORK_DRIVER/UE_IP/netlink.c
	cd /home/liu/openairinterface5g/cmake_targets/oaisim_build_oai/build/CMakeFiles/ue_ip && make -C /lib/modules/3.19.0-031900-lowlatency/build M=/home/liu/openairinterface5g/cmake_targets/oaisim_build_oai/build/CMakeFiles/ue_ip

ue_ip: CMakeFiles/ue_ip
ue_ip: ue_ip.ko
ue_ip: CMakeFiles/ue_ip.dir/build.make
.PHONY : ue_ip

# Rule to build all files generated by this target.
CMakeFiles/ue_ip.dir/build: ue_ip
.PHONY : CMakeFiles/ue_ip.dir/build

CMakeFiles/ue_ip.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ue_ip.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ue_ip.dir/clean

CMakeFiles/ue_ip.dir/depend:
	cd /home/liu/openairinterface5g/cmake_targets/oaisim_build_oai/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/liu/openairinterface5g/cmake_targets/oaisim_build_oai /home/liu/openairinterface5g/cmake_targets/oaisim_build_oai /home/liu/openairinterface5g/cmake_targets/oaisim_build_oai/build /home/liu/openairinterface5g/cmake_targets/oaisim_build_oai/build /home/liu/openairinterface5g/cmake_targets/oaisim_build_oai/build/CMakeFiles/ue_ip.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ue_ip.dir/depend

