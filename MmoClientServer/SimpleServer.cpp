//
//  main.cpp
//  MmoClientServer
//
//  Created by Andrew Borisov on 22.02.2021.
//

#include <iostream>
#include <olc_net.h>

enum class CustomMsgTypes : uint32_t
{
    ServerAccept,
    ServerDeny,
    ServerPing,
    MessageAll,
    ServerMessage,
};

class CustomServer : public olc::net::server_interface<CustomMsgTypes>
{
public:
    CustomServer(uint16_t nPort) : olc::net::server_interface<CustomMsgTypes>(nPort);
    {
        
    }
protected:
    virtual bool OnClientConnect(olc::shared_ptr<olc::net::connection<CustomMsgTypes>> client)
    {
        olc::net::message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::ServerAccept;
        client->Send(msg);
        return true;
    }
}

int main(int argc, const char * argv[]) {
    
    return 0;
}
