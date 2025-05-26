// Summary: Double Free (Across Functions)
// This occurs when dynamically allocated memory is freed in one function,
// but a pointer to that same memory (held by the caller or another function)
// is used to free it again. Lack of clear ownership or communication about
// which function is responsible for deallocation is a common cause.
// This leads to heap corruption and undefined behavior, potentially
// exploitable for arbitrary code execution.

#include <iostream>

// Function that frees the passed pointer
void helper_free_memory(int* ptr_param) {
    std::cout << "Helper function freeing memory at: " << ptr_param << std::endl;
    delete ptr_param;
    // ptr_param is now dangling within this function's scope.
    // The original pointer in the calling function is also now dangling.
}

int main() {
    int* data_ptr = new int(77);
    std::cout << "Allocated in main: " << data_ptr << " value: " << *data_ptr << std::endl;
    helper_free_memory(data_ptr); // First free happens here
    // data_ptr in main is now a dangling pointer.
    delete data_ptr; // Second free: Double Free! Undefined Behavior.
    std::cout << "Attempted second free in main. Behavior is undefined." << std::endl;
    return 0;
}

// Mitigation Strategy:
// To prevent double free across functions:
// 1. Establish Clear Ownership: Define which part of the code (which function,
//    object, or scope) "owns" the dynamically allocated memory and is
//    responsible for its deallocation.
// 2. Transfer Ownership Explicitly with Smart Pointers: Use `std::unique_ptr`
//    to transfer ownership. The function receiving the `std::unique_ptr`
//    (e.g., by `std::move`) becomes the new owner.
// 3. Use `std::shared_ptr` for Shared Ownership: If multiple parts of the code
//    need to share access and lifetime management, use `std::shared_ptr`.
// 4. Nullify Pointers (Limited Effectiveness): If a function frees a pointer
//    passed by raw pointer, it cannot nullify the caller's pointer. The caller
//    must do it. If passing by reference to pointer (`int*&`), the function can nullify:
//    `void helper_free(int*& p) { delete p; p = nullptr; }`.
// 5. Documentation and API Design: Clearly document which functions take
//    ownership of raw pointers and which ones merely observe them.
// 6. Avoid Raw Pointers for Ownership Transfer: Prefer smart pointers for any
//    scenario involving transfer or sharing of ownership of dynamic memory.
// 7. Static and Dynamic Analysis: Use tools like AddressSanitizer (ASan) and
//    Valgrind to detect such issues during runtime.
