// Summary: Memory Leak due to Missing Destructor
// A common C++ pitfall is a memory leak occurring when a class allocates
// memory dynamically (e.g., using 'new') but lacks a destructor, or its
// destructor fails to deallocate this memory. When an object of such a
// class is destroyed, the memory it acquired remains allocated but
// unreachable, leading to a leak. This is particularly problematic for
// objects created and destroyed frequently, or for long-running applications,
// as cumulative leaks can exhaust system memory and degrade performance.

class LeakyResource {
public:
    int* data;
    LeakyResource() {
        data = new int[100]; // Allocate memory
        // No destructor to free 'data'
    }
};

int main() {
    LeakyResource lr; // lr.data is leaked when lr goes out of scope
    return 0;
}

// Mitigation Strategy:
// To prevent memory leaks from missing or incorrect destructors:
// 1. Implement a Destructor: If your class allocates resources (like memory
//    with 'new' or 'new[]'), it MUST have a destructor that releases these
//    resources (using 'delete' or 'delete[]' respectively).
// 2. Follow the Rule of Three/Five/Zero:
//    - Rule of Three: If you define any of a destructor, copy constructor,
//      or copy assignment operator, you should probably define all three.
//    - Rule of Five (C++11 onwards): Extends the Rule of Three to include
//      move constructor and move assignment operator.
//    - Rule of Zero: Prefer classes that manage no resources directly.
//      Instead, use resource-managing classes from the standard library
//      (e.g., std::vector, std::string) or smart pointers.
// 3. Use Smart Pointers: Employ `std::unique_ptr` for exclusive ownership
//    or `std::shared_ptr` for shared ownership. These automatically manage
//    the lifetime of dynamically allocated objects, deallocating memory
//    when the smart pointer goes out of scope. This often aligns with the
//    Rule of Zero.
// 4. Code Reviews & Static Analysis: Regularly review code for resource
//    management issues. Use static analysis tools that can detect
//    potential memory leaks.
// 5. Memory Profiling Tools: Utilize tools like Valgrind (on Linux/macOS)
//    or Visual Studio's debugger (on Windows) to detect memory leaks
//    during runtime.
