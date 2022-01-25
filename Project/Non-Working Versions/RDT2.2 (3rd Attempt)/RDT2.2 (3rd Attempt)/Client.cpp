//
//  Client.cpp
//  RDT2.2 (3rd Attempt)
//
//  Created by Gavin Forsberg on 12/7/20.
//

#include "Client.hpp"
#include "Server.hpp"
#include "packet.hpp"
#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;

int client::clientReceive(SERVER_PACKET pkt)
{
    CLIENT_PACKET cpkt;
    vector<unsigned char> incomingMessage;
    copy(begin(pkt.dataMessage), end(pkt.dataMessage), begin(incomingMessage));
    
    //vector<unsigned char> charMsg = charConversion(incomingMessage);
    
    cout << "incomingMsg: \n";
    for(int i = 0; i < incomingMessage.size(); i++)
    {
        cout << incomingMessage[i];
    }
//    cout << "CharMsg: \n";
//    for(int i = 0; i < charMsg.size(); i++)
//    {
//        cout << charMsg[i] << " " ;
//    }
    
    //run checksum before "accepting" the packet
    //unsigned char checksum = chksum(pkt.dataMessage, pkt.length);
    
    //if(checksum == pkt.checksum)
        cout << "Checksum is the same. No data corruption.\n";
    //else
        cout << "Checksum is different. Data has been corrupted.\n";
    
    
    cout << "\nPacket received.\n";
    return 0;
}

vector<unsigned char> client::charConversion(vector<unsigned char> msg)
{
    std::vector<unsigned char> charMsg;
    for (int i = 0; i < msg.size(); i++)
    {
        charMsg.push_back(char(msg[i]));
    }
    return charMsg;
}

unsigned char client::chksum(unsigned char *buf, int count)
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
