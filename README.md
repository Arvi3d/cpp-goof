# cpp-goof
Purposely vulnerable repository in C/C++ (testing purpose)

Folder `src` contains the source code of the repository with multiple vulnerabilities.
Each file contains an explanation, example, and mitigation strategy.

Some vulnerabilities are found by Snyk, some by Clang Static Analyzer and few by both.
There are also some vulnerabilities that are not detected by either tool or detected by mistake. 

## Vulnerability Summary Table

| Issue                                  | FS  | Snyk | CSA |
| :------------------------------------- | :-- | :--- | :-- |
| [Buffer Overflow](src/buffer_overflow.cpp) | No | No | Yes |
| [Command Injection](src/command_injection.cpp) | No | Yes | No |
| [Concurrency Atomicity Violation](src/concurrency_atomicity_violation.cpp) | No | No | No |
| [Concurrency Deadlock](src/concurrency_deadlock.cpp) | No | No | No |
| [Concurrency Race Condition](src/concurrency_race_condition.cpp) | No | No | No |
| [Cryptography ECB Mode](src/cryptography_ecb_mode.cpp) | No | No | No |
| [Cryptography Hardcoded IV](src/cryptography_hardcoded_iv.cpp) | No | No | No |
| [Dangling Pointer](src/dangling_pointer.cpp) | No | Yes | Yes |
| [Dangling Pointer (Path Sens.) - True](src/dangling_pointer_path_sensitive.cpp) | No | Yes | No |
| [Dangling Pointer (Path Sens.) - False](src/dangling_pointer_path_sensitive.cpp) | Yes | Yes | No |
| [Division by Zero (Double)](src/division_zero_double.cpp) | No | No | No |
| [Division by Zero (Int)](src/division_zero_int.cpp) | No | Yes | Yes |
| [Double Free (Aliased Ptr)](src/double_free_aliased_pointer.cpp) | No | No | No |
| [Double Free (Direct)](src/double_free_direct.cpp) | No | Yes | Yes |
| [Double Free (Function)](src/double_free_function.cpp) | No | No | Yes |
| [Format String](src/format_string.cpp) | No | Yes | No |
| [Type Conv. (Narrowing)](src/incorrect_typecon_narrowing.cpp) | No | No | No |
| [Type Conv. (Pointer)](src/incorrect_typecon_pointer.cpp) | No | No | No |
| [Type Conv. (Signed)](src/incorrect_typecon_signed.cpp) | No | No | No |
| [Type Conv. (Unsafe C)](src/incorrect_typecon_unsafe_c.cpp) | No | No | No |
| [Int. Overflow (Signed)](src/integer_overflow_signed.cpp) | No | No | No |
| [Int. Overflow (Unsigned)](src/integer_overflow_unsigned.cpp) | No | No | No |
| [Memory Leak (Delete)](src/memory_leak_delete.cpp) | No | Yes | Yes |
| [Memory Leak (Destructor)](src/memory_leak_destructor.cpp) | No | No | Yes |
| [Memory Leak (Loop)](src/memory_leak_loop.cpp) | No | Yes | No |
| [Null Ptr Dereference](src/null_pointer_dereference.cpp) | No | Yes | No |
| [Null Ptr Deref. (Path Sens.) - False](src/null_pointer_dereference_path_sensitive.cpp) | Yes | No | No |
| [Path Traversal](src/path_traversal.cpp) | No | Yes | No |
| [Resource Leak (File)](src/resource_leak_file.cpp) | No | No | No |
| [Resource Leak (Socket)](src/resource_leak_socket.cpp) | No | No | No |
| [SQL Injection](src/sql_injection.cpp) | No | Yes | No |
| [Uninitialized Variable](src/uninitialized_variable.cpp) | No | No | No |
| [Uninit. Var. (Path Sens.) - False](src/unitialized_variable_path_sensitive.cpp) | Yes | No | No |

