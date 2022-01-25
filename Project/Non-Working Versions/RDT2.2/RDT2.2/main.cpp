//
//  main.cpp
//  RDT2.2
//
//  Created by Gavin Forsberg on 11/19/20.
//

#include <iostream>
#include "Client.hpp"
#include "Packet.hpp"
#include "Server.hpp"
#include <sstream>
#include <cstring>
#include <bitset>
using namespace std;

/*
 1. Client and server are standalone executables.
 You don't have the socket in your code to allow client/server to communicate.
 Check my sample code
 https://github.com/djlin/socket

 2. I created issues on GitHub with my comments.
 Check them out

 3. The initial packet (data packet) has flag =10 (binary, 2 in decimal).
 Your code prints ACK: 0 <- this should be 2 (in decimal).
        -----> https://stackoverflow.com/questions/7349689/how-to-print-using-cout-a-number-in-binary-form

 Best regards,
 Tachun
 --
 Tachun Lin, Ph.D.
 Associate Professor
 Dept. of Computer Science & Information Systems
 Bradley University
 */

/*--------- OVERVIEW ---------*/
/*
    Sender sends data (up to 20 characters)
        Receiver accepts packet (after verifying checksum / no errors)
        --> Print out content of packet --> send back an ACK without data and reset length to 0
    Sender receives expected ACK --> print out buffer message and erase buffer content
    Sender and receiver can continue to exchange messages until terminated but keeps original options (with/without error)
    
 
    Sender Start: given two options: normal transmission or random bit error
        --> Bit error is randomly selected and flipped AFTER checksum is calculated.
        --> Can send up to 20 characters of data --> ORIGINAL packet should be stored in the buffer for retransmission
    Receiver Start: given two options: normal transmission or random error bit in ACK
        --> error bit randomly selected and flipped after checksum is calculated
*/

int main()
{
    packet pack;    server serve;   //client clnt;    //struct pkt structPack;
    
    // Taking in the data
    string msg = "";
    cout << "Please enter up to 20 characters.\n";
    
    getline(cin, msg);
    
    while(msg.length() > 20)
    {
        msg = "";
        cout << "\nPlease enter up to TWENTY characters.\n";
        getline(cin, msg);
    }
    
    // Sets data with message input above
    pack.setData(msg);
    
    // Selection method from server.cpp
    serve.senderSelection();
    
    // packet.cpp method
    pack.generatePacket();
    
    // displays information using generatePacket()
    serve.displayInformation();
    
    
    
    
    /* Some calls I will probably have to end up making based on order of the assingment details */
    
    // sender.send()
    // receiver.receive()
    // receiver.checksum()
    // receiver.verifyChecksum()
    // receiver.displayPacketContent()
    // receiver.sendACK -> maybe in this method it resets data and length
    // sender.receive() --> will check until ack is right?
    // sender.printBufferMsg --> maybe reset buffer when completed
    // program.restart?
}
