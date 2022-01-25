//
//  Server.cpp
//  RDT2.2
//
//  Created by Gavin Forsberg on 11/19/20.
//

#include "Server.hpp"
using namespace std;
packet packetObj;




/*
 Not sure I understand how the buffer works. What data type to use? Where does it go? etc
 Unsure of how to checksum all header/data
        Parameter data type is unsigned short, so all other data types (for length, seq num, ack, etc) should be unsigned short?)
        It looks like the parameter is a pointer to the buffer? So figure out buffer/how it works first
 I think using structs for data, packet, etc. is a better way to do this project than generatePacket(), all methods involving it, and everything that went with that start.
    ---> and if so, i should break up parts of generatePacket method for simplicity and to condense unnecessary parts but keep useful components
 */





/*--------- SENDER ---------*/

// Just asks the user whether they want random bit error or a normal transmission. Calls methods accordingly.
void server::senderSelection()
{
    int senderSelection;
    cout << "\n\n//// Sender ////\n\n(1) Normal outgoing packet transmission without error\n(2) Random error bit\n";
    cin >> senderSelection;
    
    // User selection
    if (senderSelection == 1)
        normalTransmission(); // call normal packet transmission
    else if(senderSelection == 2)
        randomErrorBit(); // call random bit error
    else
    {
        cout << "\nPlease only input a '0' or '1'.\n";
        cin >> senderSelection;
    }
}

// This method is based on the structs in packet header file. Everything else so far has been based on generatePacket in packet.cpp file
int server::normalTransmission()
{
    // Initializing some variables in the packet / data struct
    struct pkt pack;
    struct data dataMsg;
    
    // Generating some data via the method in packet.cpp
    packetObj.generatePacket();
    
    // Getting a string version of data, converting it to ASCII from packet.cpp conversion method,
        //  and storing the result in pack struct data variable
    string data = packetObj.getData();
    
    
    pack.data = packetObj.asciiConversion(packetObj.getData());
    dataMsg.dataMessage;
    
    // Directly making seqNum zero to start
    pack.seqNum = 0;
    
    // Directly assinging the ACK as 01, also storing it in the flag
    pack.ack = 01;
    pack.flag = pack.ack;
    
    // Setting the length of packet structure to packet's set length
    packetObj.setLength(data.size() + 4);
    pack.length = packetObj.getLength();
    
    
        // very unsure about how to implement checksum
        // checksum
//    unsigned short allDataArray[pack.length]; // Create an array of unsigned shorts including all header data/data?
//    std::copy(pack.data.begin(), pack.data.end(), allDataArray); // copy data into array
//
      //Trying to see what's in the array now
//    for(int i = 0; i < pack.length; i++)
//    {
//        for(int j = 0; j < pack.length; i++)
//        allDataArray[i];
//    }
    
    
//    packetObj.chksum(<#unsigned short *buf#>, <#int count#>);
    
    
    
    return 0;
}

// Alternative to above method
int server::randomErrorBit()
{
    packetObj.generatePacket();
    
    return 0;
}


// Not complete at all, just a method to show what's created from packet.cpp's generatePacket method
void server::displayInformation()
{
    // output binary:   (std::bitset<8>([variable]);)
    
    cout << "\n\nAll information below is produced from generatePacket: ";
    packetObj.generatePacket();
    
    int seqNum = packetObj.getSeqNum();
    unsigned long len = packetObj.getLength();
    unsigned short checksum = packetObj.getChecksum();
    
    
    
    
    cout << "\nseqNum: " << bitset<8>(seqNum) << "\nLength: " << std::bitset<8>(len) << "\nChecksum: 0x" << hex << checksum;
        
    cout << "\nFlag: ";
    cout << "\n\tACK: " << packetObj.flag[0];
    cout << "\n\tData: ";
    for(int i = 1; i < packetObj.getData().size() + 1; i++)
    {
        cout << (char) packetObj.flag[i];
    }
    
    cout << endl;
}
