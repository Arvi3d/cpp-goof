// Summary: Concurrency Issue - Atomicity Violation
// An atomicity violation occurs when a sequence of operations that must
// appear as a single, indivisible (atomic) operation is interrupted by
// another thread. If other threads can observe or interact with the shared
// data in an intermediate state (after some operations in the sequence have
// completed but before others), it can lead to inconsistent data, incorrect
// program logic, and difficult-to-debug errors. The final outcome can
// become dependent on the unpredictable order of thread execution.

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>    // For mitigation example
#include <chrono>   // For std::this_thread::sleep_for
#include <cstdlib>  // For std::rand, std::srand
#include <ctime>    // For std::time

struct SharedResource {
    int valueA = 0;
    int valueB = 0;
    // Invariant: For this example, we might intend valueA and valueB to always be equal
    // after an "atomic" update.
};

SharedResource resource;
// std::mutex resource_mutex; // Uncomment for mitigation

// This function intends to set valueA and valueB to the same new_value.
// This operation should be atomic.
void update_resource_non_atomic(int new_value) {
    std::cout << "Thread " << std::this_thread::get_id() << ": updating resource to " << new_value << std::endl;
    resource.valueA = new_value;
    // Simulate some processing or potential for context switch
    std::this_thread::sleep_for(std::chrono::microseconds(10 + (std::rand() % 10)));
    resource.valueB = new_value;
    std::cout << "Thread " << std::this_thread::get_id() << ": finished updating resource." << std::endl;
}

// Reader thread to check for inconsistencies
void check_resource_consistency() {
    for (int i = 0; i < 5; ++i) {
        // For mitigation, lock here: std::lock_guard<std::mutex> lock(resource_mutex);
        int valA = resource.valueA;
        // Simulate a small delay or work
        std::this_thread::sleep_for(std::chrono::microseconds(5 + (std::rand() % 5)));
        int valB = resource.valueB;

        if (valA != valB) {
            std::cout << "ATOMCITY VIOLATION DETECTED by thread " << std::this_thread::get_id()
                      << "! valueA = " << valA << ", valueB = " << valB << std::endl;
        } else {
            std::cout << "Thread " << std::this_thread::get_id() << ": Consistent state: valueA = " << valA << ", valueB = " << valB << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(20)); // Check periodically
    }
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed for rand() used in sleep

    std::vector<std::thread> threads;
    threads.push_back(std::thread(update_resource_non_atomic, 100));
    threads.push_back(std::thread(check_resource_consistency));
    threads.push_back(std::thread(update_resource_non_atomic, 200));
    threads.push_back(std::thread(check_resource_consistency));

    for (std::thread& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }
    std::cout << "Final state: valueA = " << resource.valueA << ", valueB = " << resource.valueB << std::endl;
    return 0;
}

// Mitigation Strategy:
// To prevent atomicity violations:
// 1. Mutexes (`std::mutex`): Enclose the entire sequence of operations that
//    must be atomic within a critical section protected by a mutex. This ensures
//    only one thread can execute that sequence at a time.
//    Example:
//    void update_resource_atomic(int new_value) {
//        std::lock_guard<std::mutex> lock(resource_mutex); // Acquire lock
//        resource.valueA = new_value;
//        // ... other operations in the atomic sequence ...
//        resource.valueB = new_value;
//    } // Lock released automatically by lock_guard destructor
// 2. Atomic Data Types (`std::atomic`): If the operations involve simple types
//    and can be mapped to atomic hardware instructions (e.g., updating a single
//    counter, flag, or pointer), use `std::atomic`. For complex structures or
//    sequences involving multiple variables, mutexes are generally needed.
// 3. Condition Variables (`std::condition_variable`): For more complex synchronization
//    patterns where threads must wait for specific conditions related to the atomic
//    operation, condition variables can be used in conjunction with mutexes.
// 4. Software Transactional Memory (STM): Some experimental libraries or language
//    extensions offer STM, which allows blocks of code to be marked as
//    transactions, ensuring atomicity. Not standard C++.
// 5. Careful Design: Minimize shared mutable state. If operations can be designed
//    to be idempotent or to work on thread-local copies which are then merged
//    atomically, this can reduce the need for complex locking.
// 6. Immutable Data: If shared data is immutable after creation, atomicity
//    concerns for read operations are often eliminated. Updates involve creating
//    new immutable objects.
