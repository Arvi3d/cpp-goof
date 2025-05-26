// Summary: Resource Leak (File Handle)
// A resource leak occurs when a program acquires a system resource,
// such as a file handle, network socket, or database connection,
// but fails to release it when it's no longer needed. In C++,
// this often happens when a file is opened (e.g., using fopen or std::fstream)
// but not closed (e.g., using fclose or fstream::close()).
// Each unreleased handle consumes system resources. Accumulating
// unreleased handles can lead to resource exhaustion, preventing the
// program or even other system processes from acquiring new resources,
// potentially causing errors or crashes.

#include <fstream> // For std::ofstream
#include <iostream> // For std::cout (optional, for demonstration)

void file_handle_leak() {
    std::ofstream outfile("test_leak.txt"); // Open a file
    outfile << "Writing some data to the file.\n";
    // outfile.close(); // Missing: The file handle is not explicitly closed.
    // When 'outfile' goes out of scope, its destructor *should* close the file.
    // However, relying solely on RAII without explicit close can be risky if
    // exceptions occur before scope exit or if destructor behavior is non-standard.
    // For raw C file pointers (FILE*), explicit fclose is mandatory.
}

int main() {
    file_handle_leak();
    // The file handle for "test_leak.txt" might be leaked if not closed by destructor.
    std::cout << "File handle leak example finished. OS might hold the handle." << std::endl;
    return 0;
}

// Mitigation Strategy:
// To prevent resource leaks (specifically file handles):
// 1. Explicitly Close Resources: Always close file handles when you are
//    finished with them. For `std::fstream` objects, call the `close()`
//    method. For C-style `FILE*` pointers, use `fclose()`.
// 2. Use RAII (Resource Acquisition Is Initialization): This is a core C++
//    idiom. Objects like `std::fstream` are designed with RAII in mind;
//    their destructors automatically release the resource (close the file).
//    However, be mindful of potential issues:
//    a. Exceptions before scope exit: If an exception occurs after opening
//       and before the object goes out of scope, ensure cleanup.
//    b. Complex Scenarios: In more complex resource management, explicit
//       control might still be necessary.
// 3. Smart Pointers for Custom Resources: If you are managing custom
//    resources that are not standard library types, wrap them in classes
//    that follow RAII, potentially using smart pointers (`std::unique_ptr`
//    with a custom deleter) to ensure cleanup.
// 4. Check Return Values: Always check the return values of functions that
//    open resources (e.g., `fopen`, `fstream::is_open()`) to ensure the
//    resource was acquired successfully before attempting to use or close it.
// 5. Limit Resource Scope: Keep the scope of objects managing resources
//    as small as possible to ensure they are released promptly.
// 6. Static Analysis: Use static analysis tools that can detect potential
//    resource leaks.
