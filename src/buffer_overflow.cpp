#include <cstring>

int main() {
  char buffer[10]; 
  strcpy(buffer, "This string is too long!"); // Causes overflow
  return 0;
}
