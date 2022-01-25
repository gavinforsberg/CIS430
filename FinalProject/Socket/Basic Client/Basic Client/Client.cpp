//
//  Client.cpp
//  Basic Client
//
//  Created by Gavin Forsberg on 12/12/20.
//
// Written / compiled directly in Xcode - MacBook Pro 2.3 GHz Quad-Core Intel Core i7 - 32GB

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#define PORT 30042
using namespace std;
   
int main(int argc, char const *argv[])
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
       
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    
    //*-------------------------------------------------------//
    
    // Taking in the data
    string character = "";
    cout << "Please enter one character.\n";
    cin >> character;
    
    // Ensures user only types one character
    while(character.length() != 1)
    {
        character = "";
        cout << "\nPlease enter ONE character.\n";
        getline(cin, character);
    }
    
    // Convert string to const char * to send
    const char * c = character.c_str();
    
    // SEND TO SERVER
    send(sock, c, strlen(c), 0);
    cout << "\nMessage " << c << " sent.\n";
    
    // Receive swapped character
    valread = read(sock , buffer, 1024);
    
    // Store all of buffer in string
    string output = "";
    for(int i = 0; i < sizeof(buffer); i++)
    {
        output += buffer[i];
    }
    
    // Convert string to int
    int outputInt = stoi(output);
        
    // Print swapped charcter in hex format
    cout << "\nPrinting swapped character (hex): ";
    cout << hex << outputInt << "\n\n";
    
    return 0;
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
