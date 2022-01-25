//
//  Client.hpp
//  RDT2.2
//
//  Created by Gavin Forsberg on 11/19/20.
//

#ifndef Client_hpp
#define Client_hpp
#include <stdio.h>
#include <iostream>
#include "Packet.hpp"

class client
{
public:
    void receiverSelection();
    int normalPacket();
    int randomError();
};

#endif /* Client_hpp */
