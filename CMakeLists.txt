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

include_directories(sources)
include_directories(include)
include_directories(shaders)

find_package(SDL2 REQUIRED)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} 
                    ${glm_INCLUDE_DIRS} 
                    ${OPENGL_INCLUDE_DIRS})

set(SOURCES
    Main.cpp
    sources/glad.c
    sources/Window.cpp
    sources/Context.cpp
    sources/Axes.cpp
    sources/Cube.cpp
    sources/Camera.cpp
    sources/EventHandling.cpp
    sources/ShaderHandler.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} 
                      ${SDL2_LIBRARIES} 
                      ${GLEW_LIBRARIES} 
                      ${OPENGL_LIBRARIES})

