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
