//
//  main.cpp
//  Basic Server
//
//  Created by Gavin Forsberg on 12/12/20.
//
// Written / compiled directly in Xcode - MacBook Pro 2.3 GHz Quad-Core Intel Core i7 - 32GB

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#define PORT 30042

using namespace std;
char swapped(char x);

int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
       
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
       
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
       
    // Forcefully attaching socket to the port 8080
    if (::bind(server_fd, (struct sockaddr *)&address,
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                       (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    
    //*-------------------------------------------------------//
    
    // Read message from client
    valread = read( new_socket , buffer, 1024);
    cout << "Message Received: " ;
    printf("%s\n", buffer);
    
    // Extract character sent and swap nibbles
    char character = (int) buffer[0];
    unsigned char swappedCharInt = swapped(character);
    
    // Convert unsigned char to int to string to const char * to send
    int swapped = (int) swappedCharInt;
    string swappedStr = to_string(swapped);
    const char * c = swappedStr.c_str();
    
    // SEND TO CLIENT
    cout << "\nSending swapped character, " << hex << swapped << ", to client.\n";
    send(new_socket, c, strlen(c), 0);
    printf("\nMessage sent.\n\n");
    return 0;
}

// Function to swap nibbles
char swapped(char x)
{
    x &= 0xFF;
    return (unsigned char) ( (x & 0x0F) << 4 | (x & 0xF0) >> 4 );
}

// Socket setup code modified from Geeks for Geeks
    // --> https://www.geeksforgeeks.org/socket-programming-cc/
// Other resources helpful (not necessarily taken from)
    // --> Bitwise shifting https://stackoverflow.com/questions/12515412/what-is-this-doing-input-4-0x0f
    // --> Swap bits https://stackoverflow.com/questions/16700498/in-a-byte-how-to-swap-the-4-higher-bits-with-its-4-lower-bits (not really how i did it)
    // --> Printf bytes https://stackoverflow.com/questions/3555791/why-does-printf-not-print-out-just-one-byte-when-printing-hex
    // --> Recv issues https://stackoverflow.com/questions/28246190/socket-close-while-recv-issue
    // --> Empty buffer https://stackoverflow.com/questions/38474190/empty-buffer-after-successful-recv
    // --> Beej Guide http://beej.us/guide/bgnet/pdf/bgnet_usl_c_1.pdf
    // --> Read socket https://stackoverflow.com/questions/666601/what-is-the-correct-way-of-reading-from-a-tcp-socket-in-c-c
