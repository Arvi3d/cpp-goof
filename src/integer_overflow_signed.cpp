// Summary: Signed Integer Overflow
// A signed integer overflow occurs when an arithmetic operation (like addition,
// subtraction, or multiplication) on signed integers results in a value
// that is outside the range that can be represented by the type (e.g.,
// too large positive or too small negative). In C++, signed integer
// overflow is explicitly Undefined Behavior (UB). This means the C++
// standard places no requirements on what happens; the program might crash,
// produce an incorrect result (which could be a wrap-around on some
// platforms, but this is not guaranteed), or exhibit other unpredictable
// behavior. Relying on any specific outcome of signed overflow is dangerous.

#include <iostream>
#include <limits> // Required for std::numeric_limits

void demonstrate_signed_overflow() {
    signed int max_val = std::numeric_limits<signed int>::max();
    std::cout << "Max signed int: " << max_val << std::endl;
    signed int result = max_val + 1; // Signed integer overflow: Undefined Behavior!
    // The actual result is unpredictable.
    std::cout << "Max signed int + 1 (signed overflow): " << result << std::endl;

    signed int min_val = std::numeric_limits<signed int>::min();
    std::cout << "Min signed int: " << min_val << std::endl;
    result = min_val - 1; // Signed integer underflow: Undefined Behavior!
    std::cout << "Min signed int - 1 (signed overflow): " << result << std::endl;
}

int main() {
    demonstrate_signed_overflow();
    return 0;
}

// Mitigation Strategy:
// To prevent or handle signed integer overflows:
// 1. Use Larger Data Types: If values might exceed the range of `signed int`,
//    use `long int` or `long long int`. Check `std::numeric_limits` for their ranges.
// 2. Pre-computation Checks: Before performing an operation, check if it
//    could lead to an overflow. For `a + b`:
//    If b > 0, check if a > std::numeric_limits<signed int>::max() - b.
//    If b < 0, check if a < std::numeric_limits<signed int>::min() - b.
//    Similar checks exist for subtraction, multiplication, and division.
// 3. Use Safe Integer Libraries: Libraries like Boost.SafeNumerics or CERT Secure Coding
//    Integer Library can perform checked arithmetic, throwing exceptions or
//    returning error codes on overflow.
// 4. Compiler Flags/Sanitizers: Utilize compiler features like GCC/Clang's
//    UndefinedBehaviorSanitizer (UBSan) with `-fsanitize=signed-integer-overflow`
//    to detect overflows at runtime during development and testing.
// 5. Cast to Larger Unsigned Type for Checks: Sometimes, casting operands to a
//    larger unsigned type before an operation can help detect potential overflow
//    if the result is then checked against the original signed type's limits.
//    However, this requires careful handling of signs.
// 6. Input Validation: Rigorously validate any external input that will be used
//    in arithmetic operations to ensure it's within safe bounds.
// 7. Code Reviews and Testing: Focus on arithmetic operations during code reviews
//    and test with boundary values (min/max int, zero, etc.).
