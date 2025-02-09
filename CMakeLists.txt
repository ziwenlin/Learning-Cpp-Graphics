cmake_minimum_required(VERSION 3.5...3.11)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ##############################################################################
# Setup project

project(
        LearningSFML
        VERSION 0.0.1
        LANGUAGES CXX)

set(SOURCES src/PhysicsObject.cpp
        src/SmartMouse.cpp
        include/SmartMouse.h)
set(TEST_SOURCES tests/test_PhysicsObject.cpp)

add_executable(${PROJECT_NAME} src/main.cpp ${SOURCES})
target_include_directories(${PROJECT_NAME}
        PRIVATE ${PROJECT_SOURCE_DIR}/include)

# ##############################################################################
# Setup libraries

# Externe library Simple and Fast Media Language
include(FetchContent)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL SYSTEM)
FetchContent_MakeAvailable(SFML)

# Externe library fmt
include(FetchContent)
FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG e69e5f977d458f2650bb346dadf2ad30c5320281) # 10.2.1
FetchContent_MakeAvailable(fmt)

# Link externe libraries
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)

# ##############################################################################
# CTest

# Enable CTest
enable_testing()

# Fetch Doctest (if not using system package)
include(FetchContent)
FetchContent_Declare(
  doctest
  GIT_REPOSITORY https://github.com/doctest/doctest.git
  GIT_TAG v2.4.9)
FetchContent_MakeAvailable(doctest)

# Link main sources to unit_tests
add_executable(unit_tests ${TEST_SOURCES} ${SOURCES})
target_include_directories(unit_tests PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Link testing framework Catch2
target_link_libraries(unit_tests PRIVATE doctest)
target_link_libraries(unit_tests PRIVATE SFML::Graphics)
target_link_libraries(unit_tests PRIVATE fmt::fmt)

# Register test with CTest
add_test(NAME UnitTest COMMAND unit_tests)
