//
//  server.hpp
//  Server
//
//  Created by Gavin Forsberg on 12/6/20.
//

#ifndef server_h
#define server_h
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>

struct PACKET
{
    unsigned char flag;
    unsigned char seqNum;
    unsigned char ack;
    unsigned char checksum;
    unsigned char length;
    unsigned char dataMessage[20];
};

class server
{
public: 
    // Checksum function
    unsigned char chksum(unsigned char *buf, int count);
    
    // Gives user option for error or normal transmission
    void senderSelection();
    
    // Functions for type of transmission
    int normalTransmission();
    int randomErrorBit();
    
    // ASCII Conversion and Back
    std::vector<char> asciiConversion(char[20]);
    std::vector<char> charConversion(std::vector<int> num);
};

#endif /* server_h */
