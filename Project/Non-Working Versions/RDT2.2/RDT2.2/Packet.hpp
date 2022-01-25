//
//  Packet.hpp
//  RDT2.2
//
//  Created by Gavin Forsberg on 11/19/20.
//

#ifndef Packet_hpp
#define Packet_hpp
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>

struct data
{
    char dataMessage[20];
};

struct pkt
{   // use unsigned chars
    unsigned char flag;
    unsigned char seqNum;
    unsigned char ack;
    unsigned char checksum;
    unsigned char length;
};


class packet
{
public:
    // Function to generate all info
    void generatePacket();
    
    // Vector to hold ACK/SEQ and DATA (ASCII)
    std::vector<int> flag;
    
    // Given checksum function
    unsigned short chksum(unsigned char *buf, int count);
    
    // ASCII Conversion and Back
    std::vector<unsigned char> asciiConversion(std::string msg);
    std::vector<char> charConversion(std::vector<int> num);

    
    // Getters / Setters
    std::string getData();
    void setData(std::string d);    // Data Getter/Setter
    
    unsigned short getChecksum();
    void setChecksum(unsigned short c); // Checksum Getter/Setter
   
    unsigned long getLength();
    void setLength(unsigned long l);    // Length Getter/Setter
    
    int getSeqNum();
    void setSeqNum(int s);  // Sequence Number Getter/Setter
    
    int getACK();
    void setACK(int ack);  // ACK Getter/Setter
    
private:
    // Message (String)
    std::string data;
    
    // header components (1 byte each)
    int ack;
    int sequenceNumber;
    unsigned long length; // 1 byte per header component + length of data
    unsigned short checksum;
};

#endif /* Packet_hpp */
