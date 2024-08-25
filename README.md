
## Concurrent Chat Server

This project is a multi-client TCP server implemented in C, designed to handle multiple clients concurrently using process forking. The server listens for incoming connections on a specified port (8080) and communicates with each client independently. It demonstrates basic server-client interaction, including handling client messages and gracefully managing server shutdown.

## Key Features

- Socket Creation: The server creates a TCP socket using the socket() function.
- Binding: It binds the socket to a specific IP address and port using the bind() function.
- Listening: The server listens for incoming connections with the listen() function.
- Forking: Upon accepting a new connection, the server forks a new child process to handle the client communication independently, allowing the parent process to continue listening for new connections.
- Client Communication: The child process handles the communication with the client, receiving a message, processing it, and sending a response back to the client.
- Concurrency: The use of fork() allows the server to handle multiple clients concurrently, making it suitable for applications where multiple clients need to interact with the server simultaneously.


## Tech Stack

* C: Programming language used for the server implementation.
* Linux/Unix: Operating system platform for running the server.
* Process Forking: Concurrency mechanism for handling multiple clients.
* GCC: Compiler used for building the server code.
* POSIX Sockets: For TCP connection management.
* Libraries Used:
  * <sys/socket.h>: For socket creation and management.
  * <netinet/in.h>: For IP address and port handling.
  * <arpa/inet.h>: For IP address conversion functions.
  * <unistd.h>: For system calls like fork() and close().
  * <signal.h>: For signal handling, e.g., graceful shutdown.


## How to run the application

### Prerequisites

* Linux Operating System
* A C compiler
* Terminal/command prompt access

### Instructions

#### 1. Clone the Repository

Clone the repository from GitHub to your local machine:

```bash
git clone https://github.com/ramankumar7c/Concurrent_ChatServer.git
cd Concurrent_ChatServer
```
#### 2. Compile the Concurrent_ChatServer

Open a terminal in the project directory and compile the code:

```bash
gcc chat_server.c -o chat_server
```

#### 3. Run the Code
In one terminal window, start the server:

```bash
./chat_server
```
The server will begin listening on port 8080.

#### 4. Connect the Client
In another terminal window connect client to server.
```bash
nc localhost 8080
```
If you want you can connect multiple client to the server, run this code in mutiple terminal.

Now start sending message from cient to server.

#### 5. Disconnect the client
If you want to disconnect any client from server just send logout message from client to server.
    
