//
//  main.cpp
//  MmoClientServer
//
//  Created by Andrew Borisov on 22.02.2021.
//

#include <iostream>
#include <string>
#include <vector>
#include <chrono>

#define ASIO_STANDALONE
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

std::vector<char> vBuffer(1 * 1024);

void GrabSomeData(boost::asio::ip::tcp::socket& socket)
{
    socket.async_read_some(boost::asio::buffer(vBuffer.data(), vBuffer.size()),
      [&](std::error_code ec, std::size_t length)
      {
         if(!ec)
         {
             std::cout << "\n\nRead " << length << " bytes\n\n";
             
             for (int i = 0; i < length; i++)
                std::cout << vBuffer[i];
             
             GrabSomeData(socket);
         }
      }
    );
}

int main(int argc, const char * argv[]) {
    boost::system::error_code ec;
    
    // Create a "context" - essentially the platform specific interface
    boost::asio::io_context context;
    
    // Gime some fake tasks to asio so the context doesnt finish
    boost::asio::io_context::work idleWork(context);
    
    // Start the context
    std::thread thrContext = std::thread([&](){ context.run(); });
    
    // Get the address of somewhere we wish to connect to
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::make_address("51.38.81.49"), 80);
    
    // Create a socket, the context will deliver the implementation
    boost::asio::ip::tcp::socket socket(context);
    
    // Tell socket to try and connect
    socket.connect(endpoint, ec);
    
    if (!ec)
    {
        std::cout << "Connected!" << std::endl;
    }
    else
    {
        std::cout << "Failed to connect to address:\n" << ec.message() << std::endl;
    }
    
    if(socket.is_open())
    {
        GrabSomeData(socket);
        
        std::string sRequest =
            "GET /index.html HTTP/1.1\r\n"
            "Host: example.com\r\n"
            "Connection: close\r\n\r\n";
        
        socket.write_some(boost::asio::buffer(sRequest.data(), sRequest.size()), ec);
        
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(2000ms);
    }
    
    std::cout << "Hello world" << std::endl;
    return 0;
}
