// Summary: Dangling Pointer / Use After Free - Path sensitive flow
// A dangling pointer is a pointer that refers to a memory location that has
// been deallocated (freed). Attempting to dereference or use such a pointer
// results in a "Use After Free" error. This is undefined behavior and can
// lead to crashes, corrupted data, or security vulnerabilities. If the freed
// memory is later reallocated for a different purpose, using the dangling
// pointer can inadvertently access or modify unrelated data, potentially
// allowing an attacker to execute arbitrary code or cause other exploits.

#include <iostream>

void use_after_free() {
    int* ptr = new int(42); // Allocate memory
    std::cout << "Value before free: " << *ptr << std::endl;
    delete ptr;             // Deallocate memory, ptr is now dangling
    // ptr = nullptr;       // Good practice: Set ptr to nullptr after delete
    std::cout << "Attempting to use pointer after free..." << std::endl;

    switch (test & 0x1) {
        case 0:
            // This assignment constitutes a Use-After-Free.
            // This line is expected to be unreachable if the assumption about 'test'
            // (leading to (test & 0x1) != 0) holds, as detailed before the switch.
            *ptr = 10;
            break;
        case 1:
            *ptr = 100;             // Use After Free: Undefined Behavior!
            // The behavior here is unpredictable. It might crash, or it might seem to work
            // by corrupting memory that might be reused later.
            break;
    }
}

int main() {
    use_after_free();
    return 0;
}

// Mitigation Strategy:
// To prevent dangling pointers and Use After Free vulnerabilities:
// 1. Set Pointers to `nullptr` After Deallocation: Immediately after `delete`ing
//    a pointer, set it to `nullptr`. This makes subsequent checks for null
//    effective in preventing dereference of a dangling pointer.
//    Example: delete ptr; ptr = nullptr;
// 2. Avoid Multiple Pointers to the Same Raw Memory Without Clear Ownership:
//    If multiple pointers refer to the same memory managed by `new`/`delete`,
//    ensure only one is responsible for deallocation, and others are not used
//    after deallocation.
// 3. Use Smart Pointers: `std::unique_ptr` enforces exclusive ownership,
//    preventing dangling pointers by automatically managing memory and nullifying
//    the pointer on move. `std::shared_ptr` uses reference counting; memory is
//    freed only when the last `shared_ptr` to it is destroyed. `std::weak_ptr`
//    can be used to observe a `shared_ptr`-managed object without affecting its
//    lifetime, and it can be checked (e.g., via `lock()`) before use.
// 4. Be Cautious with Pointers to Stack Variables: Do not return pointers or
//    references to local (stack-allocated) variables from functions, as they
//    become dangling once the function exits.
// 5. Code Reviews and Static/Dynamic Analysis: Use static analysis tools (SAST)
//    and dynamic analysis tools (DAST, e.g., AddressSanitizer - ASan) to detect
//    Use After Free issues. Thorough code reviews are also crucial.
// 6. Object Lifetimes: Clearly define and manage the lifetimes of objects,
//    especially when raw pointers are involved.
