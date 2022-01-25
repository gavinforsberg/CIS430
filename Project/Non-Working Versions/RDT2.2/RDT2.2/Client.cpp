//
//  Client.cpp
//  RDT2.2
//
//  Created by Gavin Forsberg on 11/19/20.
//

#include "Client.hpp"
using namespace std;

/*---------- RECEIVER ----------*/

// Just asks the user whether they want random bit error or a normal transmission. Calls methods accordingly.
void client::receiverSelection()
{
    int userSelection;
    cin >> userSelection;
    // User selection
    if (userSelection == 1)
        normalPacket(); // call normal packet transmission
    else if(userSelection == 2)
        randomError(); // call random bit error
}

int client::normalPacket()
{
    return 0;
}

int client::randomError()
{
    return 0;
}
