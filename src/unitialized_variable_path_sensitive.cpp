// Summary: Path-Sensitive Uninitialized Variable
// This example demonstrates a case where an uninitialized variable warning should not be reported
// because the variable is guaranteed to be initialized before use in all execution paths.

#include <iostream>
#include <cstdlib>

// Function to demonstrate path-sensitive initialization
void test() {
    int offset = 0;
    int value; // Variable declared but not immediately initialized
    int test = rand(); // Random value to control the path

    // The switch statement ensures value is initialized in all cases
    switch (test & 0x1) {
        case 0:
            value = 0;
            break;
        case 1:
            value = 1;
            break;
    }

    // At this point, value is guaranteed to be initialized (0 or 1)
    // because all paths through the switch statement initialize it
    offset += value; // This should NOT be flagged as uninitialized variable
}

int main() {
    test();
    std::cout << "Path-sensitive initialization example finished." << std::endl;
    return 0;
}

// Mitigation: While this example is safe, in general:
// 1. Always initialize variables at declaration when possible
// 2. Use assertions to verify initialization if unsure
// 3. Consider using std::optional for variables that might not have a value
// 4. Use RAII (Resource Acquisition Is Initialization) where applicable