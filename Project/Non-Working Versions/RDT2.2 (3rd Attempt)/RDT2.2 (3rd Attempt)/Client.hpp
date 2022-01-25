//
//  Client.hpp
//  RDT2.2 (3rd Attempt)
//
//  Created by Gavin Forsberg on 12/7/20.
//

#ifndef Client_hpp
#define Client_hpp
#include "packet.hpp"
#include <stdio.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

class client
{
public:
    // Function for client to receive information
    int clientReceive(SERVER_PACKET pkt);
    
    // Function to convert data in packet back to normal characters
    std::vector<unsigned char> charConversion(std::vector<unsigned char> msg);
    
    // Checksum function
    unsigned char chksum(unsigned char *buf, int count);
};

#endif /* Client_hpp */
