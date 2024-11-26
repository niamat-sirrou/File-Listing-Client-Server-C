# List of Files and Directories in the Current Directory of the Server

## Description
This project implements a client-server application in C that allows a client to request the list of files and directories in the current directory of the server and display this list on the client side. The server and the client run on different machines and communicate through sockets.

## Functionality
1. **Server**: The server listens for incoming connections on a specified port, retrieves the list of files and directories from the current directory, and sends this list to the client.
2. **Client**: The client connects to the server, sends a request to get the list of files and directories, and then displays the list on the screen.

## Objective
- Demonstrate communication between a client and a server using sockets in C.
- Learn how to manipulate files and directories remotely.
- Practice the client-server architecture in a networked environment.

## Prerequisites
- Operating System: Windows (using `winsock2`).
- A compatible C compiler.

## Installation
1. Clone the repository.
   ```bash
   git clone https://github.com/niamat-sirrou/File-Listing-Client-Server-C.git
