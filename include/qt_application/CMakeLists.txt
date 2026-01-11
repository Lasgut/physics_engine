cmake_minimum_required(VERSION 3.16)

project(qt_application LANGUAGES CXX)

set(CMAKE_PREFIX_PATH "/home/lasse/Qt/6.9.1/gcc_64/lib/cmake")

# ============================================================
# Options
# ============================================================
option(QT_APPLICATION_STANDALONE
    "Build standalone Qt test application"
    OFF
)

# ============================================================
# Qt / C++ setup
# ============================================================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets OpenGL Charts)

# ============================================================
# Library (used by PHYSICS_ENGINE and test app)
# ============================================================
set(QT_APPLICATION_LIB_SOURCES
    ChartWidget.cpp
    ChartWidget.h
    MainWindow.cpp
    MainWindow.h
    MainWindow.ui
)

add_library(qt_application_lib STATIC
    ${QT_APPLICATION_LIB_SOURCES}
)

target_link_libraries(qt_application_lib
    PUBLIC
        Qt6::Widgets
        Qt6::OpenGL
        Qt6::Charts
)

target_include_directories(qt_application_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# ============================================================
# Optional standalone test executable
# ============================================================
if (QT_APPLICATION_STANDALONE)
    add_executable(qt_application_test
        main.cpp
    )

    target_link_libraries(qt_application_test
        PRIVATE
            qt_application_lib
    )

    set_target_properties(qt_application_test PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()

# ============================================================
# Diagnostics (optional but helpful)
# ============================================================
message(STATUS "Qt application standalone build: ${QT_APPLICATION_STANDALONE}")

