// Summary: Division by Zero (Floating-Point)
// Floating-point (e.g., double, float) division by zero is generally
// well-defined by the IEEE 754 standard. Unlike integer division by zero,
// it does not usually cause a program crash directly.
// - A non-zero number divided by 0.0 results in +/- infinity (`inf`).
// - 0.0 divided by 0.0 results in Not a Number (`NaN`).
// While not a crash, these special values can propagate through calculations,
// leading to unexpected or erroneous results if not explicitly handled.
// This can be a logical error or a vulnerability if these results affect
// critical decisions or outputs.

#include <iostream>
#include <cmath>   // For std::isinf, std::isnan
#include <limits>  // For std::numeric_limits

void demonstrate_fp_division_by_zero() {
    double numerator_pos = 10.0;
    double numerator_neg = -10.0;
    double numerator_zero = 0.0;
    double denominator_zero = 0.0;

    std::cout << "Demonstrating floating-point division by zero:" << std::endl;

    double result1 = numerator_pos / denominator_zero; // Results in +inf
    std::cout << numerator_pos << " / " << denominator_zero << " = " << result1 << std::endl;
    if (std::isinf(result1)) {
        std::cout << "  (Result is infinity)" << std::endl;
    }

    double result2 = numerator_neg / denominator_zero; // Results in -inf
    std::cout << numerator_neg << " / " << denominator_zero << " = " << result2 << std::endl;
    if (std::isinf(result2)) {
        std::cout << "  (Result is negative infinity)" << std::endl;
    }

    double result3 = numerator_zero / denominator_zero; // Results in NaN
    std::cout << numerator_zero << " / " << denominator_zero << " = " << result3 << std::endl;
    if (std::isnan(result3)) {
        std::cout << "  (Result is NaN - Not a Number)" << std::endl;
    }
    
    // Using these special values in further calculations can be problematic
    double further_calc = result1 + 100.0; // inf + 100 = inf
    std::cout << "inf + 100.0 = " << further_calc << std::endl;
    
    further_calc = result3 * 100.0; // NaN * 100 = NaN
    std::cout << "NaN * 100.0 = " << further_calc << std::endl;
}

int main() {
    demonstrate_fp_division_by_zero();
    return 0;
}

// Mitigation Strategy:
// While not a crash, unhandled `inf` or `NaN` can cause issues:
// 1. Check the Divisor: Before a floating-point division, check if the
//    divisor is zero (or very close to zero, considering precision issues).
//    Example:
//    if (std::abs(divisor) < std::numeric_limits<double>::epsilon()) {
//        // Handle as effectively zero: log, error, alternative value, etc.
//        std::cerr << "Error: Attempt to divide by zero or very small number." << std::endl;
//    } else {
//        result = numerator / divisor;
//    }
// 2. Check Results: After division or other floating-point operations, check
//    if the result is `inf` or `NaN` using `std::isinf()` and `std::isnan()`
//    (from `<cmath>`) and handle these cases appropriately.
// 3. Input Validation: If divisors come from external sources, validate them.
// 4. Floating-Point Environment: Advanced users can explore `<cfenv>` to check
//    floating-point status flags (like FE_DIVBYZERO), but this is complex and
//    often not necessary if direct checks are performed.
// 5. Understand IEEE 754 Behavior: Be aware of how `inf` and `NaN` propagate
//    in arithmetic operations (e.g., `inf + x = inf`, `NaN op x = NaN`).
