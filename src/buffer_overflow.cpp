// Summary of Buffer Overflow:
// A buffer overflow is a vulnerability that occurs when a program writes data
// beyond the allocated boundary of a buffer. This overwrites adjacent memory,
// potentially corrupting data, causing a program crash, or, in more severe
// cases, allowing an attacker to execute arbitrary code. This issue is
// particularly prevalent in languages like C and C++ that offer direct memory
// manipulation without automatic bounds checking.


#include <cstring> // For strcpy
#include <iostream> // For std::cout

int main() {
    char dest_buffer[10];
    // Source string is explicitly an array.
    char source_string[] = "This string is definitely too long for the buffer"; 

    std::cout << "Attempting stack buffer overflow with strcpy from a char array variable..." << std::endl;
    // Vulnerable strcpy
    strcpy(dest_buffer, source_string);

    // Accessing dest_buffer[0] to see if it's still valid or if program crashed.
    std::cout << "First char of dest_buffer (if reachable): '" << dest_buffer[0] << "'" << std::endl;
    std::cout << "Program finished (or crashed before this)." << std::endl;
    
    return 0;
}

// Mitigation Strategies for Buffer Overflow:
// *   Use Safer Functions: Replace unsafe functions (like `strcpy`, `strcat`,
//     `sprintf`, `gets`, `scanf` with unbounded `%s`) with their bounded
//     counterparts (e.g., `strncpy`, `strncat`, `snprintf`, `fgets`). Always
//     ensure correct size calculations and null termination. For example:
//     `strncpy(buffer, user_input, sizeof(buffer) - 1); buffer[sizeof(buffer)-1] = '\0';`
// *   Input Validation: Rigorously validate the length and format of all
//     external input before it's used in buffer operations. Reject or truncate
//     oversized inputs.
// *   Compiler Protections: Enable and utilize compiler-provided security
//     features such as:
//     *   Stack Canaries (e.g., GCC/Clang: `-fstack-protector-all`, MSVC: `/GS`):
//         Detect stack smashing attacks.
//     *   Address Space Layout Randomization (ASLR): Makes it harder for
//         attackers to predict target addresses. (OS-level feature, ensure
//         executable is compatible).
//     *   Data Execution Prevention (DEP)/NX Bit: Prevents execution of code in
//         data segments. (OS-level feature, ensure executable is compatible).
