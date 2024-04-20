
# https://stackoverflow.com/questions/75567031/compiling-c-project-with-sqlite3-through-cmake
cmake_minimum_required(VERSION 3.22)
enable_testing()

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -ggdb")

project(
    
    Learning_GTK
    VERSION 1.0
    DESCRIPTION "A learn project with GTK and Cmake"
    LANGUAGES C

)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk4)

include_directories(${GTK_INCLUDE_DIRS})
link_directories(${GTK_LIBRARY_DIRS})

execute_process(
    COMMAND pkg-config --cflags gtk4
    OUTPUT_VARIABLE GTK_CFLAGS
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
    COMMAND pkg-config --libs gtk4
    OUTPUT_VARIABLE GTK_LIBS
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

string(REGEX REPLACE "-mfpmath=sse" "" GTK_CFLAGS "${GTK_CFLAGS}")
string(REPLACE " " ";" GTK_CFLAGS_LIST ${GTK_CFLAGS})

add_subdirectory(src/libs)

file(GLOB SOURCES "src/*.c")
add_executable(

    main

    ${SOURCES}

)

target_compile_options(main PUBLIC src/feats)
target_compile_options(main PRIVATE ${GTK_CFLAGS_LIST})
target_link_libraries(main ${GTK_LIBS} ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR} -lsqlite3)

