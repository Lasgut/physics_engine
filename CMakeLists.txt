cmake_minimum_required(VERSION 3.10.0)
project(physics_engine VERSION 1.0)

set(OSBitness 32)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(OSBitness 64)
endif()
set (FullOutputDir "${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}${OSBitness}/${CMAKE_BUILD_TYPE}")
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${FullOutputDir}/static libs")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${FullOutputDir}")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${FullOutputDir}")

include_directories(sources/objects)
include_directories(sources/shapes)
include_directories(sources/tools)
include_directories(sources/tools_external)
include_directories(include)
include_directories(shaders)
include_directories(resources)

find_package(SDL2 REQUIRED)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Eigen3 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} 
                    ${glm_INCLUDE_DIRS} 
                    ${OPENGL_INCLUDE_DIRS}
                    ${EIGEN3_INCLUDE_DIRS})

set(SOURCES
    Main.cpp
    sources/objects/Drone.cpp
    sources/objects/Floor.cpp
    sources/objects/Axes.cpp
    sources/objects/Terrain.cpp
    sources/shapes/Line.cpp
    sources/shapes/Cube.cpp
    sources/shapes/Rectangle.cpp
    sources/shapes/Shape.cpp
    sources/shapes/Triangle.cpp
    sources/tools_external/glad.c
    sources/tools/Window.cpp
    sources/tools/Context.cpp
    sources/tools/Camera.cpp
    sources/tools/Clock.cpp
    sources/tools/EventHandler.cpp
    sources/tools/ShaderHandler.cpp
    sources/tools/Light.cpp
    sources/tools/Kinematics.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} 
                      ${SDL2_LIBRARIES} 
                      ${OPENGL_LIBRARIES})

