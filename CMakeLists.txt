CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

project(microbenchmarks CXX ASM)

IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE "RelWithDebInfo")
ENDIF()

set(BENCHMARK_ENABLE_TESTING FALSE)
add_subdirectory(third_party/benchmark)

ADD_COMPILE_OPTIONS(-Wall -Wextra -Wpedantic -Werror)

ADD_EXECUTABLE(search_in_cardinalities search_in_cardinalities.cpp)
TARGET_LINK_LIBRARIES(search_in_cardinalities benchmark::benchmark)
target_compile_options(search_in_cardinalities PRIVATE -mavx2 -falign-loops=64)

ADD_EXECUTABLE(hsum hsum.cpp)
TARGET_LINK_LIBRARIES(hsum benchmark::benchmark)
target_compile_options(hsum PRIVATE -mavx2 -falign-loops=64)

ADD_EXECUTABLE(function_alignment function_alignment.cpp function_alignment.s)
TARGET_LINK_LIBRARIES(function_alignment benchmark::benchmark)
