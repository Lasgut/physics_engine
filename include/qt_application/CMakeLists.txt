cmake_minimum_required(VERSION 3.5)

project(qt_application VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6 components
find_package(Qt6 REQUIRED COMPONENTS Widgets OpenGL Charts)

set(LIB_SOURCES
    MainWindow.cpp
    MainWindow.h
    MainWindow.ui
)

set(EXECUTABLE_SOURCES
    main.cpp
)

# Application target
qt_add_executable(qt_application
    MANUAL_FINALIZATION
    ${EXECUTABLE_SOURCES}
    ${LIB_SOURCES}
)

target_link_libraries(qt_application PUBLIC
    Qt6::Widgets
    Qt6::OpenGL
    Qt6::Charts
)

# Install
include(GNUInstallDirs)
install(TARGETS qt_application
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

#### Make it a library too ####
add_library(qt_application_lib STATIC ${LIB_SOURCES})

target_link_libraries(qt_application_lib PUBLIC
    Qt6::Widgets
    Qt6::OpenGL
    Qt6::Charts
)

target_include_directories(qt_application_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

