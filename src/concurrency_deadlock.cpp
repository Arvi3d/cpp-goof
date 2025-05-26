// Summary: Concurrency Issue - Deadlock
// A deadlock is a state in concurrent programming where two or more threads
// are blocked forever, each waiting for a resource held by another thread
// in the same set. A common scenario involves two threads trying to acquire
// two mutexes in opposite orders. Thread A locks mutex1 and tries to lock
// mutex2, while Thread B locks mutex2 and tries to lock mutex1. Neither
// can proceed, resulting in a deadlock. The program will typically hang.

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono> // For std::this_thread::sleep_for

std::mutex mutex1;
std::mutex mutex2;

// Thread 1 tries to lock mutex1 then mutex2
void process1() {
    std::cout << "Thread 1: Trying to lock mutex1...\n";
    std::lock_guard<std::mutex> lock1(mutex1);
    std::cout << "Thread 1: Locked mutex1.\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Encourage deadlock
    std::cout << "Thread 1: Trying to lock mutex2...\n";
    std::lock_guard<std::mutex> lock2(mutex2); // Waits for mutex2
    std::cout << "Thread 1: Locked mutex2.\n";
    // Do work with both mutexes
    std::cout << "Thread 1: Releasing locks.\n";
}

// Thread 2 tries to lock mutex2 then mutex1
void process2() {
    std::cout << "Thread 2: Trying to lock mutex2...\n";
    std::lock_guard<std::mutex> lock2(mutex2);
    std::cout << "Thread 2: Locked mutex2.\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Encourage deadlock
    std::cout << "Thread 2: Trying to lock mutex1...\n";
    std::lock_guard<std::mutex> lock1(mutex1); // Waits for mutex1
    std::cout << "Thread 2: Locked mutex1.\n";
    // Do work with both mutexes
    std::cout << "Thread 2: Releasing locks.\n";
}

int main() {
    std::cout << "Starting deadlock example. Program will likely hang.\n";
    std::thread t1(process1);
    std::thread t2(process2);

    if (t1.joinable()) t1.join();
    if (t2.joinable()) t2.join();

    std::cout << "Deadlock example finished (if it didn't hang).\n"; // Likely not reached
    return 0;
}

// Mitigation Strategy:
// To prevent deadlocks:
// 1. Lock Ordering (Lock Hierarchy): Establish a global order for acquiring
//    locks. All threads must acquire locks in this predefined order. If a
//    thread holds lock A and needs lock B, and A < B in the hierarchy, this is
//    fine. But it cannot try to acquire A if it already holds B.
// 2. Try Lock (`std::try_lock` or `std::timed_mutex::try_lock_for`):
//    Attempt to acquire a lock, but if it's not available, don't block.
//    Instead, release any locks already held and try again later, or take
//    an alternative action. This is more complex to implement correctly.
//    Example:
//    if (mtx1.try_lock()) {
//        if (mtx2.try_lock()) { /* ... */ mtx2.unlock(); }
//        mtx1.unlock();
//    }
// 3. `std::lock` (C++11): Use `std::lock(mutex1, mutex2, ...)` to acquire
//    multiple locks simultaneously in an all-or-nothing fashion, using a
//    deadlock-avoidance algorithm internally. Then use `std::lock_guard`
//    with `std::adopt_lock` for RAII.
//    Example:
//    std::lock(m1, m2); // Deadlock-avoidance algorithm
//    std::lock_guard<std::mutex> guard1(m1, std::adopt_lock);
//    std::lock_guard<std::mutex> guard2(m2, std::adopt_lock);
// 4. Avoid Holding Locks for Long Durations: Minimize the time locks are held.
// 5. Avoid Calling External Code While Holding Locks: External code might
//    try to acquire other locks, potentially leading to unexpected deadlocks.
// 6. Deadlock Detection Tools: Some advanced debuggers or analysis tools can
//    help detect potential or actual deadlocks.
// 7. Scoped Locks (`std::scoped_lock` in C++17): A variadic RAII wrapper that
//    acquires multiple locks using a deadlock-avoidance algorithm. This is often
//    the simplest and safest way to lock multiple mutexes.
//    Example: `std::scoped_lock locks(m1, m2);`
