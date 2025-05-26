// Summary: Command Injection
// Command injection vulnerabilities occur when an application incorporates
// untrusted user input into a command that is then executed by the system's
// command-line interpreter. If the input is not properly sanitized or validated,
// an attacker can inject arbitrary commands, potentially leading to unauthorized
// system access, data breaches, or denial of service. This is a critical
// vulnerability, especially in applications that use system calls to interact
// with the underlying operating system based on user-provided data.

#include <iostream>
#include <string>
#include <cstdlib> // For system()

// Vulnerable function that constructs and executes a system command
void execute_ping(const std::string& host) {
    // Constructing the command string by concatenating user input.
    // Example of vulnerable input: "8.8.8.8; ls -la" or "8.8.8.8 && rm -rf /"
    std::string command = "ping -c 1 " + host;
    std::cout << "Executing command: " << command << std::endl;

    // The system() call executes the command string via the system's shell.
    // This is highly dangerous if 'host' contains malicious commands.
    int result = system(command.c_str());

    if (result == 0) {
        std::cout << "Ping successful." << std::endl;
    } else {
        std::cout << "Ping failed or command execution error." << std::endl;
    }
}

int main() {
    std::string userInput;
    std::cout << "Enter a hostname or IP address to ping: ";
    std::getline(std::cin, userInput); // Get user input

    execute_ping(userInput);
    return 0;
}

// Mitigation Strategy:
// To prevent command injection vulnerabilities:
// 1. Avoid `system()` with User Input: The safest approach is to avoid
//    calling `system()` or similar shell-invoking functions with any data
//    derived from user input.
// 2. Use Platform-Specific APIs: If system interaction is necessary, use
//    safer, platform-specific APIs that execute commands directly without
//    involving a shell (e.g., `CreateProcess` on Windows, `exec` family
//    functions like `execve` on POSIX systems). These functions typically
//    take arguments as a list, preventing the shell from interpreting them.
// 3. Input Sanitization/Validation (Less Secure): If using shell commands is
//    unavoidable, rigorously sanitize and validate all user input. This involves:
//    a. Allow-listing: Only permit known-good characters or patterns.
//    b. Escaping: Escape shell metacharacters (e.g., ;, |, &, $, <, >, `, !, etc.).
//       This is complex and error-prone; it's hard to get right for all shells.
// 4. Principle of Least Privilege: Run the application with the minimum
//    privileges necessary. This won't prevent injection but can limit its impact.
// 5. Parameterized Execution: When using APIs like `execve`, pass user input
//    as separate arguments to the command, not as part of the command string itself.
//    Example (POSIX):
//    `execlp("ping", "ping", "-c", "1", host.c_str(), (char *)NULL);`
//    Here, `host.c_str()` is treated as a single argument, not parsed by a shell.
// 6. Static Analysis (SAST) and Dynamic Analysis (DAST): Use security testing
//    tools to identify potential command injection flaws.
