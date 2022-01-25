//
//  Packet.cpp
//  RDT2.2
//
//  Created by Gavin Forsberg on 11/19/20.
//

#include "Packet.hpp"
using namespace std;

packet pack;

void packet::generatePacket()
{
    // Initial sequence number is 0
    setSeqNum(0);
    
    // Normal Data
    string normMsg = pack.getData();
    
    // ASCII Version of Data
    vector<unsigned char> asciiMsg = asciiConversion(pack.getData());
    
    // Unsigned short array of data (ASCII)
    unsigned short dataArray[asciiMsg.size()];
    std::copy(asciiMsg.begin(), asciiMsg.end(), dataArray);

    // Storing ACK or SEQ # in vector flag
    flag.push_back(pack.sequenceNumber);
    flag.insert(flag.end(), asciiMsg.begin(), asciiMsg.end());
    
    // Length of header and data
    setLength(pack.data.size() + 4);
    
    
    
    
    // Checksum calculation and storage
    
    unsigned char buffer[pack.length];
    std::copy(normMsg.begin(), normMsg.end(), buffer);
    for( int i = 0; i < normMsg.size(); i++)
    {
        cout << buffer[i];
    }
    
    //unsigned short errorDetection =  chksum(dataArray, (unsigned short) sizeof(dataArray)/sizeof(dataArray[0]));
    //setChecksum(errorDetection);
    
    
    
    
    
    //cout << "\nErrorDetection: " << hex << errorDetection << endl;
}


    // Checksum calculation
    // Created by Tachun Lin, Modified by Gavin Forsberg

/*
 My chksum() will produce 16-bit checksum. In this project, you should produce 8-bit checksum.
 Thus, you need to modify both the unsigned short, unsigned long, 0xFFFF0000, and 0xFFFF part to reflect the difference.

 0xFFFF0000 -> 32-bit
 0xFFFF -> 16-bit

 You'll need the data type which holds byte info for both the header and the data.

 See https://en.cppreference.com/w/cpp/language/types
 
unsigned short packet::chksum(unsigned short *buf, int count)
{
    unsigned long sum = 0;

    while(count--) {
        sum += *buf++;
        if(sum & 0xFFFF0000) {
    // --- carry occurreed, so swap around --- //
            sum &= 0xFFFF;
            sum++;
        }
    }
    return ~(sum & 0xFFFF);
}
*/

// create buffer like this:     char* buffer = new char[length];

unsigned short packet::chksum(unsigned char *buf, int count)
{
    unsigned char sum = 0;

    while(count--) {
        sum += *buf++;
        if(sum & 0xFFFF) // 16-bit: 0xFFFF
        {
    // --- carry occurreed, so swap around --- //
            sum &= 0xFF; // 8-bit: 0xFF
            sum++;
        }
    }
    return ~(sum & 0xFF);
}

