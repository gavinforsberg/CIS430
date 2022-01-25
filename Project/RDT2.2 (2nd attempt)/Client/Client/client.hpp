//
//  client.hpp
//  Client
//
//  Created by Gavin Forsberg on 12/6/20.
//

#ifndef client_h
#define client_h
#include <stdio.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <string>

struct PACKET
{
    unsigned char flag;
    unsigned char seqNum;
    unsigned char ack;
    unsigned char checksum;
    unsigned char length;
    unsigned char dataMessage[20];
};

class client
{
public: 
    // Given checksum function
    char chksum(unsigned char *buf, int count);
    
    // Function to choose random/normal transmission
    void receiverSelection(std::string msg);
    
    //Functions for normal transmission and flipped bit transmission
    int normalTransmission(std::string msg);
    int randomErrorBit(std::string msg);
};

#endif /* client_h */
