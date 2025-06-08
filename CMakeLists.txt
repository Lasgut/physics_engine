cmake_minimum_required(VERSION 3.10.0)
project(physics_engine VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(OSBitness 32)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(OSBitness 64)
endif()
set (FullOutputDir "${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}${OSBitness}/${CMAKE_BUILD_TYPE}")
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${FullOutputDir}/static libs")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${FullOutputDir}")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${FullOutputDir}")

include_directories(include/data_containers)
include_directories(include/data_types)
include_directories(include/libraries)
include_directories(include/qt_application)
include_directories(sources/visualizer)
include_directories(sources/entity)
include_directories(sources/application_utilities)
include_directories(third_party/glad/include)
include_directories(third_party/stb)
include_directories(third_party/stl_reader)

add_subdirectory(include/qt_application)

find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Eigen3 REQUIRED)

include_directories(${glm_INCLUDE_DIRS} 
                    ${OPENGL_INCLUDE_DIRS}
                    ${EIGEN3_INCLUDE_DIRS})

# Gather all .cpp files in the sources/objects and sources/shapes directories
file(GLOB_RECURSE VISUALIZER_SOURCES        "sources/visualizer/*.cpp")
file(GLOB_RECURSE ENTITY_SOURCES            "sources/entity/*.cpp")
file(GLOB_RECURSE APPLICATION_UTILS_SOURCES "sources/application_utilities/*.cpp")

file(GLOB GLAD_SOURCES "third_party/glad/src/gl.c")

set(SOURCES
    ${APPLICATION_UTILS_SOURCES}
    ${VISUALIZER_SOURCES}
    ${ENTITY_SOURCES}
    ${GLAD_SOURCES}
    "Main.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} 
                      qt_application_lib
                      ${SDL2_LIBRARIES} 
                      ${OPENGL_LIBRARIES})

