cmake_minimum_required(VERSION 3.10)
project(MCP2515_Driver_Test)

set(CMAKE_CXX_STANDARD 14)

# Where are our header files?
include_directories(Drivers/user_drivers/INC)

# Get GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# Fix for Windows compilation
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Create the Test Executable
add_executable(run_tests
    Drivers/user_drivers/SRC/MCP2515.cpp
    Drivers/user_drivers/TESTS/test_main.cpp # We make this next
)

# Link GTest
target_link_libraries(run_tests gtest_main)