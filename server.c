#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>
#include <dirent.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define BUFFER_SIZE 1024

void list_files(char *buffer) {
    struct dirent *de;
    DIR *dr = opendir(".");

    if (dr == NULL) {
        strcpy(buffer, "Could not open current directory");
        return;
    }

    buffer[0] = '\0';
    while ((de = readdir(dr)) != NULL) {
        strcat(buffer, de->d_name);
        strcat(buffer, "\n");
    }
    closedir(dr);
}

int main() {
    WSADATA wsa;
    SOCKET server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    // Winsock Initialization
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Failed. Error Code: %d\n", WSAGetLastError());
        return 1;
    }

    // Create server socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Socket creation error: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Configure server address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind socket to the specified address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == SOCKET_ERROR) {
        printf("Bind failed with error code: %d\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        printf("Listen failed\n");
        return 1;
    }
    printf("Server listening on port %d\n", PORT);

    // Accept incoming connections and process requests
    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) == INVALID_SOCKET) {
            printf("Accept failed\n");
            return 1;
        }

        // Process the request to list files and directories
        list_files(buffer);

        // Send the list to the client
        send(new_socket, buffer, strlen(buffer), 0);
        printf("Files and directories sent to client\n");

        closesocket(new_socket);
    }

    closesocket(server_fd);
    WSACleanup();
    return 0;
}
