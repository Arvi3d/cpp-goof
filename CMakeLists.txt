cmake_minimum_required(VERSION 3.10)

project(CppGoofProject CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SQLite3 REQUIRED) # Added for SQLite
find_package(Threads REQUIRED)

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
add_executable(null_pointer_dereference src/null_pointer_dereference.cpp)
add_executable(dangling_pointer src/dangling_pointer.cpp)
add_executable(integer_overflow_signed src/integer_overflow_signed.cpp)
add_executable(integer_overflow_unsigned src/integer_overflow_unsigned.cpp)
add_executable(double_free_direct src/double_free_direct.cpp)
add_executable(double_free_aliased_pointer src/double_free_aliased_pointer.cpp)
add_executable(double_free_function src/double_free_function.cpp)
add_executable(concurrency_race_condition src/concurrency_race_condition.cpp)
add_executable(concurrency_deadlock src/concurrency_deadlock.cpp)
add_executable(concurrency_atomicity_violation src/concurrency_atomicity_violation.cpp)
add_executable(uninitialized_variable src/uninitialized_variable.cpp)
add_executable(command_injection src/command_injection.cpp)
add_executable(format_string src/format_string.cpp)
add_executable(incorrect_typecon_narrowing src/incorrect_typecon_narrowing.cpp)
add_executable(incorrect_typecon_signed src/incorrect_typecon_signed.cpp)
add_executable(incorrect_typecon_pointer src/incorrect_typecon_pointer.cpp)
add_executable(incorrect_typecon_unsafe_c src/incorrect_typecon_unsafe_c.cpp)
add_executable(division_zero_int src/division_zero_int.cpp)
add_executable(division_zero_double src/division_zero_double.cpp)
target_link_libraries(sql_injection PRIVATE SQLite::SQLite3) # Link to SQLite
target_link_libraries(concurrency_race_condition PRIVATE Threads::Threads)
target_link_libraries(concurrency_deadlock PRIVATE Threads::Threads)
target_link_libraries(concurrency_atomicity_violation PRIVATE Threads::Threads)

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
