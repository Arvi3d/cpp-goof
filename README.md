# cpp-goof
Purposely vulnerable repository in C/C++ (testing purpose)

Folder `src` contains the source code of the repository with multiple vulnerabilities.
Each file contains an explanation, example, and mitigation strategy.

Some vulnerabilities are found by Snyk, some by Clang Static Analyzer and few by both.
There are also some vulnerabilities that are not detected by either tool or detected by mistake. 

## Vulnerability Summary Table

| Issue                                  | FS  | Snyk | CSA |
| :------------------------------------- | :-- | :--- | :-- |
| [Buffer Overflow](src/buffer_overflow.cpp) | No | No | [Yes](csa-results/scan-build-2025-06-10-17-35-52-388277-melysrtp/report-fbfcd0.html) |
| [Command Injection](src/command_injection.cpp) | No | [Yes](https://app.eu.snyk.io/org/code/project/944d1d2c-20a4-4890-9287-eb06f4ef5fbe#issue-95f9f6b6-701b-49b0-91ee-d19ea59abc90) | No |
| [Concurrency Atomicity Violation](src/concurrency_atomicity_violation.cpp) | No | No | No |
| [Concurrency Deadlock](src/concurrency_deadlock.cpp) | No | No | No |
| [Concurrency Race Condition](src/concurrency_race_condition.cpp) | No | No | No |
| [Cryptography ECB Mode](src/cryptography_ecb_mode.cpp) | No | No | No |
| [Cryptography Hardcoded IV](src/cryptography_hardcoded_iv.cpp) | No | [Yes](https://app.eu.snyk.io/org/code/project/944d1d2c-20a4-4890-9287-eb06f4ef5fbe#issue-2fad2398-6ddd-4360-bb85-550c5526396b) | No |
| [Use After Free](src/dangling_pointer.cpp) | No | [Yes](https://app.eu.snyk.io/org/code/project/944d1d2c-20a4-4890-9287-eb06f4ef5fbe#issue-95da6c6e-845d-493a-80ec-d076733cf4d0) | [Yes](csa-results/scan-build-2025-06-10-17-35-52-388277-melysrtp/report-ce589f.html) |
| [Use After Free (Path Sens.) - True](src/dangling_pointer_path_sensitive.cpp) | No | [Yes](https://app.eu.snyk.io/org/code/project/944d1d2c-20a4-4890-9287-eb06f4ef5fbe#issue-24b6cace-4b3b-4a2b-8e17-5666f9298d1c) | No |
| [Use After Free (Path Sens.) - False](src/dangling_pointer_path_sensitive.cpp) | Yes | [Yes](https://app.eu.snyk.io/org/code/project/944d1d2c-20a4-4890-9287-eb06f4ef5fbe#issue-f7071dca-c8c2-455c-b7c1-723f370093b5) | No |
| [Division by Zero (Double)](src/division_zero_double.cpp) | No | No | No |
| [Division by Zero (Int)](src/division_zero_int.cpp) | No | [Yes](https://app.eu.snyk.io/org/code/project/944d1d2c-20a4-4890-9287-eb06f4ef5fbe#issue-4aff60da-5b26-4f9f-9c9d-780c33cc9e76) | [Yes](csa-results/scan-build-2025-06-10-17-35-52-388277-melysrtp/report-4726a5.html) |
| [Double Free (Aliased Ptr)](src/double_free_aliased_pointer.cpp) | No | No | No |
| [Double Free (Direct)](src/double_free_direct.cpp) | No | [Yes](https://app.eu.snyk.io/org/code/project/944d1d2c-20a4-4890-9287-eb06f4ef5fbe#issue-19998ea9-6274-4e9f-8b8c-9c14d21540af) | [Yes](csa-results/scan-build-2025-06-10-17-35-52-388277-melysrtp/report-0e40a0.html) |
| [Double Free (Function)](src/double_free_function.cpp) | No | No | [Yes](csa-results/scan-build-2025-06-10-17-35-52-388277-melysrtp/report-48b029.html) |
| [Format String](src/format_string.cpp) | No | [Yes](https://app.eu.snyk.io/org/code/project/944d1d2c-20a4-4890-9287-eb06f4ef5fbe#issue-7f944ac6-4256-4add-a971-d5b7c420f7ec) | No |
| [Type Conv. (Narrowing)](src/incorrect_typecon_narrowing.cpp) | No | No | No |
| [Type Conv. (Pointer)](src/incorrect_typecon_pointer.cpp) | No | No | No |
| [Type Conv. (Signed)](src/incorrect_typecon_signed.cpp) | No | No | No |
| [Type Conv. (Unsafe C)](src/incorrect_typecon_unsafe_c.cpp) | No | No | No |
| [Int. Overflow (Signed)](src/integer_overflow_signed.cpp) | No | No | No |
| [Int. Overflow (Unsigned)](src/integer_overflow_unsigned.cpp) | No | No | No |
| [Memory Leak (Delete)](src/memory_leak_delete.cpp) | No | [Yes](https://app.eu.snyk.io/org/code/project/944d1d2c-20a4-4890-9287-eb06f4ef5fbe#issue-a1627315-4627-4460-bbe0-873ba29b8185) | [Yes](csa-results/scan-build-2025-06-10-17-35-52-388277-melysrtp/report-6ca886.html) |
| [Memory Leak (Destructor)](src/memory_leak_destructor.cpp) | No | No | [Yes](csa-results/scan-build-2025-06-10-17-35-52-388277-melysrtp/report-c26b0c.html) |
| [Memory Leak (Loop)](src/memory_leak_loop.cpp) | No | [Yes](https://app.eu.snyk.io/org/code/project/944d1d2c-20a4-4890-9287-eb06f4ef5fbe#issue-9c1df944-38c9-4948-bfe1-ae3ab0e499ab) | No |
| [Null Ptr Dereference](src/null_pointer_dereference.cpp) | No | [Yes](https://app.eu.snyk.io/org/code/project/944d1d2c-20a4-4890-9287-eb06f4ef5fbe#issue-fe6de715-cbc4-4703-b347-646a3686912b) | No |
| [Null Ptr Deref. (Path Sens.) - False](src/null_pointer_dereference_path_sensitive.cpp) | Yes | No | No |
| [Path Traversal](src/path_traversal.cpp) | No | [Yes](https://app.eu.snyk.io/org/code/project/944d1d2c-20a4-4890-9287-eb06f4ef5fbe#issue-a5188080-d3e9-4e73-946a-dcaae41d4774) | No |
| [Resource Leak (File)](src/resource_leak_file.cpp) | No | No | No |
| [Resource Leak (Socket)](src/resource_leak_socket.cpp) | No | No | No |
| [SQL Injection](src/sql_injection.cpp) | No | [Yes](https://app.eu.snyk.io/org/code/project/944d1d2c-20a4-4890-9287-eb06f4ef5fbe#issue-1b71a9f5-cb1a-4d3a-b4eb-48edef431ff1) | No |
| [Uninitialized Variable](src/uninitialized_variable.cpp) | No | No | No |
| [Uninit. Var. (Path Sens.) - False](src/unitialized_variable_path_sensitive.cpp) | Yes | No | No |

