// Summary: Format String Vulnerability
// A format string vulnerability occurs when user-controlled input is used
// directly as the format string argument in functions like `printf`, `sprintf`,
// `fprintf`, etc. (or their C++ iostream equivalents if misused, though less common).
// Attackers can supply malicious format specifiers (e.g., %x, %s, %n) to read
// from or write to arbitrary memory locations, view stack contents, or cause
// a crash. The `%n` specifier is particularly dangerous as it writes the number
// of bytes written so far to an address specified by a pointer on the stack,
// enabling arbitrary memory writes.

#include <iostream>
#include <cstdio> // For printf, snprintf (C-style functions)
#include <string> // For strcspn
#include <cstring> // Required for strcspn if <string> doesn't pull it in on all compilers
#include "utils/format_string.h" // Include the library header

int main() {
    char user_buffer[100];
    std::cout << "Enter a string to print (try '%x %x %x %s %n' or similar): ";
    // Using fgets to prevent buffer overflow on user_buffer, but not the format string issue
    if (fgets(user_buffer, sizeof(user_buffer), stdin)) {
        // Remove newline character if present
        user_buffer[strcspn(user_buffer, "\n")] = 0;
        special_printf(user_buffer);
    }
    std::cout << "After vulnerable_printf. If %n was used, memory might be corrupted." << std::endl;
    return 0;
}

// Mitigation Strategy:
// To prevent format string vulnerabilities:
// 1. Always Use a Static Format String: When calling functions like `printf`,
//    provide a constant format string as the first argument. User input should
//    be passed as subsequent arguments.
//    Correct: `printf("%s", user_input);`
//    Incorrect: `printf(user_input);`
// 2. Use `iostream` Safely in C++: C++ iostreams (`std::cout`, `std::cerr`) are
//    generally safer as they don't interpret their input as format strings in
//    the same way `printf` does. However, ensure that if you are building
//    output that might later be passed to a C-style format function, it's handled correctly.
// 3. Compiler Warnings/Flags: Modern compilers often provide warnings for
//    potential format string vulnerabilities (e.g., GCC/Clang with `-Wformat`,
//    `-Wformat-security`, `-Wformat-nonliteral`). Enable and heed these warnings.
//    Some compilers might even treat these as errors by default or with flags like `-Werror=format-security`.
// 4. Static Analysis (SAST): Use SAST tools that are specifically designed to
//    detect format string bugs.
// 5. Disable `%n` if Possible: Some systems or libraries might offer ways to
//    disable the `%n` format specifier if it's not needed, though this is not
//    a universal solution.
// 6. Input Validation (Limited Effectiveness): While validating input can help
//    against some attacks, it's very difficult to create a foolproof blocklist
//    for all malicious format specifiers. Prioritize static format strings.
