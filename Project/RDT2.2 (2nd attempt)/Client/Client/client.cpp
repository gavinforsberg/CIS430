//
//  client.cpp
//  Client
//
//  Created by Gavin Forsberg on 12/5/20.
//

// Written and compiled directly on Xcode - MacBook Pro 2.3 GHz Quad-Core Intel Core i7 - 32GB

#include "client.hpp"
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <algorithm>
#include <iterator>
#include <numeric>

#define PORT 30041
#define MAX_LINE 256
#define MAX_LEN 20

using namespace std;
client clnt;


int main(int argc, const char * argv[])
{
    
    // Socket setup code from Dr. Lin/Geeks for Geeks
        // --> https://github.com/djlin/socket
        // --> https://www.geeksforgeeks.org/socket-programming-cc/
    
    int sock = 0; long valread;
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
    string msg = "";
    cout << "Please enter up to 20 characters.\n";

    getline(cin, msg);

    while(msg.length() > 20)
    {
        msg = "";
        cout << "\nPlease enter up to TWENTY characters.\n";
        getline(cin, msg);
    }

    /*
    //Might need this to add error detection after bringing "normal transmission" directly into main()
    int senderSelection;
    cout << "\n\n//// Sender ////\n\n(1) Normal outgoing packet transmission without error\n(2) Random error bit\n";
    cin >> senderSelection;

    // User selection
    if (senderSelection == 1)
        clnt.normalTransmission(msg); // call normal packet transmission
    else if(senderSelection == 2)
        clnt.randomErrorBit(msg); // call random bit error
    else
    {
        cout << "\nPlease only input a '0' or '1'.\n";
        cin >> senderSelection;
    }
    
    clnt.receiverSelection(msg);
    clnt.normalTransmission(msg);
     */
  
    PACKET pkt;
    
    std::vector<char> asciiMsg;
    
    for (int i = 0; i < msg.length(); i++)
    {
        char x = msg.at(i);
        asciiMsg.push_back(int(x));
    }
    
    std::copy(asciiMsg.begin(), asciiMsg.end(), pkt.dataMessage);
    
    unsigned char data[msg.size()];
    strcpy((char*)data, msg.c_str());
    
    pkt.checksum = clnt.chksum(data, (int) msg.size());    
    pkt.ack = 1; // print binary = std::bitset<8> x(pkt.ack);
    pkt.seqNum = 0;
    pkt.flag = 2;
    pkt.length = (sizeof(pkt.dataMessage) / sizeof(pkt.dataMessage[0])) + 4;
    
    cout << "Type '1' if you would you like a random error?\nType anything else followed by enter to continue normally.\n";
    
    int userSelect;
    cin >> userSelect;
    
    if(userSelect == 1)
    {
//        serve.randomErrorBit();
        for(int i = 0; i < pkt.length; i++)
        {
            pkt.dataMessage[0] = (unsigned char) '~';
        }
    }
    else {}
    
    send(sock, &pkt, sizeof(pkt), 0);
        
    printf("Messages sent\n");
    valread = read( sock , buffer, 1024);
    printf("%s\n", buffer);
    return 0;
}

char client::chksum(unsigned char *buf, int count)
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

void client::receiverSelection(string msg)
{
    int userSelection;
    cout << "\n\n//// Receiver ////\n\n(1) Normal outgoing packet transmission without error\n(2) Random error bit\n";
    cin >> userSelection;
    
    // User selection
    if (userSelection == 1)
        ;//normalTransmission(msg); // call normal packet transmission
    else if(userSelection == 2)
        randomErrorBit(msg); // call random bit error
}

/* Added this whole content to main
int client::normalTransmission(string msg)
{
    PACKET pkt;
    
    std::vector<char> asciiMsg;
    
    for (int i = 0; i < msg.length(); i++)
    {
        char x = msg.at(i);
        asciiMsg.push_back(int(x));
    }
    
    std::copy(asciiMsg.begin(), asciiMsg.end(), pkt.dataMessage);
    
    cout << "Printing data message: " ;
    for(int i = 0; i < asciiMsg.size();i++)
    {
        cout << pkt.dataMessage[i];
    }
    cout << endl;
    
    
    unsigned char data[msg.size()];
    strcpy((char*)data, msg.c_str());
    
    pkt.checksum = clnt.chksum(data, (int) msg.size());
    cout << "Checksum: " << pkt.checksum << endl;
    
    pkt.ack = 1; // std::bitset<8> x(pkt.ack);
    pkt.seqNum = 0;
    pkt.flag = 2;
    pkt.length = (sizeof(pkt.dataMessage) / sizeof(pkt.dataMessage[0])) + 4;
    
    return 0;
}
 */

int client::randomErrorBit(string msg)
{
    return 0;
}
