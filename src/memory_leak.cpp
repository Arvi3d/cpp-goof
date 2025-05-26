// Summary: Memory Leak (Missing Delete)
// A memory leak occurs when a program allocates memory dynamically (e.g., using 'new')
// but fails to deallocate it when it's no longer needed (e.g., using 'delete' or 'delete[]').
// This leads to a gradual loss of available memory, potentially causing the program
// to slow down or crash.

#include <iostream>

void demonstrate_leak() {
    int* data = new int[100]; // Allocate memory
    // data is used here...
    // Missing: delete[] data; // Memory is not deallocated
}

int main() {
    demonstrate_leak();
    // The memory allocated in demonstrate_leak is now leaked.
    std::cout << "Memory leak example finished. Check memory usage." << std::endl;
    return 0;
}

// Mitigation Strategy:
// Always ensure that dynamically allocated memory is deallocated using 'delete' for
// single objects or 'delete[]' for arrays when the memory is no longer needed.
// Consider using smart pointers (e.g., std::unique_ptr, std::shared_ptr) which
// automatically manage memory deallocation, reducing the risk of leaks.
// Regularly use memory profiling tools (e.g., Valgrind) to detect and diagnose leaks.
