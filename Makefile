# Makefile for cpp-goof project
# Includes security testing with Snyk CLI and Clang Static Analyzer

# Compiler settings
CXX = g++
CXXFLAGS = -Wall -Wextra -g

# Source files
SRCS = buffer_overflow.cpp path_traversal_vuln.cpp sql_injection_vuln.cpp
OBJS = $(SRCS:.cpp=.o)
EXES = $(SRCS:.cpp=)

# Clang Static Analyzer settings
SCAN_BUILD = scan-build
SCAN_BUILD_FLAGS = -enable-checker security,core,unix,deadcode,cplusplus -v -V

# Default target
all: $(EXES)

# Rule for building executables
%: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

# Clean target
clean:
	rm -f $(OBJS) $(EXES)
	rm -rf scan-build-results

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

# Clang Static Analyzer section
.PHONY: clang-analyze
clang-analyze:
	@echo "Running Clang Static Analyzer..."
	mkdir -p scan-build-results
	$(SCAN_BUILD) $(SCAN_BUILD_FLAGS) -o scan-build-results $(CXX) $(CXXFLAGS) $(SRCS)
	@echo "Analysis complete. Results saved in scan-build-results directory."

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
	@echo "Clang Static Analyzer installed successfully."
	@echo "Make sure LLVM tools are in your PATH by adding the following to your shell profile:"
	@echo "export PATH=\"/usr/local/opt/llvm/bin:\$PATH\""
	@echo "For Apple Silicon Macs, use: export PATH=\"/opt/homebrew/opt/llvm/bin:\$PATH\""

# Install Snyk binary locally
.PHONY: install-snyk
install-snyk:
	@echo "Downloading Snyk CLI for macOS ARM64..."
	curl --compressed https://downloads.snyk.io/cli/stable/snyk-macos-arm64 -o snyk
	chmod +x ./snyk
	@echo "Snyk CLI installed successfully in the current directory."
	@echo "You can run Snyk using ./snyk instead of snyk in your commands."

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