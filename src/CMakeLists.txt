cmake_minimum_required(VERSION 3.10)

project(fractalapp)

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../lib )

find_package(wxWidgets COMPONENTS core base REQUIRED)

include_directories(../include)
include(${wxWidgets_USE_FILE})

add_library(fractalapp STATIC CURSOR_CROSS.cpp FractalBitmap.cpp FractalFrame.cpp FractalPanel.cpp HDPrintscreenDialog.cpp InfoPanel.cpp)

target_link_libraries(
    ${PROJECT_NAME}
    ${wxWidgets_LIBRARIES}
    )

target_compile_options(fractalapp PRIVATE -g -Wall -pedantic -Wunused-result -pedantic-errors -Wextra -Wcast-align -Wcast-qual -Wchar-subscripts -Wcomment -Wconversion -Wdisabled-optimization -Wfloat-equal  -Wformat  -Wformat=2 -Wformat-nonliteral -Wformat-security -Wformat-y2k -Wimport -Winit-self -Winvalid-pch -Wmissing-braces -Wmissing-field-initializers -Wmissing-format-attribute -Wmissing-include-dirs -Wmissing-noreturn -Wpacked -Wparentheses  -Wpointer-arith -Wredundant-decls -Wreturn-type -Wsequence-point  -Wshadow -Wsign-compare  -Wstack-protector -Wstrict-aliasing -Wstrict-aliasing=2 -Wswitch  -Wswitch-default -Wswitch-enum -Wtrigraphs  -Wuninitialized -Wunknown-pragmas  -Wunreachable-code -Wunused -Wunused-function  -Wunused-label  -Wunused-parameter -Wunused-value  -Wunused-variable  -Wvariadic-macros -Wvolatile-register-var  -Wwrite-strings)
