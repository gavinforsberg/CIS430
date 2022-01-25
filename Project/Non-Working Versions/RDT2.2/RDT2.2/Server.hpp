//
//  Server.hpp
//  RDT2.2
//
//  Created by Gavin Forsberg on 11/19/20.
//

#ifndef Server_hpp
#define Server_hpp
#include <stdio.h>
#include "Packet.hpp"
#include <iostream>

class server
{
public:
    void senderSelection();
    void displayInformation();
    int normalTransmission();
    int randomErrorBit(); 
};

#endif /* Server_hpp */
