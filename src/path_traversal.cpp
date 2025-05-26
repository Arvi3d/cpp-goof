/*
A path traversal vulnerability occurs when user input is used to construct file paths without proper validation, allowing attackers to access files outside the intended directory. 
*/

#include <fstream>
#include <iostream>
#include <string>

void readFile(const std::string& baseDir, const std::string& userInput) {
    std::string fullPath = baseDir + userInput; // Unsafe concatenation
    std::ifstream file(fullPath);
    
    if (file.is_open()) {
        std::cout << "File content:\n" << file.rdbuf() << std::endl;
    } else {
        std::cerr << "Failed to open file." << std::endl;
    }
}

int main() {
    std::string baseDir = "/var/www/app/static/"; // Intended directory
    std::string filename;
    std::cout << "Enter filename: ";
    std::getline(std::cin, filename);

    readFile(baseDir, filename);
    return 0;
}

/*
Exploitation:
If the user enters `../../etc/passwd`, the resolved path becomes:
`/var/www/app/static/../../etc/passwd -> /var/www/etc/passwd`, which can lead to unauthorized access to sensitive files.

Mitigation Strategies:
Always validate user input against allowlists.
Use modern path resolution libraries instead of string concatenation.
Restrict file system permissions for the application.
*/