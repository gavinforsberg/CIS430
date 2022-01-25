//
//  packet.hpp
//  RDT2.2 (3rd Attempt)
//
//  Created by Gavin Forsberg on 12/7/20.
//

#ifndef packet_h
#define packet_h

struct SERVER_PACKET
{
    unsigned char flag;
    unsigned char seqNum;
    unsigned char ack;
    unsigned char checksum;
    unsigned char length;
    unsigned char dataMessage[20];
};

struct CLIENT_PACKET
{
    unsigned char flag;
    unsigned char seqNum;
    unsigned char ack;
    unsigned char checksum;
    unsigned char length;
    unsigned char dataMessage[20];
};

#endif /* packet_h */
