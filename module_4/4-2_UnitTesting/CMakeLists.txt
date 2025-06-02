cmake_minimum_required(VERSION 3.14)
cmake_policy(SET CMP0135 NEW)

project(4_2_UnitTesting)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# macOS-specific flag for compatibility with libc++
if(APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

include(FetchContent)

# Download and build GoogleTest
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip)
# Windows-specific runtime flag
set(gtest_force_shared_crt
    ON
    CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(4_2_UnitTesting test.cpp)
target_link_libraries(4_2_UnitTesting PRIVATE gtest_main gtest)
include(GoogleTest)
gtest_discover_tests(4_2_UnitTesting)
