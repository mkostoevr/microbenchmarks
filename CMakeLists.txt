CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

project(microbenchmarks CXX ASM)

IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE "RelWithDebInfo")
ENDIF()

set(BENCHMARK_ENABLE_TESTING FALSE)
add_subdirectory(third_party/benchmark)

ADD_COMPILE_OPTIONS(-Wall -Wextra -Wpedantic -Werror)

ADD_EXECUTABLE(find_by_offset find_by_offset.cpp)
TARGET_LINK_LIBRARIES(find_by_offset benchmark::benchmark)
target_compile_options(find_by_offset PRIVATE -mavx2 -falign-functions=64 -falign-loops=64)

ADD_EXECUTABLE(function_alignment function_alignment.cpp function_alignment.s)
TARGET_LINK_LIBRARIES(function_alignment benchmark::benchmark)
