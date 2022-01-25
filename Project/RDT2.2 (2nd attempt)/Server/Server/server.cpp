//
//  main.cpp
//  Server
//
//  Created by Gavin Forsberg on 12/5/20.
//

#include "server.hpp"
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <netdb.h>
#include <cstring>
#define PORT 30041

using namespace std;
server serve;
int normalTransmission();
int randomErrorBit();
unsigned char chksum(unsigned char *buf, int count);


int main(int argc, const char * argv[])
{
    // Much of socket setup code adapted from Dr. Lin/Geeks for Geeks
        // --> https://github.com/djlin/socket
        // --> https://www.geeksforgeeks.org/socket-programming-cc/
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int s, new_socket;
    PACKET pkt;
    
    bzero((char*) &address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    
    // Creating socket file descriptor
    if(( s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
       
    // Forcefully attaching socket to the port 8080
    if((::bind(s, (struct sockaddr *) &address, sizeof(address))) < 0)
    {
        perror("Bind Failed.");
        exit(EXIT_FAILURE);
    }
        listen(s, 1);
    
    if ((new_socket = accept(s, (struct sockaddr *) &address, (socklen_t*) &addrlen)) < 0)
    {
        perror("Server: accept");
        exit(EXIT_FAILURE);
    }
    
    new_socket = (int) recv(new_socket, (void*)&pkt, sizeof(pkt), 0);
        
    cout << "Type '1' if you would you like a random error?\nType anything else followed by enter to continue normally.\n";
    
    int userSelect;
    cin >> userSelect;
    
    if(userSelect == 1)
    {
//        serve.randomErrorBit();
        for(int i = 0; i < pkt.length; i++)
        {
            pkt.dataMessage[3] = (unsigned char) '~';
        }
    }
    else {}
    
    unsigned char errorDetection = serve.chksum(pkt.dataMessage, pkt.length);
    cout << "\nReceived checksum: 0x" << hex << pkt.checksum << "\nGenerated Checksum: 0x" << hex << errorDetection << endl;
    
    if(errorDetection == pkt.checksum)
    {
        cout << "Message Accepted. Checksums were equivalent.\nMessage: ";
        for(int i = 0; i < pkt.length; i++)
        {
            cout << pkt.dataMessage[i];
        }
        cout << endl;
    }
    else
        cout << "Message was corrupt. Checksums did not match. Message deleted.\n\n";
    
    close(new_socket);
    
    
    /*
    // wait for connection, then receive and print text
    while(1)
    {
        while((length = recv(new_socket, (void*)&pkt, sizeof(buffer), 0)))
        {
            
           // fputs(buffer, stdout);
        }
        
        
        
        close(new_socket);
    }
     */
}




unsigned char server::chksum(unsigned char *buf, int count)
{
    unsigned long sum = 0;

    while(count--)
    {
        sum += *buf++;

        if(sum & 0xFF00) // 16-bit: 0xFF00
        {
    // --- carry occurreed, so swap around --- //
            sum &= 0xFF; // 8-bit: 0xFF
            sum++;
        }
    }
    // return (uint8_t)sum; --> uint8_t guaranteed the smallest unsigned type, upper bits guaranteed to be "cut off"
            // https://stackoverflow.com/questions/31151032/writing-an-8-bit-checksum-in-c
    return ~(sum & 0xFF);
}

// ASCII Conversion and Back
//vector<char> server::asciiConversion(char[20] msg)
//{
//    std::vector<char> asciiMsg;
//    for (int i = 0; i < msg.length(); i++)
//    {
//        char x = msg.at(i);
//        asciiMsg.push_back(int(x));
//    }
//    return asciiMsg;
//}
vector<char> server::charConversion(vector<int> num)
{
    std::vector<char> charMsg;
    for (int i = 0; i < num.size(); i++)
    {
        charMsg.push_back(char(num[i]));
    }
    return charMsg;
}

int server::normalTransmission()
{
    // Taking in the data
    string msg = "";
    cout << "Please enter up to 20 characters.\n";
    
    getline(cin, msg);
    
    while(msg.length() > 20)
    {
        msg = "";
        cout << "\nPlease enter up to TWENTY characters.\n";
        getline(cin, msg);
    }
    
    unsigned char data[msg.size()];
    strcpy((char*)data, msg.c_str());
    PACKET pkt;
    
    pkt.checksum = serve.chksum(data, (int) msg.size());
    cout << pkt.checksum << endl;
    
    pkt.ack = 1; // std::bitset<8> x(pkt.ack);
    pkt.seqNum = 0;
    pkt.flag = 2;
    pkt.length = (sizeof(pkt.dataMessage) / sizeof(pkt.dataMessage[0])) + 4;
    
    return 0;
}

int server::randomErrorBit()
{
    PACKET pkt;
    for(int i = 0; i < pkt.length; i++)
    {
        pkt.dataMessage[3] = (unsigned char) '~';
    }
    return 0;
}

void server::senderSelection()
{
    int senderSelection;
    cout << "\n\n//// Sender ////\n\n(1) Normal outgoing packet transmission without error\n(2) Random error bit\n";
    cin >> senderSelection;
    
    // User selection
    if (senderSelection == 1)
        serve.normalTransmission(); // call normal packet transmission
    else if(senderSelection == 2)
        serve.randomErrorBit(); // call random bit error
    else
    {
        cout << "\nPlease only input a '0' or '1'.\n";
        cin >> senderSelection;
    }
}
