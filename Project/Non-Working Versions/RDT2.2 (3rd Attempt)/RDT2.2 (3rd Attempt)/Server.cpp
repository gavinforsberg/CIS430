//
//  Server.cpp
//  RDT2.2 (3rd Attempt)
//
//  Created by Gavin Forsberg on 12/7/20.
//

#include "Server.hpp"
#include "Client.hpp"
client clnt;
using namespace std;

int server::serverReceive(SERVER_PACKET pkt)
{
    
    return 0;
}

int server::normalTransmission(string msg)
{
    SERVER_PACKET pkt; // DATA message;
    
    unsigned char data[msg.size()];
    strcpy((char*)data, msg.c_str());
    
    
    pkt.checksum = chksum(pkt.dataMessage, (int) msg.size());
    cout << "Checksum: 0x" << hex << pkt.checksum << "\n";
    
    asciiConversion(msg); // This will store ASCII values into data struct too
    
    pkt.ack = 1; // std::bitset<8> x(pkt.ack);
    pkt.seqNum = 0;
    pkt.flag = 2;
    pkt.length = (sizeof(pkt.dataMessage) / sizeof(pkt.dataMessage[0])) + 4;
    
    clnt.clientReceive(pkt);
    
    return 0;
}

int server::randomErrorBit(string msg)
{
    return 0;
}

void server::senderSelection(string msg)
{
    int senderSelection;
    cout << "\n\n//// Sender ////\n\n(1) Normal outgoing packet transmission without error\n(2) Random error bit\n";
    cin >> senderSelection;
    
    // User selection
    if (senderSelection == 1)
        normalTransmission(msg); // call normal packet transmission
    else if(senderSelection == 2)
        randomErrorBit(msg); // call random bit error
    else
    {
        cout << "\nPlease only input a '1' or '2'.\n";
        cin >> senderSelection;
    }
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
void server::asciiConversion(string msg)
{
    std::vector<char> asciiMsg;
    
    for (int i = 0; i < msg.length(); i++)
    {
        char x = msg.at(i);
        asciiMsg.push_back(int(x));
    }
    
    SERVER_PACKET data;
    std::copy(asciiMsg.begin(), asciiMsg.end(), data.dataMessage);
    
    for(int i = 0; i < msg.size() + 1; i++)
    {
        cout << data.dataMessage[i] << " " ;
    }
    cout << endl;
}

vector<char> server::charConversion(vector<int> num)
{
    std::vector<char> charMsg;
    for (int i = 0; i < num.size(); i++)
    {
        charMsg.push_back(char(num[i]));
    }
    return charMsg;
}

