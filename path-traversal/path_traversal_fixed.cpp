#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

void safeReadFile(const std::string& baseDir, const std::string& userInput) {
    try {
        // Resolve and canonicalize paths
        fs::path basePath = fs::canonical(baseDir);
        fs::path userPath = fs::canonical(baseDir / fs::path(userInput));

        // Verify the resolved path is within the base directory
        if (userPath.string().find(basePath.string()) != 0) {
            throw std::runtime_error("Invalid path!");
        }

        std::ifstream file(userPath);
        if (file.is_open()) {
            std::cout << "File content:\n" << file.rdbuf() << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    safeReadFile("/var/www/app/static/", "test.txt");
    return 0;
}

/*
Key Fixes:
	1.	Path Canonicalization: `std::filesystem::canonical` resolves `..` and `.` segments.
	2.	Validation: Checks if the resolved path starts with the base directory.
	3.	Exception Handling: Prevents crashes from invalid paths.
*/