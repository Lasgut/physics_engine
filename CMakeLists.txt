cmake_minimum_required(VERSION 3.10)
project(MySDL2Window VERSION 1.0)

# Specify the source files
set(SOURCES
    Main.cpp       # Use relative paths to your source files
    sources/Window.cpp
)

# Include the directory containing the header files
include_directories(sources)

# Find the SDL2 package
find_package(SDL2 REQUIRED)

# Specify the executable target
add_executable(my_window ${SOURCES})

# Link the SDL2 library to the executable
target_link_libraries(my_window SDL2::SDL2)

