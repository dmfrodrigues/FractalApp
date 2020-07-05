cmake_minimum_required(VERSION 3.10)

project(fractalapp)

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../lib )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

find_package(wxWidgets COMPONENTS core base REQUIRED)

include_directories(../include)
include(${wxWidgets_USE_FILE})

add_library(fractalapp STATIC CURSOR_CROSS.cpp FractalBitmap.cpp FractalFrame.cpp FractalPanel.cpp HDPrintscreenDialog.cpp InfoPanel.cpp)

target_link_libraries(
    ${PROJECT_NAME}
    ${wxWidgets_LIBRARIES}
    )
