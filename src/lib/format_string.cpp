// Summary: This is special use case of format string vulnerability
// where the format string is not directly user input, but a library function
// the idea is to test scanning between Translation Units

#include <cstdio> // For printf, snprintf (C-style functions)

// A potentially vulnerable function using printf with user input as format string
void special_printf(const char* user_input) {
    printf(user_input); // Direct use of user_input as format string
    printf("\n");
}
