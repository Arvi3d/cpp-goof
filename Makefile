# Makefile for cpp-goof project
# Includes security testing with Snyk CLI and Clang Static Analyzer

# Compiler settings
CXX = g++
CXXFLAGS = -Wall -Wextra -g

# Source files
SRCS = src/buffer_overflow.cpp src/path_traversal.cpp src/sql_injection.cpp src/memory_leak_delete.cpp src/memory_leak_destructor.cpp src/memory_leak_loop.cpp src/resource_leak_file.cpp src/resource_leak_socket.cpp src/null_pointer_dereference.cpp src/dangling_pointer.cpp src/integer_overflow_signed.cpp src/integer_overflow_unsigned.cpp src/double_free_direct.cpp src/double_free_aliased_pointer.cpp src/double_free_function.cpp src/concurrency_race_condition.cpp src/concurrency_deadlock.cpp src/concurrency_atomicity_violation.cpp src/uninitialized_variable.cpp src/command_injection.cpp src/format_string.cpp src/incorrect_typecon_narrowing.cpp src/incorrect_typecon_signed.cpp src/incorrect_typecon_pointer.cpp src/incorrect_typecon_unsafe_c.cpp src/division_zero_int.cpp src/division_zero_double.cpp src/cryptography_hardcoded_iv.cpp src/cryptography_ecb_mode.cpp
OBJS = $(SRCS:.cpp=.o)
EXES = $(SRCS:.cpp=)

# Clang Static Analyzer settings
SCAN_BUILD = /opt/homebrew/opt/llvm/bin/scan-build
SCAN_BUILD_FLAGS = --status-bugs -enable-checker security,core,unix,deadcode,cplusplus -v -V

# Default target now points to CMake build
all: build-cmake

# Target for direct g++ compilation (kept for reference or specific use)
all-direct: $(EXES)

# Rule for building executables
%: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

# Clean target
clean:
	rm -f $(OBJS) $(EXES)
	rm -rf scan-build-results
	rm -rf build

# Snyk security testing section
.PHONY: snyk-test
snyk-test:
	@echo "Running Snyk code security tests..."
	@if [ -x "./snyk" ]; then \
		echo "Using local Snyk binary..."; \
		./snyk code test; \
	else \
		echo "Using system Snyk installation..."; \
		snyk code test; \
	fi

# Run all security tests
.PHONY: security-check
security-check: snyk-test clang-analyze
	@echo "All security checks completed."

# Install Clang Static Analyzer on macOS
.PHONY: install-clang-analyzer
install-clang-analyzer:
	@echo "Installing Clang Static Analyzer on macOS..."
	@if ! command -v brew &> /dev/null; then \
		echo "Homebrew not found. Installing Homebrew..."; \
		/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"; \
	fi
	brew update
	brew install llvm
	export PATH="/opt/homebrew/opt/llvm/bin:$PATH"
	@echo "Clang Static Analyzer installed successfully."
	@echo "Make sure LLVM tools are in your PATH by adding the following to your shell profile:"
	@echo "export PATH=\"/usr/local/opt/llvm/bin:\$PATH\""
	@echo "For Apple Silicon Macs, use: export PATH=\"/opt/homebrew/opt/llvm/bin:\$PATH\""

# Clang Static Analyzer section
.PHONY: clang-analyze
clang-analyze: install-clang-analyzer cmake-configure
	@echo "Running Clang Static Analyzer on CMake build..."
	mkdir -p scan-build-results
	rm -rf build

	cmake . -Bbuild -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
	analyze-build -o ./scan-build-results --cdb ./build/compile_commands.json

	@echo "Analysis complete. Results saved in scan-build-results directory."

# Install project dependencies (CMake, Conan) on macOS
.PHONY: install-deps
install-deps:
	@echo "Installing CMake on macOS..."
	@if ! command -v brew &> /dev/null; then \
		echo "Homebrew not found. Installing Homebrew..."; \
		/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"; \
	fi
	brew update
	brew install cmake
	brew install conan
	brew install pipx
	pipx install scan-build
	@echo "CMake and Conan installed successfully (or already present)."

# Install Snyk binary locally
.PHONY: install-snyk
install-snyk:
	@echo "Downloading Snyk CLI for macOS ARM64..."
	curl --compressed https://downloads.snyk.io/cli/stable/snyk-macos-arm64 -o snyk
	chmod +x ./snyk
	@echo "Snyk CLI installed successfully in the current directory."
	@echo "You can run Snyk using ./snyk instead of snyk in your commands."

# Conan install target
.PHONY: conan-install
conan-install: install-deps
	@echo "Installing Conan dependencies..."
	conan install . --output-folder=build --build=missing --settings=build_type=Debug # Or Release

# CMake configure-only target
.PHONY: cmake-configure
cmake-configure: conan-install
	@echo "Configuring with CMake..."
	mkdir -p build
	cd build && cmake .. -DCMAKE_TOOLCHAIN_FILE=build/Debug/generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug
	@echo "CMake configuration complete."

# CMake build target
.PHONY: build-cmake
build-cmake: cmake-configure
	@echo "Building with CMake..."
	cd build && cmake --build .
	@echo "CMake build complete. Executables are in the build/ directory."

# Clean CMake build artifacts
.PHONY: clean-cmake
clean-cmake:
	rm -rf build

# Help target
.PHONY: help
help:
	@echo "Available targets:"
	@echo "  all                  - Build all executables"
	@echo "  clean                - Remove all build artifacts"
	@echo "  snyk-test            - Run Snyk security tests"
	@echo "  clang-analyze        - Run Clang Static Analyzer"
	@echo "  security-check       - Run all security checks"
	@echo "  install-clang-analyzer - Install Clang Static Analyzer on macOS"
	@echo "  install-snyk         - Download and install Snyk CLI locally"
	@echo "  install-deps         - Install project dependencies (CMake, Conan) using Homebrew and pip"
	@echo "  conan-install        - Install dependencies using Conan"
	@echo "  build-cmake          - Build the project using CMake and Conan"
	@echo "  clean-cmake          - Remove CMake build artifacts"
