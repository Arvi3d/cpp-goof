// Summary: Double Free (Aliased Pointer)
// This type of double free occurs when two or more pointers (aliases) refer
// to the same dynamically allocated memory, and `delete` is called on more
// than one of these aliases. Even if one alias is set to `nullptr` after its
// `delete` call, the other aliases still point to the (now invalid) memory
// region. Freeing through another alias leads to a double free, corrupting
// heap metadata and causing undefined behavior, similar to a direct double
// free. This can lead to crashes or be exploited for arbitrary code execution.

#include <iostream>

void demonstrate_aliased_double_free() {
    int* original_ptr = new int(20);
    int* alias_ptr = original_ptr; // alias_ptr now points to the same memory

    std::cout << "Original ptr: " << original_ptr << ", Alias ptr: " << alias_ptr << std::endl;
    std::cout << "Value via original: " << *original_ptr << std::endl;

    delete original_ptr; // Free memory via original_ptr
    original_ptr = nullptr; // Good practice for original_ptr
    std::cout << "Memory freed via original_ptr. original_ptr is now null." << std::endl;

    // alias_ptr is now a dangling pointer, but it still holds the old address.
    // delete alias_ptr; // Double Free: Undefined Behavior!
    // Uncommenting the line above would attempt to free the same memory again.
    std::cout << "alias_ptr still holds address: " << alias_ptr << ". Deleting it would be a double free." << std::endl;
    delete original_ptr; // Second delete would be the vulnerability.
}

int main() {
    demonstrate_aliased_double_free();
    return 0;
}

// Mitigation Strategy:
// To prevent double free via aliased pointers:
// 1. Establish Clear Ownership: The most crucial step. For any piece of
//    dynamically allocated memory, there should be one clear "owner" pointer
//    responsible for its deallocation. All other pointers to that memory
//    should be considered "observers" or "non-owning" and must not delete it.
// 2. Use Smart Pointers:
//    - `std::unique_ptr`: Enforces exclusive ownership. Aliasing in a way that
//      could lead to double `delete` is prevented by its design (it cannot be copied).
//    - `std::shared_ptr`: Allows multiple pointers to share ownership. The memory
//      is deallocated only when the last `shared_ptr` to it is destroyed. This
//      naturally handles aliasing for ownership purposes.
//    - `std::weak_ptr`: Can be used as a non-owning observer of memory managed
//      by `std::shared_ptr`.
// 3. Nullify All Aliases (Difficult and Error-Prone): If using raw pointers,
//    and if an alias might be used after a free, theoretically all aliases
//    should be nullified. This is often impractical to track and manage.
//    This highlights why clear ownership or smart pointers are preferred.
// 4. Avoid Passing Raw Pointers Around Casually: Be careful when functions
//    receive raw pointers. If a function stores a copy of a raw pointer, it
//    must be clear about its lifetime and ownership responsibilities.
// 5. Code Reviews and Analysis: Pay special attention to how raw pointers are
//    copied and used. Static and dynamic analysis tools (AddressSanitizer, Valgrind)
//    can help detect double free conditions.
