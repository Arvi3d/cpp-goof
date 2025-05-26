cmake_minimum_required(VERSION 3.10)

project(CppGoofProject CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SQLite3 REQUIRED) # Added for SQLite

# CMAKE_TOOLCHAIN_FILE is now set via the command line in the Makefile
# set(CMAKE_TOOLCHAIN_FILE ${CMAKE_BINARY_DIR}/conan_toolchain.cmake) # This line is commented out

# Add source files as executables (assuming they are in the project root)
add_executable(buffer_overflow src/buffer_overflow.cpp)
add_executable(path_traversal src/path_traversal.cpp)
add_executable(sql_injection src/sql_injection.cpp)
add_executable(memory_leak_delete src/memory_leak_delete.cpp)
add_executable(memory_leak_destructor src/memory_leak_destructor.cpp)
add_executable(memory_leak_loop src/memory_leak_loop.cpp)
add_executable(resource_leak_file src/resource_leak_file.cpp)
add_executable(resource_leak_socket src/resource_leak_socket.cpp)
target_link_libraries(sql_injection PRIVATE SQLite::SQLite3) # Link to SQLite

# Optional: If you want to link libraries, you can use target_link_libraries()
# Example: target_link_libraries(my_executable PRIVATE my_library)

# Optional: Set compiler flags (e.g., for GCC)
# if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
# endif()

message(STATUS "CMakeLists.txt configured for CppGoofProject")
message(STATUS "To build, run:")
message(STATUS "  mkdir build")
message(STATUS "  cd build")
message(STATUS "  cmake ..")
message(STATUS "  make")
