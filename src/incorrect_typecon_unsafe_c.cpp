// Summary: Incorrect Type Conversion (Unsafe C-Style Cast)
// C-style casts (`(new_type)expression` or `new_type(expression)`) are
// powerful but unsafe in C++ because they can perform various types of
// conversions (like `static_cast`, `const_cast`, or `reinterpret_cast`)
// without clearly indicating the programmer's intent. This can hide
// dangerous operations, such as casting between unrelated pointer types
// (effectively a `reinterpret_cast`), leading to undefined behavior,
// memory corruption, and crashes when the casted pointer is dereferenced.
// They offer no compile-time safety for many risky conversions.

#include <iostream>
#include <string>

struct Widget {
    int id;
    double weight;
};

struct Gadget {
    std::string name;
    int version;
};

void demonstrate_unsafe_c_style_cast() {
    Widget my_widget = {123, 45.67};
    std::cout << "Original Widget: id=" << my_widget.id << ", weight=" << my_widget.weight << std::endl;

    // Unsafe C-style cast from Widget* to Gadget*
    // This is equivalent to a reinterpret_cast in this context.
    Gadget* gadget_ptr = (Gadget*)&my_widget;

    std::cout << "Attempting to access Widget's memory as Gadget via C-style cast..." << std::endl;
    // Accessing members of gadget_ptr is undefined behavior because Widget and Gadget
    // are unrelated and have different memory layouts.
    try {
        // The behavior of the following lines is highly undefined.
        // Accessing gadget_ptr->name is particularly dangerous.
        // std::cout << "gadget_ptr->name (interpreted): " << gadget_ptr->name << std::endl;
        std::cout << "gadget_ptr->version (interpreted, raw memory access): " << gadget_ptr->version << std::endl;
        std::cout << "Note: Accessing gadget_ptr->name was commented out as it's very likely to crash." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception caught." << std::endl;
    }
}

int main() {
    demonstrate_unsafe_c_style_cast();
    return 0;
}

// Mitigation Strategy:
// To prevent issues from unsafe C-style casts:
// 1. Prefer C++-Style Casts: Use C++ specific cast operators (`static_cast`,
//    `dynamic_cast`, `reinterpret_cast`, `const_cast`). They make the
//    programmer's intent clearer and provide varying levels of compile-time
//    and run-time safety.
//    - `static_cast`: For related types (e.g., numeric conversions, pointer
//      up/downcasts in a known-safe hierarchy).
//    - `dynamic_cast`: For safe downcasting in polymorphic class hierarchies
//      (checks type at runtime).
//    - `reinterpret_cast`: For low-level, unsafe conversions between pointer
//      types or pointers and integers. Use with extreme caution and only when
//      absolutely necessary and the implications are fully understood.
//    - `const_cast`: To add or remove `const` or `volatile` qualifiers.
// 2. Avoid C-Style Casts: Make it a practice to avoid C-style casts in C++ code.
//    Their ability to perform different kinds of casts implicitly makes them
//    harder to review and more error-prone.
// 3. Understand Type Aliasing: Be aware of strict aliasing rules. Casting to an
//    unrelated type and then accessing its members often violates these rules,
//    leading to undefined behavior.
// 4. Compiler Warnings: Some compilers might offer warnings for certain uses of
//    C-style casts, or linters might flag them.
// 5. Code Reviews: Pay close attention to any C-style casts during code reviews
//    and question their necessity and safety.
