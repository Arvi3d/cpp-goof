// Summary: Division by Zero (Integer)
// Attempting to divide an integer by zero in C++ results in undefined
// behavior. On most modern systems, this will cause a runtime exception
// (e.g., a floating-point exception, though it's integer division, or a
// specific integer divide-by-zero exception) that, if unhandled, terminates
// the program. Unlike floating-point division by zero which can result in
// Inf or NaN, integer division by zero is typically a crash. This can lead
// to denial of service if an attacker can control the divisor.

#include <iostream>

int main() {
    int numerator = 10;
    int denominator = 0;
    int result = numerator / denominator; // Undefined behavior! Likely crash
    return 0;
}

// Mitigation Strategy:
// To prevent integer division by zero:
// 1. Check the Divisor: Always check if the divisor is zero before performing
//    an integer division operation.
//    Example:
//    if (divisor == 0) {
//        // Handle error: log, return error code, throw exception, etc.
//        std::cerr << "Error: Attempt to divide by zero." << std::endl;
//    } else {
//        result = numerator / divisor;
//    }
// 2. Input Validation: If the divisor comes from external input, validate it
//    rigorously to ensure it cannot be zero.
// 3. Use `try-catch` for Exceptions (Platform-Dependent): On some platforms,
//    integer division by zero might raise a catchable signal or exception
//    (e.g., SIGFPE on POSIX systems). However, relying on this is not portable
//    as integer division by zero is fundamentally undefined behavior in C++.
//    It's better to prevent it with checks.
// 4. Static Analysis: Some static analysis tools may be able to identify
//    potential paths where division by zero could occur.
// 5. Code Reviews: Carefully review code involving division to ensure divisors
//    are checked.
// 6. Fuzz Testing: Use fuzz testing to supply a wide range of inputs,
//    including zero for divisors, to uncover potential division by zero issues.
