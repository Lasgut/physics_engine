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
include_directories(include)
include_directories(shaders)
include_directories(resources)
include_directories(third_party)

find_package(SDL2 REQUIRED)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Eigen3 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} 
                    ${glm_INCLUDE_DIRS} 
                    ${OPENGL_INCLUDE_DIRS}
                    ${EIGEN3_INCLUDE_DIRS})

# Gather all .cpp files in the sources/objects and sources/shapes directories
file(GLOB OBJECT_SOURCES "sources/objects/*.cpp")
file(GLOB SHAPE_SOURCES "sources/shapes/*.cpp")
file(GLOB TOOL_SOURCES "sources/tools/*.cpp")

# Add third-party sources (glad, imgui)
file(GLOB GLAD_SOURCES "third_party/glad/glad.c")
file(GLOB IMGUI_SOURCES 
    "third_party/imgui/imgui.cpp"
    "third_party/imgui/imgui_draw.cpp"
    "third_party/imgui/imgui_widgets.cpp"
    "third_party/imgui/imgui_tables.cpp"
    "third_party/imgui/backends/imgui_impl_opengl3.cpp"
    "third_party/imgui/backends/imgui_impl_sdl2.cpp"
)

set(SOURCES
    ${OBJECT_SOURCES}
    ${SHAPE_SOURCES}
    ${TOOL_SOURCES}
    ${GLAD_SOURCES}
    ${IMGUI_SOURCES}
    "Main.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} 
                      ${SDL2_LIBRARIES} 
                      ${OPENGL_LIBRARIES})

