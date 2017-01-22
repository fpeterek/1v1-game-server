//
//  Server.hpp
//  1v1_server
//
//  Created by Filip Peterek on 12/12/2016.
//  Copyright © 2016 Filip Peterek. All rights reserved.
//

#ifndef Server_hpp
#define Server_hpp

#include <stdio.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "macros.hpp"
#include "Player.hpp"
#include "Dorito.hpp"
#include "Response.hpp"
#include "World.hpp"

class Server {
    
    sf::UdpSocket _socket;
    sf::IpAddress _addr1, _addr2;
    
    const unsigned short _clientPort, _serverPort;
    
    sf::Clock _clock;
    
    Player _player1, _player2;
    World _world;
    
    char _receivedData[255];
    
    sf::IpAddress playerConnection();
    void waitForConnection();
    
    Response _response;
    
    /* Accept a request from targetIP */
    void acceptRequest(sf::IpAddress & targetIP);
    void parseRequest(Player & player);
    
    void sendData();
    
    void sleep(const unsigned int milliseconds);
    
    void updatePlayers();
    
    void resetPlayers();
    
public:
    
    Server(unsigned short playerPort, unsigned short serverPort);
    
    void mainLoop();
    
};

#endif /* Server_hpp */
