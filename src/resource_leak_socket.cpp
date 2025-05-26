// Summary: Network Socket Leak
// A network socket leak occurs when a program creates network sockets (e.g., for
// TCP/IP or UDP communication) but fails to close them properly when they are no
// longer needed. Each open socket consumes system resources (like file descriptors
// on POSIX systems). If sockets are created repeatedly (e.g., in a loop or for
// each client connection) and not closed, the program can exhaust available
// resources. This can lead to an inability to create new connections, errors, or
// even system instability, particularly critical for server applications or
// long-running clients.

#include <sys/socket.h> // For socket()
#include <netinet/in.h> // For sockaddr_in
#include <arpa/inet.h>  // For inet_pton (though not used in this minimal example)
#include <unistd.h>     // For close() (on POSIX)
#include <iostream>     // For std::cout, std::cerr

void socket_leak_example() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0); // Create a TCP socket
    if (sockfd < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return;
    }
    // Socket created, fd is sockfd. Imagine it's used for communication.
    // Missing: close(sockfd); // The socket descriptor is not closed.
    std::cout << "Socket created (fd: " << sockfd << "). Not closing to demo leak." << std::endl;
}

int main() {
    socket_leak_example();
    // The socket descriptor from socket_leak_example() is now leaked.
    // On POSIX, this means a file descriptor is consumed until program exit.
    return 0;
}

// Mitigation Strategy:
// To prevent network socket leaks:
// 1. Always Close Sockets: Explicitly close socket descriptors when they are
//    no longer needed. On POSIX systems (Linux, macOS), use `close(sockfd)`.
//    On Windows, use `closesocket(sockfd)`.
// 2. Use RAII (Resource Acquisition Is Initialization): Implement or use
//    wrapper classes for sockets whose destructors automatically close the
//    socket. This ensures cleanup even if exceptions occur.
//    Example (conceptual):
//    class SocketGuard {
//        int sock_fd_ = -1;
//    public:
//        explicit SocketGuard(int fd) : sock_fd_(fd) {}
//        ~SocketGuard() { if (sock_fd_ >= 0) { close(sock_fd_); } }
//        SocketGuard(const SocketGuard&) = delete; // Prevent copying
//        SocketGuard& operator=(const SocketGuard&) = delete;
//    };
// 3. Centralized Management: In applications with many connections, use a
//    connection manager to handle the lifecycle of sockets.
// 4. Error Handling: Ensure sockets are closed even if subsequent operations
//    (like connect, bind, send, recv) fail after the socket was created.
// 5. Check Return Values: Always verify the success of `socket()` creation.
// 6. Graceful Shutdown (TCP): For connected TCP sockets, consider `shutdown()`
//    before `close()` to manage the connection termination sequence properly.
// 7. Resource Monitoring: Be aware of and monitor file descriptor limits,
//    especially in high-load server applications.
// (Windows Note: Remember WSAStartup()/WSACleanup() for Winsock applications.)
