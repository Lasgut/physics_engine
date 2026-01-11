###############################################################################
message(STATUS "#### SETUP:")
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR x86_64)
set(CMAKE_C_COMPILER   gcc)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_PREFIX_PATH "/home/lasse/Qt/6.9.1/gcc_64/lib/cmake")
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

cmake_minimum_required(VERSION 3.10)
project(PHYSICS_ENGINE VERSION 1.0 LANGUAGES CXX C)

###############################################################################
message(STATUS "#### FIND PACKAGES:")
find_package(Threads REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Widgets OpenGL Charts)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Eigen3 REQUIRED)

##############################################################################
message(STATUS "#### SOURCE FILES:")
file(GLOB_RECURSE VISUALIZER_SOURCES        "sources/visualizer/*.cpp")
file(GLOB_RECURSE COMMON_ENTITY_SOURCES     "sources/entity/common/*.cpp")
file(GLOB_RECURSE UAV_SOURCES               "sources/entity/unmanned_aerial_vehicle/*.cpp")
file(GLOB_RECURSE APPLICATION_UTILS_SOURCES "sources/application_utilities/*.cpp")
file(GLOB_RECURSE DATA_PLOTTER_SOURCES      "sources/data_plotter/*.cpp")
file(GLOB_RECURSE SIMULATION_CORE_SOURCES   "sources/simulation_core/*.cpp")

file(GLOB GLAD_SOURCES "third_party/glad/src/gl.c")

set(SOURCES
    ${APPLICATION_UTILS_SOURCES}
    ${VISUALIZER_SOURCES}
    ${COMMON_ENTITY_SOURCES}
    ${UAV_SOURCES}
    ${GLAD_SOURCES}
    ${DATA_PLOTTER_SOURCES}
    ${SIMULATION_CORE_SOURCES}
    "Main.cpp"
)

###############################################################################
message(STATUS "#### INCLUDE DIRECTORIES:")
include_directories(include/data_containers)
include_directories(include/data_types)
include_directories(include/libraries)
include_directories(include/qt_application)
include_directories(sources/visualizer)
include_directories(sources/entity/common)
include_directories(sources/entity/unmanned_aerial_vehicle)
include_directories(sources/data_plotter)
include_directories(sources/application_utilities)
include_directories(sources/simulation_core)
include_directories(third_party/glad/include)
include_directories(third_party/stb)
include_directories(third_party/stl_reader)

add_subdirectory(include/qt_application)

include_directories(${glm_INCLUDE_DIRS} 
                    ${OPENGL_INCLUDE_DIRS}
                    ${EIGEN3_INCLUDE_DIRS})

###############################################################################
message(STATUS "#### CREATE EXECUTABLE:")
add_executable(${PROJECT_NAME} ${SOURCES})

###############################################################################
message(STATUS "#### LINK LIBRARIES:")
target_link_libraries(${PROJECT_NAME} 
    qt_application_lib
    Qt6::Widgets
    Qt6::Charts
    Qt6::OpenGL
    ${SDL2_LIBRARIES} 
    ${OPENGL_LIBRARIES})
