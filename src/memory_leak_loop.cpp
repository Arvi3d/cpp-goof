// Summary: Loop-Based Memory Leak
// A loop-based memory leak occurs when memory is allocated repeatedly
// inside a loop, but not deallocated within the same loop iteration
// or after the loop finishes. Each iteration allocates new memory,
// and if the pointers to previously allocated memory are lost (e.g.,
// by overwriting the pointer variable), that memory becomes unreachable
// and thus leaked. Over time, especially in long-running loops or loops
// with many iterations, this can consume significant amounts of memory,
// leading to performance degradation or program crashes.

void loop_leak() {
    for (int i = 0; i < 1000; ++i) {
        int* data = new int[100]; // Allocate memory in each iteration
        // data might be used here...
        // If 'data' is not deallocated with delete[] before the next iteration,
        // or before 'data' goes out of scope if it's the last iteration,
        // the memory allocated in this iteration will be leaked.
    }
}

int main() {
    loop_leak();
    // Memory allocated in each iteration of loop_leak() is now leaked.
    return 0;
}

// Mitigation Strategy:
// To prevent loop-based memory leaks:
// 1. Deallocate in the Same Scope: If memory is allocated within a loop
//    iteration, ensure it's deallocated before the end of that iteration
//    if it's no longer needed.
//    Example:
//    for (int i = 0; i < 1000; ++i) {
//        int* data = new int[100];
//        // use data
//        delete[] data; // Deallocate before next iteration
//    }
// 2. Use RAII/Smart Pointers: Employ smart pointers like `std::unique_ptr`
//    or `std::shared_ptr`. These automatically manage memory, deallocating
//    it when the smart pointer goes out of scope (e.g., at the end of
//    each loop iteration if declared inside the loop).
//    Example:
//    for (int i = 0; i < 1000; ++i) {
//        std::unique_ptr<int[]> data = std::make_unique<int[]>(100);
//        // use data.get()
//        // Memory automatically freed when 'data' goes out of scope
//    }
// 3. Reuse Memory: If the size/type of the allocated memory is consistent,
//    consider allocating it once before the loop and reusing it in each
//    iteration. For collections, use standard library containers like
//    `std::vector` which manage their own memory.
// 4. Limit Allocation Frequency: If feasible, redesign the algorithm or data
//    structures to minimize the number of dynamic memory allocations within loops.
// 5. Profiling: Use memory profiling tools (e.g., Valgrind on Linux/macOS,
//    Visual Studio's debugger on Windows) to detect leaks occurring
//    within loops during runtime testing.
