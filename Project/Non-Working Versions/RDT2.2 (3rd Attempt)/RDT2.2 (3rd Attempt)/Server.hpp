//
//  Server.hpp
//  RDT2.2 (3rd Attempt)
//
//  Created by Gavin Forsberg on 12/7/20.
//

#ifndef Server_hpp
#define Server_hpp
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <cstring>
#include <string.h>
#include <iostream>
#include "packet.hpp"


class server
{
public:
    // Checksum function
    unsigned char chksum(unsigned char *buf, int count);
    
    // Gives user option for error or normal transmission
    void senderSelection(std::string msg);
    
    // Functions for type of transmission
    int normalTransmission(std::string msg);
    int randomErrorBit(std::string msg);
    
    // Receive Function
    int serverReceive(SERVER_PACKET pkt);

    // ASCII Conversion and Back
    void asciiConversion(std::string msg);
    std::vector<char> charConversion(std::vector<int> num);
};

#endif /* Server_hpp */
