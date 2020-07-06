cmake_minimum_required(VERSION 3.10)

project(fractalapp-example)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR} )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_subdirectory(.. build)

find_package(wxWidgets COMPONENTS core base REQUIRED)

include_directories(../include)
include(${wxWidgets_USE_FILE})

if(WIN32)
    add_executable(fractalapp-example WIN32 FractalApp.cpp)
else(WIN32)
    add_executable(fractalapp-example FractalApp.cpp)
endif(WIN32)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    message(STATUS "GCC detected, adding compile flags")
    set(CPP_COMPILER_OPTIMIZE -ffast-math -O3)
    set(CPP_COMPILER_WARNINGS -Wall -Wunused-result -pedantic-errors -Wextra -Wcast-align -Wcast-qual -Wchar-subscripts
                          -Wcomment -Wconversion -Wdisabled-optimization -Wfloat-equal  -Wformat  -Wformat=2
                          -Wformat-nonliteral -Wformat-security -Wformat-y2k -Wimport -Winit-self -Winvalid-pch
                          -Wmissing-braces -Wmissing-field-initializers -Wmissing-format-attribute -Wmissing-include-dirs
                          -Wmissing-noreturn -Wpacked -Wparentheses  -Wpointer-arith -Wredundant-decls -Wreturn-type
                          -Wsequence-point  -Wshadow -Wsign-compare  -Wstack-protector -Wstrict-aliasing -Wstrict-aliasing=2
                          -Wswitch  -Wswitch-default -Wswitch-enum -Wtrigraphs  -Wuninitialized -Wunknown-pragmas 
                          -Wunreachable-code -Wunused -Wunused-function  -Wunused-label  -Wunused-parameter
                          -Wunused-value  -Wunused-variable  -Wvariadic-macros -Wvolatile-register-var  -Wwrite-strings)
    target_compile_options(fractalapp-example PRIVATE -g ${CPP_COMPILER_WARNINGS} ${CPP_COMPILER_OPTIMIZE})
endif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    message(STATUS "MSVC detected, adding compile flags")
    set(CPP_COMPILER_OPTIMIZE /O2 /GL)
    set(CPP_LINKER_OPTIMIZE /LTCG)
    set(CPP_COMPILER_WARNINGS /W4 /wd4068)
    target_compile_options(fractalapp-example PRIVATE ${CPP_COMPILER_WARNINGS} ${CPP_COMPILER_OPTIMIZE})
    target_link_options(fractalapp-example PRIVATE ${CPP_LINKER_OPTIMIZE})
endif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")

target_link_libraries(${PROJECT_NAME} fractalapp)
