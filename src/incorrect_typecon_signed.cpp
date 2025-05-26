// Summary: Incorrect Type Conversion (Signed/Unsigned Mismatch)
// Mixing signed and unsigned integers in C++ can lead to unexpected behavior
// due to implicit conversion rules. When a signed integer is compared with or
// used in an arithmetic operation with an unsigned integer, the signed integer
// is often promoted to an unsigned type. If the signed integer was negative,
// this conversion results in a very large positive unsigned value (due to
// two's complement representation), leading to incorrect comparisons or
// calculation results. This can cause logical errors and potential
// vulnerabilities, especially in loop conditions, array indexing, or size checks.

#include <iostream>
#include <vector> // For std::vector::size_type example

void demonstrate_signed_unsigned_mismatch() {
    int signed_negative = -1;
    unsigned int unsigned_positive = 10;

    std::cout << "Signed negative: " << signed_negative << std::endl;
    std::cout << "Unsigned positive: " << unsigned_positive << std::endl;

    // Implicit conversion of signed_negative to unsigned in the comparison
    // On most systems, -1 (signed int) becomes a very large unsigned int (UINT_MAX).
    // So, UINT_MAX < 10 is false.
    if (signed_negative < unsigned_positive) { 
        std::cout << "(-1 < 10) is TRUE (This branch is taken if signed_negative was positive or if comparison logic was different)." << std::endl;
    } else {
        std::cout << "(-1 < 10) is FALSE (because -1 as unsigned is large) - Potential Bug!" << std::endl;
    }

    // A more robust way to compare, if you expect standard integer logic:
    bool comparison_result;
    if (signed_negative < 0) { // If signed is negative, it's always less than any unsigned (unless unsigned is 0 and signed is also 0 after conversion)
        comparison_result = true; 
    } else {
        // Now signed_negative is non-negative, safe to cast to unsigned for comparison
        comparison_result = static_cast<unsigned int>(signed_negative) < unsigned_positive;
    }
    std::cout << "Corrected comparison (-1 < 10): " << (comparison_result ? "TRUE" : "FALSE") << std::endl;

    // Example with vector size (size_type is usually unsigned)
    std::vector<int> my_vector; // Empty vector, size() is 0
    // int loop_count = -5; // A negative value
    // for (int i = 0; i < my_vector.size() + loop_count; ++i) { /* ... */ }
    // If loop_count is negative, my_vector.size() + loop_count might wrap around to a large
    // positive if my_vector.size() is small, leading to unexpected loop behavior or crashes.
    // A common mistake: for (int i = 0; i < vec.size() - N; ++i) where N > vec.size().
    // vec.size() - N underflows to a large unsigned number.
}

int main() {
    demonstrate_signed_unsigned_mismatch();
    return 0;
}

// Mitigation Strategy:
// To prevent issues from signed/unsigned mismatches:
// 1. Avoid Mixing Signed and Unsigned Types: The best practice is to use
//    consistent types (either all signed or all unsigned) in comparisons
//    and arithmetic operations.
// 2. Explicit Casts with Care: If mixing is unavoidable, use explicit casts
//    (`static_cast`) to make the conversion intent clear and to control how
//    it occurs. Be fully aware of the implications of casting a negative
//    signed value to unsigned.
//    Example: `if (signed_negative < static_cast<int>(unsigned_positive))` (if you know unsigned_positive fits in int)
//    Or: `if (static_cast<long long>(signed_negative) < static_cast<long long>(unsigned_positive))`
// 3. Compiler Warnings: Enable and heed compiler warnings about signed/unsigned
//    comparisons (e.g., GCC/Clang with `-Wsign-compare` which is part of `-Wall`).
// 4. Use Appropriate Types for Sizes and Indices: For array indices and container
//    sizes, use `size_t` or the container's `size_type`, which are unsigned.
//    When iterating, ensure loop variables are of a compatible (often unsigned) type.
//    If comparing with a signed variable, cast one carefully or check ranges.
// 5. Range Checks for Negative Values: Before comparing a signed variable with an
//    unsigned one, check if the signed variable is negative. If it is, the result
//    of a "less than" comparison with any unsigned value is typically true (unless
//    the unsigned value is 0 and the signed is also 0 after conversion).
//    `if (signed_val < 0 || static_cast<unsigned int>(signed_val) < unsigned_val)` (This logic needs care for 0)
// 6. Static Analysis: Use static analysis tools that can highlight problematic
//    mixed-sign operations.
