# cpp-goof
Purposely vulnerable repository in C/C++ (testing purpose)

Folder `src` contains the source code of the repository with multiple vulnerabilities.
Each file contains an explanation, example, and mitigation strategy.

Some vulnerabilities are found by Snyk, some by Clang Static Analyzer and few by both.
There are also some vulnerabilities that are not detected by either tool or detected by mistake. 

## Vulnerability Summary Table

| File                                      | Issue                                  | FS  | Snyk | CSA |
| :---------------------------------------- | :------------------------------------- | :-- | :--- | :-- |
| `buffer_overflow.cpp`                     | Buffer Overflow                        | No  | No   | Yes |
| `command_injection.cpp`                   | Command Injection                      | No  | Yes  | No  |
| `concurrency_atomicity_violation.cpp`     | Concurrency Atomicity Violation        | No  | No   | No  |
| `concurrency_deadlock.cpp`                | Concurrency Deadlock                   | No  | No   | No  |
| `concurrency_race_condition.cpp`          | Concurrency Race Condition             | No  | No   | No  |
| `cryptography_ecb_mode.cpp`               | Cryptography ECB Mode                  | No  | No   | No  |
| `cryptography_hardcoded_iv.cpp`           | Cryptography Hardcoded IV              | No  | No   | No  |
| `dangling_pointer.cpp`                    | Dangling Pointer                       | No  | Yes  | Yes |
| `dangling_pointer_path_sensitive.cpp`     | Dangling Pointer (Path Sens.) - True   | No  | Yes  | No  |
| `dangling_pointer_path_sensitive.cpp`     | Dangling Pointer (Path Sens.) - False  | Yes | Yes  | No  |
| `division_zero_double.cpp`                | Division by Zero (Double)              | No  | No   | No  |
| `division_zero_int.cpp`                   | Division by Zero (Int)                 | No  | Yes  | Yes |
| `double_free_aliased_pointer.cpp`         | Double Free (Aliased Ptr)              | No  | No   | No  |
| `double_free_direct.cpp`                  | Double Free (Direct)                   | No  | Yes  | Yes |
| `double_free_function.cpp`                | Double Free (Function)                 | No  | No   | Yes |
| `format_string.cpp`                       | Format String                          | No  | Yes  | No  |
| `incorrect_typecon_narrowing.cpp`         | Type Conv. (Narrowing)                 | No  | No   | No  |
| `incorrect_typecon_pointer.cpp`           | Type Conv. (Pointer)                   | No  | No   | No  |
| `incorrect_typecon_signed.cpp`            | Type Conv. (Signed)                    | No  | No   | No  |
| `incorrect_typecon_unsafe_c.cpp`          | Type Conv. (Unsafe C)                  | No  | No   | No  |
| `integer_overflow_signed.cpp`             | Int. Overflow (Signed)                 | No  | No   | No  |
| `integer_overflow_unsigned.cpp`           | Int. Overflow (Unsigned)               | No  | No   | No  |
| `memory_leak_delete.cpp`                  | Memory Leak (Delete)                   | No  | Yes  | Yes |
| `memory_leak_destructor.cpp`              | Memory Leak (Destructor)               | No  | No   | Yes |
| `memory_leak_loop.cpp`                    | Memory Leak (Loop)                     | No  | Yes  | No  |
| `null_pointer_dereference.cpp`            | Null Ptr Dereference                   | No  | Yes  | No  |
| `null_pointer_dereference_path_sensitive.cpp` | Null Ptr Deref. (Path Sens.) - False | Yes | No | No  |
| `path_traversal.cpp`                      | Path Traversal                         | No  | Yes  | No  |
| `resource_leak_file.cpp`                  | Resource Leak (File)                   | No  | No   | No  |
| `resource_leak_socket.cpp`                | Resource Leak (Socket)                 | No  | No   | No  |
| `sql_injection.cpp`                       | SQL Injection                          | No  | Yes  | No  |
| `uninitialized_variable.cpp`              | Uninitialized Variable                 | No  | No   | No  |
| `unitialized_variable_path_sensitive.cpp` | Uninit. Var. (Path Sens.) - False      | Yes | No  | No  |

