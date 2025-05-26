// Summary: Double Free (Direct)
// A double free vulnerability occurs when `delete` (or `free` in C) is called
// more than once on the same memory address with no intervening reallocation.
// This corrupts the memory allocator's internal data structures.
// The consequences are undefined behavior, which can range from an immediate
// program crash to exploitable conditions. An attacker might be able to
// control the corrupted heap metadata to write arbitrary values to arbitrary
// memory locations, potentially leading to remote code execution. This is a
// critical memory corruption vulnerability.

#include <iostream>

void demonstrate_double_free() {
    int* ptr = new int(10);
    std::cout << "Allocated memory at: " << ptr << " with value: " << *ptr << std::endl;
    delete ptr; // First free
    std::cout << "Memory freed once." << std::endl;
    // ptr = nullptr; // Forgetting to nullify makes double free more likely
    delete ptr; // Second free on the same address: Undefined Behavior!
    std::cout << "Attempted to free memory twice. Behavior is undefined." << std::endl;
}

int main() {
    demonstrate_double_free();
    return 0;
}

// Mitigation Strategy:
// To prevent direct double free vulnerabilities:
// 1. Set Pointer to `nullptr` After Free: Immediately after deallocating
//    memory with `delete` or `free()`, set the pointer to `nullptr`.
//    `delete nullptr;` is a safe no-op, preventing accidental double free.
//    Example: `delete ptr; ptr = nullptr;`
// 2. Strict Ownership Semantics: Ensure that for any dynamically allocated
//    memory, there is a single, clear owner responsible for its deallocation.
//    Avoid scenarios where multiple parts of the code might attempt to free
//    the same memory.
// 3. Use Smart Pointers: Employ C++ smart pointers (`std::unique_ptr`,
//    `std::shared_ptr`). They automate memory management and significantly
//    reduce the risk of double frees and other memory-related errors.
//    `std::unique_ptr` ensures exclusive ownership and deallocation.
//    `std::shared_ptr` uses reference counting for deallocation.
// 4. Avoid Raw Pointers for Owned Memory: Whenever possible, avoid using raw
//    pointers (`Type*`) to manage the lifetime of dynamically allocated memory.
//    Prefer smart pointers or standard library containers.
// 5. Code Reviews: Carefully review code sections that perform manual memory
//    management.
// 6. Dynamic Analysis Tools: Use tools like AddressSanitizer (ASan), Valgrind,
//    or other memory debuggers during development and testing. They can often
//    detect double free errors at runtime.
// 7. Encapsulation: Encapsulate memory management logic within classes.
//    The class destructor can handle deallocation, reducing the chances of
//    errors in client code.
