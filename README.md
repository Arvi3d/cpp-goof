# cpp-goof
Purposely vulnerable repository in C/C++ (testing purpose)

Folder `src` contains the source code of the repository with multiple vulnerabilities.
Each file contains an explanation, example, and mitigation strategy.

Full list of found vulnerabilities:
 - [Snyk Code](https://app.eu.snyk.io/org/code/project/944d1d2c-20a4-4890-9287-eb06f4ef5fbe)
 - [Clang Static Analyzer](csa-results/scan-build-2025-06-11-09-33-38-331106-oufkiuvc/index.html)

## Issue comparison

Some issues are found by Snyk, some by Clang Static Analyzer and few by both.
There are also some vulnerabilities that are not detected by either tool or detected by mistake. 

| Issue                                  | Snyk | CSA |
| :------------------------------------- | :--- | :-- |
| [Command Injection](src/command_injection.cpp) | [Yes](https://app.eu.snyk.io/org/code/project/944d1d2c-20a4-4890-9287-eb06f4ef5fbe#issue-95f9f6b6-701b-49b0-91ee-d19ea59abc90) | No |
| [Path Traversal](src/path_traversal.cpp) | [Yes](https://app.eu.snyk.io/org/code/project/944d1d2c-20a4-4890-9287-eb06f4ef5fbe#issue-a5188080-d3e9-4e73-946a-dcaae41d4774) | No |
| [SQL Injection](src/sql_injection.cpp) | [Yes](https://app.eu.snyk.io/org/code/project/944d1d2c-20a4-4890-9287-eb06f4ef5fbe#issue-1b71a9f5-cb1a-4d3a-b4eb-48edef431ff1) | No |
| [Format String](src/format_string.cpp) | [Yes](https://app.eu.snyk.io/org/code/project/944d1d2c-20a4-4890-9287-eb06f4ef5fbe#issue-7f944ac6-4256-4add-a971-d5b7c420f7ec) | No |
| [Buffer Overflow](src/buffer_overflow.cpp) | No | [Yes](csa-results/scan-build-2025-06-11-09-33-38-331106-oufkiuvc/report-fbfcd0.html) |
| [Use After Free](src/dangling_pointer.cpp) | [Yes](https://app.eu.snyk.io/org/code/project/944d1d2c-20a4-4890-9287-eb06f4ef5fbe#issue-95da6c6e-845d-493a-80ec-d076733cf4d0) | [Yes](csa-results/scan-build-2025-06-11-09-33-38-331106-oufkiuvc/report-ce589f.html) |
| [Double Free (Aliased Ptr)](src/double_free_aliased_pointer.cpp) | No | No |
| [Double Free (Direct)](src/double_free_direct.cpp) | [Yes](https://app.eu.snyk.io/org/code/project/944d1d2c-20a4-4890-9287-eb06f4ef5fbe#issue-19998ea9-6274-4e9f-8b8c-9c14d21540af) | [Yes](csa-results/scan-build-2025-06-11-09-33-38-331106-oufkiuvc/report-0e40a0.html) |
| [Double Free (Function)](src/double_free_function.cpp) | No | [Yes](csa-results/scan-build-2025-06-11-09-33-38-331106-oufkiuvc/report-48b029.html) |
| [Memory Leak (Delete)](src/memory_leak_delete.cpp) | [Yes](https://app.eu.snyk.io/org/code/project/944d1d2c-20a4-4890-9287-eb06f4ef5fbe#issue-a1627315-4627-4460-bbe0-873ba29b8185) | [Yes](csa-results/scan-build-2025-06-11-09-33-38-331106-oufkiuvc/report-6ca886.html) |
| [Memory Leak (Destructor)](src/memory_leak_destructor.cpp) | No | [Yes](csa-results/scan-build-2025-06-11-09-33-38-331106-oufkiuvc/report-c26b0c.html) |
| [Memory Leak (Loop)](src/memory_leak_loop.cpp) | [Yes](https://app.eu.snyk.io/org/code/project/944d1d2c-20a4-4890-9287-eb06f4ef5fbe#issue-9c1df944-38c9-4948-bfe1-ae3ab0e499ab) | No |
| [Null Pointer Dereference](src/null_pointer_dereference.cpp) | [Yes](https://app.eu.snyk.io/org/code/project/944d1d2c-20a4-4890-9287-eb06f4ef5fbe#issue-fe6de715-cbc4-4703-b347-646a3686912b) | No |
| [Resource Leak (File)](src/resource_leak_file.cpp) | No | No |
| [Resource Leak (Socket)](src/resource_leak_socket.cpp) | No | No |
| [Concurrency Atomicity Violation](src/concurrency_atomicity_violation.cpp) | No | No |
| [Concurrency Deadlock](src/concurrency_deadlock.cpp) | No | No |
| [Concurrency Race Condition](src/concurrency_race_condition.cpp) | No | No |
| [Cryptography ECB Mode](src/cryptography_ecb_mode.cpp) | No | No |
| [Cryptography Hardcoded IV](src/cryptography_hardcoded_iv.cpp) | [Yes](https://app.eu.snyk.io/org/code/project/944d1d2c-20a4-4890-9287-eb06f4ef5fbe#issue-2fad2398-6ddd-4360-bb85-550c5526396b) | No |
| [Division by Zero (Double)](src/division_zero_double.cpp) | No | No |
| [Division by Zero (Int)](src/division_zero_int.cpp) | [Yes](https://app.eu.snyk.io/org/code/project/944d1d2c-20a4-4890-9287-eb06f4ef5fbe#issue-4aff60da-5b26-4f9f-9c9d-780c33cc9e76) | [Yes](csa-results/scan-build-2025-06-11-09-33-38-331106-oufkiuvc/report-4726a5.html) |
| [Integer Overflow (Signed)](src/integer_overflow_signed.cpp) | No | No |
| [Integer Overflow (Unsigned)](src/integer_overflow_unsigned.cpp) | No | No |
| [Uninitialized Variable](src/uninitialized_variable.cpp) | No | No |
| [Type Conv. (Narrowing)](src/incorrect_typecon_narrowing.cpp) | No | No |
| [Type Conv. (Pointer)](src/incorrect_typecon_pointer.cpp) | No | No |
| [Type Conv. (Signed)](src/incorrect_typecon_signed.cpp) | No | No |
| [Type Conv. (Unsafe C)](src/incorrect_typecon_unsafe_c.cpp) | No | No |


## Path Sensitive flow analysis

Unrelated to specific vulnerabilities, SAST engine must be able to detect path sensitive flow analysis. It means, that it takes into account the order of execution of instructions together with all conditions and loops.

| Issue | Snyk | CSA |
| :--------------------------- | :--- | :-- |
| [Use After Free - True positive](src/dangling_pointer_path_sensitive.cpp) | [Yes](https://app.eu.snyk.io/org/code/project/944d1d2c-20a4-4890-9287-eb06f4ef5fbe#issue-24b6cace-4b3b-4a2b-8e17-5666f9298d1c) | No |
| [Use After Free - False positive](src/dangling_pointer_path_sensitive.cpp) | [Yes](https://app.eu.snyk.io/org/code/project/944d1d2c-20a4-4890-9287-eb06f4ef5fbe#issue-f7071dca-c8c2-455c-b7c1-723f370093b5) | No |
| [Null Pointer Deref. - False positive](src/null_pointer_dereference_path_sensitive.cpp) | No | No |
| [Uninitialized Variable - False positive](src/unitialized_variable_path_sensitive.cpp) | No | No |


## Inter Translation Unit scanning capabilities

When application composed from multiple translation units, SAST engine must be able to detect vulnerabilities that span across them. A function can be defined in a separately build library and used in the main application.

| Issue | Snyk | CSA |
| :--------------------------- | :--- | :-- |
| [Format String](src/unitialized_variable_path_sensitive.cpp) | [Yes](https://app.eu.snyk.io/org/code/project/944d1d2c-20a4-4890-9287-eb06f4ef5fbe#issue-86f492e1-db1d-4dca-833a-836654ec23e4) | No |
| [Division by zero (integers)](src/division_zero_int_using_library.cpp) | No | No |
