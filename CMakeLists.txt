cmake_minimum_required(VERSION 3.14)
PROJECT(z3wasm)
add_compile_options(-Wall -Wextra)# -pedantic -Werror)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
#set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -stdlib=libc++")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")

#fmtlib
include_directories(${PROJECT_SOURCE_DIR}/fmtlib/include)
add_subdirectory("fmtlib")

# Z3
set(Z3_BUILD_LIBZ3_SHARED OFF)
set(Z3_SINGLE_THREADED TRUE)
set(Z3_ENABLE_TRACING_FOR_NON_DEBUG TRUE)
#set(Z3_LINK_TIME_OPTIMIZATION OFF)
#set(Z3_C_EXAMPLES_FORCE_CXX_LINKER ON)
set(Z3_BUILD_TYPE Release)
include_directories(${PROJECT_SOURCE_DIR}/z3/src/)
include_directories(${PROJECT_SOURCE_DIR}/z3/src/api/)
include_directories(${PROJECT_SOURCE_DIR}/z3/src/api/c++/)
add_subdirectory("z3")

add_executable(z3wasm main.cpp)
# their cmake is broken and they output liblibz3
target_link_libraries(z3wasm optimized libz3 fmt)


