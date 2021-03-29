//
//  main.cpp
//  NetClient
//
//  Created by Andrew Borisov on 16.03.2021.
//

#include <iostream>
#include <olc_net.h>

enum class CustomMsgTypes : uint32_t
{
    ServerAccept,
    ServerDeny,
    ServerPing,
    MessageAll,
    ServerMessage
};

class CustomClient : public olc::net::client_interface<CustomMsgTypes>
{
    public:
        void PingServer()
        {
            olc::net::message<CustomMsgTypes> msg;
            msg.header.id = CustomMsgTypes::ServerPing;
            
            // Caution with this...
            std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
        
            msg << timeNow;
            //olc::net::client_interface.Send(msg);
            //Send(msg);
        }
    
        void MessageAll()
        {
            olc::net::message<CustomMsgTypes> msg;
            msg.header.id = CustomMsgTypes::MessageAll;
        }
};

int main(int argc, const char * argv[]) {
    CustomClient c;
    //c.Connect("127.0.0.1", 600000);
    
    return 0;
}
