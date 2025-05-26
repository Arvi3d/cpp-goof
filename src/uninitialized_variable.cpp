// Summary: Uninitialized Variable
// Using an uninitialized variable in C++ leads to undefined behavior.
// When a variable is declared but not explicitly initialized (for non-static
// local variables of built-in types or POD types), its initial value is
// indeterminate (it holds whatever garbage value was in that memory location).
// Reading from such a variable before assigning a value can result in
// unpredictable program behavior, crashes, incorrect calculations, or even
// security vulnerabilities if the garbage value influences control flow or data.

#include <iostream>

void use_uninitialized_variable() {
    int uninitialized_val; // Declared but not initialized
    // For static or global variables, they are zero-initialized by default.
    // For local non-static POD types, their initial value is indeterminate.

    std::cout << "Attempting to use uninitialized_val..." << std::endl;
    // The following line reads from an uninitialized variable.
    // Its behavior is undefined. It might print a garbage value, or crash.
    std::cout << "Value of uninitialized_val: " << uninitialized_val << std::endl;

    if (uninitialized_val > 0) { // Behavior of this condition is undefined
        std::cout << "uninitialized_val was positive (undefined behavior)." << std::endl;
    } else {
        std::cout << "uninitialized_val was not positive (undefined behavior)." << std::endl;
    }
}

int main() {
    use_uninitialized_variable();
    return 0;
}

// Mitigation Strategy:
// To prevent issues with uninitialized variables:
// 1. Always Initialize Variables: Initialize variables at the point of
//    declaration.
//    Example: `int initialized_val = 0;` or `int initialized_val{0};` (C++11 uniform initialization)
// 2. Scope Variables Tightly: Declare variables in the smallest possible scope,
//    ideally just before their first use, making it easier to ensure they are
//    initialized.
// 3. Constructor Initialization Lists: For class member variables, initialize
//    them in the constructor's member initializer list rather than assigning
//    values in the constructor body. This is especially important for const
//    members, reference members, and members of class types without default
//    constructors.
// 4. Compiler Warnings: Enable and heed compiler warnings. Most modern compilers
//    (e.g., GCC with `-Wall` or `-Wuninitialized`, Clang with `-Wuninitialized`)
//    can detect and warn about many uses of uninitialized variables.
// 5. Static Analysis Tools: Use static analysis tools (linters, SAST tools)
//    which can often identify more complex cases of uninitialized variable usage.
// 6. Default Member Initializers (C++11 onwards): For class member variables,
//    you can provide default initializers directly in the class definition.
//    Example: `class MyClass { int count = 0; };`
// 7. Zero-Initialization: When in doubt, initializing to a sensible default (like
//    zero for numeric types, `nullptr` for pointers) is often a good practice.
