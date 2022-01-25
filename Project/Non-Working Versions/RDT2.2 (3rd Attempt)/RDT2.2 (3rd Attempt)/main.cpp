//
//  main.cpp
//  RDT2.2 (3rd Attempt)
//
//  Created by Gavin Forsberg on 12/7/20.
//

#include "Server.hpp"
#include "Client.hpp"
#include <iostream>
using namespace std;
server serve;
client client;
SERVER_PACKET pkt;

int main()
{
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
    
    serve.senderSelection(msg);
    
    for(int i = 0; i < msg.size() + 1; i++)
    {
        cout << pkt.dataMessage[i] << " " ;
    }
    cout << endl;
    
    
    return 0;
}
