//
//  Checksum.cpp
//  RDT2.2
//
//  Created by Tachun Lin
//  Modified by Gavin Forsberg
//

#include <stdio.h>
#include <iostream>
#include <vector>
//extern std::istream cin;

using namespace std;

//unsigned short chksum(unsigned short *buf, int count);
unsigned char chksum(unsigned char *buf, int count);
//uint8_t chksum8(const unsigned char *buff, size_t len);
struct data
{
    unsigned char data[20];
};

struct packet
{
    unsigned char flag;
    unsigned char seqNum;
    unsigned char ack;
    unsigned char checksum;
    unsigned char length;
    unsigned char dataMessage[20];
};

int main() {
    
    //unsigned short input[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    //unsigned short input [] = {119, 111, 114, 107, 32, 110, 111, 119};
    
    //unsigned char input[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 119, 111, 114, 107, 32, 110, 111, 119, 29, 182};
    
    unsigned char input[20] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t'};
    
    //unsigned char input[] = {119, 111, 114, 107, 32, 110, 111, 119};
    
    //unsigned char input[] = {119, 111, 114, 107, 32, 110, 111, 119};
    
    //unsigned char input[20];
    
    
    string data = "";
    cout << "Please enter up to 20 characters.\n";
    // getline(cin, data);
    
    std::vector<unsigned char> messageInput;
    
    // ASCII Converter
    for (int i = 0; i < data.length(); i++)
    {
        char x = data.at(i);
        messageInput.push_back(int(x));
    }
    
    // unsigned char input[messageInput.size()];
    // std::copy(messageInput.begin(), messageInput.end(), input);
    
//    for (int i = 0; i < sizeof(input)/sizeof(input[0]); i++)
//    {
//       cout << input[i];
//    }
    
    unsigned char checksum = chksum(input, sizeof(input)/sizeof(input[0]));
    cout << "0x" << hex << checksum << endl;

    return 0;
}

unsigned char chksum(unsigned char *buf, int count)
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
