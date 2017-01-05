//
//  Server.cpp
//  1v1_server
//
//  Created by Filip Peterek on 12/12/2016.
//  Copyright © 2016 Filip Peterek. All rights reserved.
//

#include "Server.hpp"

Server::Server(unsigned short clientPort, unsigned short serverPort) :
    _clientPort(clientPort), _serverPort(serverPort), _player1(_world), _player2(_world) {
    
    if (_socket.bind(_serverPort) != sf::Socket::Done) {
        
        std::stringstream ss;
        ss << "Error binding UDP socket to port " << _serverPort;
        throw std::runtime_error(ss.str());
        
    }
    
    _response.addEntity(_player1);
    _response.addEntity(_player2);
    
    /* Player sprite is 10 pixels wide without hair (hitbox is 10 pixels wide) */
    /* Player sprite is scaled up by 3, therefor the hitbox is 10 * 3          */
    /* Width of player is 30                                                   */
    _player1.pos.x = 110;
    _player1.pos.y = 295;
    _player1.hitbox.setPosition(_player1.pos.x, _player1.pos.y);
    _player1.dir = direction::right;
    _player1.hp = 6;
        
    _player2.pos.x = 690 - 30;
    _player2.pos.y = 295;
    _player2.hitbox.setPosition(_player2.pos.x, _player2.pos.y);
    _player2.dir = direction::left;
    _player2.hp = 6;
    
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
        if (port != _clientPort) { continue; }
        if (strcmp(input, "connect")) { continue; }
        break;
        
    }
 
    std::cout << "Received " << received << " bytes from " << address.toString() << std::endl;
    char response[10] = { 'c', 'o', 'n', 'n', 'e', 'c', 't', 'e', 'd', '\0' };
    _socket.send(response, 10, address, port);
 
    return address;
    
}

void Server::waitForConnection() {
    
    {
        sf::IpAddress localIP = sf::IpAddress::getLocalAddress();
        std::cout << "IP Address: " << (localIP.toString() != "0.0.0.0" ? localIP : "None") << "\n" << std::endl;
    }
    std::cout << "Waiting for connection...\n" << "IP Address 1: None \n" << "IP Address 2: None" << std::endl;
    _addr1 = playerConnection();
    
#ifndef NO_2_PLAYERS
    
    std::cout << "Waiting for connection... \n" << "IP Address 1: " << _addr1.toString() << "\nIP Address 2: None" << std::endl;
    _addr2 = playerConnection();
    
#endif
    
    std::cout << "\u001b[2J\u001b[1;1H" << std::endl;
    std::cout << "2 players connected, running server... \n";
    std::cout << "Player 1: " << _addr1.toString() << ":" << _clientPort << "\n";
    std::cout << "Player 2: " << _addr2.toString() << ":" << _clientPort << std::endl;
    
    
}

void Server::acceptRequest(sf::IpAddress & targetIP) {
    
    size_t received;
    sf::IpAddress remoteAddress;
    unsigned short remotePort;
    
    if (_socket.receive(_receivedData, 255, received, remoteAddress, remotePort) != sf::Socket::Done) {
        return;
    }
    
    if (remoteAddress == targetIP and remotePort == _clientPort) {
        
        Player & player = (targetIP == _addr1) ? _player1 : _player2;
        parseRequest(player);
        
    }
    
}

void Server::parseRequest(Player & player) {
    
    std::string data(_receivedData);
    std::cout << data << std::endl;
    char action;
    /* Request won't be greater than 255 bytes, so I can use unsigned char, because it will never overflow */
    for (unsigned char iter = 1; action != '}'; ++iter) {
        
        action = data[iter];
        
        switch (action) {
                
            case LEFT:
            case RIGHT:
                player.move(direction(action));
                break;
            case JUMP:
                player.jump();
                break;
                
            default:
                break;
                
        }
            
    }
    
}

void Server::sendData() {
    
    std::string dataStr = _response.generateResponse();
    const char * data   = dataStr.c_str();
    size_t dataLen      = dataStr.length();
    
    _socket.send(data, dataLen, _addr1, _clientPort);
    _socket.send(data, dataLen, _addr2, _clientPort);
    
}

void Server::mainLoop() {
    
    /* Probably don't want a blocking socket anymore, so the server doesn't stop to wait for packet if one client loses connection */
    _socket.setBlocking(false);
    
    sf::Clock timer;
    int timeToSleep;
    
    while (true) {
        
        /* Accept and parse requests from both clients */
        acceptRequest(_addr1);
        
#ifndef NO_2_PLAYERS
        /* Trying to accept a request from 0.0.0.0 is probably pointless */
        /* Gotta save the 5 cycles                                       */
        acceptRequest(_addr2);
#endif
        
        _player1.applyForce();
        _player2.applyForce();
        
        sendData();
        
        timeToSleep = 10 - timer.restart().asMilliseconds();
        /* I hope I can just make the thread sleep */
        std::this_thread::sleep_for(std::chrono::milliseconds( timeToSleep ));
        
    }
    
}
