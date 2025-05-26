// Summary: Null Pointer Dereference
// A null pointer dereference occurs when a program attempts to access
// (read or write) the memory location that a null pointer points to.
// Since a null pointer, by definition, does not point to a valid memory
// object, this operation is undefined behavior. On most systems, it
// results in a program crash (e.g., segmentation fault, access violation).
// This is a common and often critical bug, as it can lead to unexpected
// program termination and, in some contexts, security vulnerabilities if
// an attacker can control the conditions leading to the dereference.

#include <iostream>

void cause_null_dereference() {
    int* ptr = nullptr; // ptr is a null pointer
    std::cout << "Attempting to dereference a null pointer..." << std::endl;
    *ptr = 10; // Dereferencing ptr: Undefined Behavior! Likely crash.
    std::cout << "Value: " << *ptr << std::endl; // This line likely won't be reached.
}

int main() {
    cause_null_dereference();
    return 0;
}

// Mitigation Strategy:
// To prevent null pointer dereferences:
// 1. Always Initialize Pointers: Initialize pointers to `nullptr` or a valid
//    memory address upon declaration. Uninitialized pointers can hold garbage
//    values that might coincidentally be valid addresses or zero.
// 2. Check for Null Before Dereferencing: Before dereferencing any pointer,
//    explicitly check if it is `nullptr`.
//    Example: if (ptr != nullptr) { *ptr = value; }
// 3. Use References Where Possible: C++ references must be initialized and
//    cannot be null (by standard). Prefer references over pointers when a
//    "null" state is not meaningful for the variable.
// 4. Smart Pointers: Use smart pointers like `std::unique_ptr` and
//    `std::shared_ptr`. While they can hold `nullptr`, their usage often
//    clarifies ownership and lifetime, reducing chances of misuse.
//    `std::shared_ptr` and `std::unique_ptr` can be checked against `nullptr`.
// 5. Assertions and Preconditions: Use assertions (e.g., `assert(ptr != nullptr);`)
//    during development and testing to catch null dereferences early.
//    Clearly document preconditions for functions that expect non-null pointers.
// 6. Code Reviews and Static Analysis: Employ static analysis tools that can
//    detect potential null pointer dereferences. Thorough code reviews can
//    also help identify such issues.
// 7. Avoid Returning Raw Pointers from Functions if Ownership is Unclear:
//    If a function returns a pointer, ensure its lifetime and nullability are
//    well-documented. Consider returning smart pointers or references.
// 8. Modern C++ Features: Use `std::optional` for values that might be absent,
//    instead of returning a null pointer to indicate absence.
