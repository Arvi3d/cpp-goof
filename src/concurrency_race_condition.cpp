// Summary: Concurrency Issue - Race Condition (Data Corruption)
// A race condition occurs when multiple threads access shared data concurrently,
// and at least one of them modifies the data. The outcome of the computation
// depends on the non-deterministic order in which accesses take place.
// This can lead to corrupted data, incorrect results, crashes, or other
// unpredictable behavior. For example, a common "read-modify-write"
// operation (like incrementing a counter: value = value + 1) is not atomic
// and can be interleaved by threads, causing updates to be lost.

#include <iostream>
#include <thread>
#include <vector>
#include <mutex> // For mitigation example

// Shared data prone to race condition
long long shared_counter = 0;

// Function executed by each thread (vulnerable version)
void increment_counter_racy(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        shared_counter++; // Read-modify-write: NOT ATOMIC!
    }
}

int main() {
    const int num_threads = 10;
    const int iterations_per_thread = 100000;
    std::vector<std::thread> threads;

    std::cout << "Expected counter value: " << num_threads * iterations_per_thread << std::endl;

    for (int i = 0; i < num_threads; ++i) {
        threads.push_back(std::thread(increment_counter_racy, iterations_per_thread));
    }

    for (std::thread& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    std::cout << "Actual counter value (racy): " << shared_counter << std::endl;
    // The actual value will likely be less than expected due to lost updates.
    return 0;
}

// Mitigation Strategy:
// To prevent race conditions and ensure data integrity:
// 1. Mutexes (Mutual Exclusion): Use `std::mutex` to protect critical sections
//    where shared data is accessed. Only one thread can own the mutex at a time.
//    Example:
//    std::mutex mtx;
//    void increment_safe() {
//        std::lock_guard<std::mutex> lock(mtx); // RAII lock
//        shared_counter++;
//    }
// 2. Atomic Operations: For simple operations like incrementing, use
//    `std::atomic` types (e.g., `std::atomic<long long> shared_counter;`).
//    Atomic operations are guaranteed to be performed without interruption.
//    Example: `std::atomic<long long> atomic_counter; atomic_counter++;`
// 3. Condition Variables (`std::condition_variable`): Use with mutexes to manage
//    complex synchronization scenarios where threads need to wait for certain
//    conditions to become true.
// 4. Read-Write Locks (`std::shared_mutex` in C++17): Allow multiple readers
//    or one writer, useful when reads are more frequent than writes.
// 5. Thread-Safe Data Structures: Design or use data structures that are
//    inherently thread-safe, encapsulating their own synchronization.
// 6. Avoid Sharing Data: If possible, redesign algorithms to minimize or
//    eliminate shared mutable state. Use thread-local storage or pass data
//    via messages between threads.
// 7. Careful Design and Review: Concurrency bugs are hard to find. Carefully
//    design concurrent interactions and review them thoroughly.
// 8. Testing and Tools: Use thread sanitizers (e.g., TSan in GCC/Clang)
//    and stress testing to help detect race conditions.
