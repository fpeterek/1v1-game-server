//
//  Server.cpp
//  1v1_server
//
//  Created by Filip Peterek on 12/12/2016.
//  Copyright © 2016 Filip Peterek. All rights reserved.
//

#include "Server.hpp"

Server::Server() {
    
    if (_socket.bind(PORT) != sf::Socket::Done) {
        
        throw std::runtime_error("Error binding UDP socket to port 60 000");
        
    }
    
    
    waitForConnection();
    mainLoop();
    
}

sf::IpAddress Server::playerConnection() {
    
    char input[8];
    size_t received = 0;
    sf::IpAddress address;
    unsigned short port;
    
    while (true) {
        
        _socket.receive(input, 8, received, address, port);
        std::cout << "Received " << received << " bytes from " << address.toString() << ":" << port << " - " << input << std::endl;
        if (port != PORT_CLIENT) { continue; }
        if (strcmp(input, "connect")) { continue; }
        break;
        
    }
 
    std::cout << "Received " << received << " bytes from " << address.toString() << std::endl;
    char response[10] = { 'c', 'o', 'n', 'n', 'e', 'c', 't', 'e', 'd', '\0' };
    _socket.send(response, 10, address, port);
 
    return address;
    
}

void Server::waitForConnection() {
    
    std::cout << "IP Address: " << sf::IpAddress::getLocalAddress() << "\n" << std::endl;
    
    std::cout << "Waiting for connection...\n" << "IP Address 1: None \n" << "IP Address 2: None" << std::endl;
    _addr1 = playerConnection();
    
#ifndef NO_2_PLAYERS
    
    std::cout << "Waiting for connection... \n" << "IP Address 1: " << _addr1.toString() << "\nIP Address 2: None" << std::endl;
    _addr2 = playerConnection();
    
#endif
    
}

void Server::acceptRequest() {
    
    size_t received;
    sf::IpAddress remoteAddress;
    unsigned short remotePort;
    
    if (_socket.receive(_receivedData, 1024, received, remoteAddress, remotePort) != sf::Socket::Done) {
        return;
    }
    
    if (remoteAddress == _addr1 and remotePort == PORT_CLIENT) {
        
        Player & player = _player1;
        parseRequest(player);
        
    }
    else if (remoteAddress == _addr2 and remotePort == PORT_CLIENT) {
        
        Player & player = _player2;
        parseRequest(player);
        
    }
    
}

void Server::parseRequest(Player & player) {
    
    std::string data(_receivedData);
    
    if (data[0] == MOVE) {
        
        
        
    }
    
}

void Server::mainLoop() {
    
    std::cout << "\u001b[2J\u001b[1;1H" << std::endl;
    std::cout << "2 players connected, running server... \n";
    std::cout << "Player 1: " << _addr1.toString() << ":" << PORT_CLIENT << "\n";
    std::cout << "Player 2: " << _addr2.toString() << ":" << PORT_CLIENT << std::endl;
    
    while (true) {
        
        
        /* Accept and parse requests from both clients */
        acceptRequest();
        acceptRequest();
        
    }
    
}
