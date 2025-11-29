cmake_minimum_required(VERSION 3.14)
project(lab_06)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

# Main Application
add_executable(lab_06 
    src/main.cpp 
    src/npc.cpp 
    src/knight.cpp 
    src/druid.cpp 
    src/elf.cpp
)

# Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(lab_06_tests 
    test/tests.cpp
    src/npc.cpp 
    src/knight.cpp 
    src/druid.cpp 
    src/elf.cpp
)

target_link_libraries(lab_06_tests gtest_main)

include(GoogleTest)
gtest_discover_tests(lab_06_tests)
