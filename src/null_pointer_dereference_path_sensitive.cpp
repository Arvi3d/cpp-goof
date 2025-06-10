// Summary: Path-Sensitive Null Pointer Dereference (Safe Case)
// This example demonstrates a safe case of pointer dereference where null pointer
// checks are performed in all execution paths before any dereference.

#include <iostream>

// Simple data structure with self-referential pointer
struct Data {
    int x;
    Data *data;
};

// Function demonstrating safe recursive comparison with null checks
int compare(Data &a, Data &b) {
    // Get the pointer values to compare
    Data *aData = a.data;
    Data *bData = b.data;

    // First check: Equal pointers (both null or same address)
    if (aData == bData) {
        // If pointers are equal, they're either both null or point to same location
        return 0;
    }

    // Second check: Only aData is valid
    if (aData && !bData) {
        // aData is valid, bData is null - aData is "greater"
        return 1;
    }

    // Third check: Only bData is valid
    if (!aData && bData) {
        // aData is null, bData is valid - bData is "greater"
        return -1;
    }

    // At this point, we've covered all null cases:
    // 1. Both null (handled by first check)
    // 2. Only aData null (handled by third check)
    // 3. Only bData null (handled by second check)
    // 4. Both valid (reaches this point)
    // Therefore, dereferencing *aData and *bData is safe
    return compare(*aData, *bData); // This is safe due to prior checks
}

// Mitigation Strategy:
// While this example is safe due to comprehensive null checks, in general:
// 1. Always use null checks before dereferencing pointers
// 2. Consider using smart pointers (std::unique_ptr, std::shared_ptr) that handle
//    null cases automatically
// 3. Use std::optional for values that might not be present
// 4. Consider using assertions to verify pointer validity in debug builds
// 5. Use RAII (Resource Acquisition Is Initialization) to manage pointer lifetimes
// 6. Avoid raw pointer usage when possible, preferring references or smart pointers