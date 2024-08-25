#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

#define PORT 8080
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

void handle_client(int client_socket);
void signal_handler(int sig);

void signal_handler(int sig) {
    printf("Server shutting down...\n");
    exit(0);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    pid_t child_pid;

    signal(SIGINT, signal_handler);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, MAX_CLIENTS) < 0) {
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
        if (client_socket < 0) {
            perror("Client accept failed");
            continue;
        }

        if ((child_pid = fork()) == 0) {
            close(server_socket);
            handle_client(client_socket);
            exit(0);
        } else if (child_pid < 0) {
            perror("Fork failed");
            close(client_socket);
        }

        close(client_socket);

        while (waitpid(-1, NULL, WNOHANG) > 0);
    }

    close(server_socket);
    return 0;
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received;

    while ((bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
        buffer[bytes_received] = '\0';

        buffer[strcspn(buffer, "\r\n")] = '\0';

        printf("Client: %s\n", buffer);

        if (strcmp(buffer, "logout") == 0) {
            printf("Client disconnected.\n");
            break;
        }

        // Append a newline to the message before sending it back
        strcat(buffer, "\n");

        send(client_socket, buffer, strlen(buffer), 0);
    }

    close(client_socket);
}
