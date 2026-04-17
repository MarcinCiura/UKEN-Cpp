cmake_minimum_required(VERSION 3.14)
project(lab_05_mapy)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
# (Tylko dla Windowsa) Zapobiega nadpisywaniu ustawień kompilatora przez GoogleTest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  main main.cpp funkcje.cpp
)

add_executable(
  lab05test funkcje_test.cpp funkcje.cpp
)

target_link_libraries(
  lab05test GTest::gtest_main
)

#include(GoogleTest)
#gtest_discover_tests(hello_test)
