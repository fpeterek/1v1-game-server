//
//  Server.cpp
//  1v1_server
//
//  Created by Filip Peterek on 12/12/2016.
//  Copyright © 2016 Filip Peterek. All rights reserved.
//

#include "Server.hpp"

Server::Server() {
    
    // _socket.setBlocking(false);
    if (_socket.bind(PORT) != sf::Socket::Done) {
        
        throw std::runtime_error("Error binding UDP socket to port 60 000");
        
    }
    
    mainLoop();
    
}

sf::IpAddress Server::playerConnection() {
    
    char input[8];
    size_t received = 0;
    sf::IpAddress address;
    unsigned short port;
    
    while (true) {
        
        // std::this_thread::sleep_for(std::chrono::milliseconds(15));
        _socket.receive(input, 8, received, address, port);
        std::cout << "Received " << received << " bytes from " << address.toString() << ":" << port << " - " << input << std::endl;
        if (port != PORT_CLIENT) { continue; }
        if (strcmp(input, "connect")) { continue; }
        _addr1 = address;
        break;
        
    }
 
    std::cout << "Received " << received << " bytes from " << address.toString() << std::endl;
    char response[10] = { 'c', 'o', 'n', 'n', 'e', 'c', 't', 'e', 'd', '\0' };
    _socket.send(response, 10, address, port);
    
}

void Server::waitForConnection() {
    
    std::cout << "IP Address: " << sf::IpAddress::getLocalAddress() << "\n" << std::endl;
    
    std::cout << "Waiting for connection...\n" << "IP Address 1: None \n" << "IP Address 2: None" << std::endl;
    
    _addr1 = playerConnection();
    
    std::cout << "Waiting for connection... \n" << "IP Address 1: " << _addr1.toString() << "\nIP Address 2: None" << std::endl;
    
    _addr2 = playerConnection();
    
}

void Server::mainLoop() {
    
    
    waitForConnection();
    
}
