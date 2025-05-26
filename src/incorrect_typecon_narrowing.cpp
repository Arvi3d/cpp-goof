// Summary: Incorrect Type Conversion (Implicit Narrowing)
// Implicit narrowing conversion occurs when a value of a larger or wider
// data type is assigned or converted to a smaller or narrower data type,
// and this conversion might result in loss of data or precision without
// an explicit cast from the programmer. For example, assigning a `long`
// to an `int`, or a `double` to an `int`. While sometimes benign if the
// value fits, it can lead to data truncation, unexpected behavior,
// incorrect calculations, and bugs that are hard to detect if the value
// exceeds the range of the narrower type.

#include <iostream>
#include <limits> // For std::numeric_limits

void demonstrate_narrowing() {
    long long large_value = std::numeric_limits<int>::max() + 10LL;
    // This could also be a double value like 123.45 being assigned to an int.

    std::cout << "Original long long value: " << large_value << std::endl;

    // Implicit narrowing conversion from long long to int
    int narrow_val = large_value; // Potential loss of data!
                                  // Behavior is implementation-defined if out of range.

    std::cout << "Value after implicit narrowing to int: " << narrow_val << std::endl;
    // The 'narrow_val' will likely not hold the original 'large_value' correctly.

    double floating_point = 123.789;
    std::cout << "Original double value: " << floating_point << std::endl;
    int int_from_double = floating_point; // Fractional part is truncated
    std::cout << "Value after implicit narrowing double to int: " << int_from_double << std::endl;
}

int main() {
    demonstrate_narrowing();
    return 0;
}

// Mitigation Strategy:
// To prevent issues from implicit narrowing conversions:
// 1. Use Explicit Casts: If a narrowing conversion is intentional and understood,
//    use an explicit cast (e.g., `static_cast<int>(large_value)`). This makes
//    the intent clear and silences compiler warnings.
// 2. Compiler Warnings: Enable and heed compiler warnings related to narrowing
//    conversions (e.g., GCC/Clang with `-Wconversion` or `-Wnarrowing` as part of
//    `-Wall` or `-Wextra`). C++11's uniform initialization (`{}`) also helps by
//    disallowing most narrowing conversions.
//    Example: `int narrow_val{large_value};` // Would likely cause a compiler error.
// 3. Range Checks: Before performing a narrowing conversion, check if the value
//    fits within the target type's range.
//    Example:
//    if (large_value >= std::numeric_limits<int>::min() && large_value <= std::numeric_limits<int>::max()) {
//        narrow_val = static_cast<int>(large_value);
//    } else { /* Handle error: value out of range */ }
// 4. Choose Appropriate Data Types: Use data types that are large enough to hold
//    all expected values throughout their lifetime to avoid the need for narrowing.
// 5. Static Analysis: Utilize static analysis tools that can detect potentially
//    unsafe narrowing conversions.
// 6. List Initialization (C++11): Prefer list initialization (using `{}`) as it
//    disallows narrowing conversions that could lead to data loss, making them
//    compile-time errors.
//    Example: `int x = {some_long_long}; // Error if some_long_long doesn't fit in int`
