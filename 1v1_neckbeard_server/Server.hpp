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

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "ResourcePath.hpp"

#include "macros.hpp"
#include "Player.hpp"


class Server {
    
    sf::UdpSocket _socket;
    sf::IpAddress _addr1, _addr2;
    
    Player _player1, _player2;
    
    char _receivedData[1024];
    
    sf::IpAddress playerConnection();
    void waitForConnection();
    
    void acceptRequest();
    void parseRequest(Player & player);
    
public:
    
    Server();
    
    void mainLoop();
    
};

#endif /* Server_hpp */
