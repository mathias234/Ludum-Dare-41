cmake_minimum_required(VERSION 3.9)

################### Variables. ####################
# Change if you want modify path or other values. #
###################################################

set(PROJECT_NAME 3DGameEngine)
# Output Variables
set(OUTPUT_DEBUG /bin/debug)
set(OUTPUT_REL /bin/release)
# Folders files
set(CPP_DIR_1 Src)
set(CPP_DIR_2 Src/vendor/Binary-Reader-Writer)
set(CPP_DIR_3 Src/vendor/stb_image)


set(CPP_DIR_4 Src/vendor/physics)
set(CPP_DIR_5 Src/vendor/physics/broadphase)
set(CPP_DIR_6 Src/vendor/physics/collision)
set(CPP_DIR_7 Src/vendor/physics/common)
set(CPP_DIR_8 Src/vendor/physics/debug)
set(CPP_DIR_9 Src/vendor/physics/dynamics)
set(CPP_DIR_10 Src/vendor/physics/math)
set(CPP_DIR_11 Src/vendor/physics/scene)
set(CPP_DIR_12 Src/lighting)
set(CPP_DIR_13 Src/vendor/tinyobjloader)
set(CPP_DIR_14 Src/vendor/imgui)
set(CPP_DIR_15 Src/vendor/imgui/misc/freetype)
set(CPP_DIR_16 Src/vendor/imgui/misc/natvis)
set(CPP_DIR_17 Src/vendor/tinydir)


############## CMake Project ################
#        The main options of project        #
#############################################

project(${PROJECT_NAME})

add_definitions(
        -DGLEW_STATIC
)

################# Flags ################
# Defines Flags for Windows and Linux. #
########################################
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -static-libgcc")
set(CMAKE_CXX_STANDARD 11)

################ Files ################
#   --   Add files to project.   --   #
#######################################

file(GLOB SRC_FILES
        ${CPP_DIR_1}/*.*
        ${CPP_DIR_2}/*.*
        ${CPP_DIR_3}/*.*
        ${CPP_DIR_4}/*.*
        ${CPP_DIR_5}/*.*
        ${CPP_DIR_6}/*.*
        ${CPP_DIR_7}/*.*
        ${CPP_DIR_8}/*.*
        ${CPP_DIR_9}/*.*
        ${CPP_DIR_10}/*.*
        ${CPP_DIR_11}/*.*
        ${CPP_DIR_12}/*.*
        ${CPP_DIR_13}/*.*
        ${CPP_DIR_14}/*.*
        ${CPP_DIR_15}/*.*
        ${CPP_DIR_16}/*.*
        ${CPP_DIR_17}/*.*
        )

# Add executable to build.


include_directories(../Dependencies/glew-2.1.0/include)
include_directories(../Dependencies/GLFW/include)
include_directories(../Dependencies/glm-0.9.9-a2)
include_directories(../Dependencies/freetype/include)

link_directories(../Dependencies/GLFW/lib-vc2015)
link_directories(../Dependencies/glew-2.1.0/lib)
link_directories(../Dependencies/freetype/lib)

add_executable(${PROJECT_NAME} ${SRC_FILES})


# Link with other dependencies.
target_link_libraries(${PROJECT_NAME} freetyped.lib glew32s.lib glfw3.lib opengl32.lib User32.lib Gdi32.lib Shell32.lib)
