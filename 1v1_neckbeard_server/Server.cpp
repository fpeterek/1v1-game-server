//
//  Server.cpp
//  1v1_server
//
//  Created by Filip Peterek on 12/12/2016.
//  Copyright © 2016 Filip Peterek. All rights reserved.
//

#include "Server.hpp"

Server::Server(unsigned short clientPort, unsigned short serverPort) :
        _clientPort(clientPort),
        _serverPort(serverPort),
        _player1(_world),
        _player2(_world) {
    
    if (_socket.bind(_serverPort) != sf::Socket::Done) {
        
        std::stringstream ss;
        ss << "Error binding UDP socket to port " << _serverPort;
        throw std::runtime_error(ss.str());
        
    }
    
    _response.addEntity(_player1);
    _response.addEntity(_player2);
    _response.addEntity(_player1.getDorito());
    _response.addEntity(_player2.getDorito());
    
    resetPlayers();
    
    waitForConnection();
    /* Restart clock before doing anything else */
    _clock.restart();
    mainLoop();
    
}

void Server::resetPlayers() {
    
    /* Player sprite is 10 pixels wide without hair (hitbox is 10 pixels wide) */
    /* Player sprite is scaled up by 3, therefor the hitbox is 10 * 3          */
    /* Width of player is 30                                                   */
    _player1.position().x = 110;
    _player1.position().y = 150;
    _player1.getDirection() = direction::right;
    
    _player2.position().x = 690 - 30;
#ifdef TEMPORARY_MOVE_PLAYER2
    _player2.position().x -= 200;
#endif
    _player2.position().y = 150;
    _player2.getDirection() = direction::left;
    
    auto init = [&] (Player & player) -> void {
        player.resetAttack();
        player.resetDorito();
        player.getHitbox().setPosition(player.position().x, player.position().y);
        player.hp() = 6;
    };
    
    init(_player1);
    init(_player2);
    
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
    
    std::cout << "IP Address: " << sf::IpAddress::getLocalAddress() << "\n" << std::endl;
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
    Player & player = (targetIP == _addr1) ? _player1 : _player2;
    
    sf::Socket::Status status = _socket.receive(_receivedData, 255, received, remoteAddress, remotePort);
    
    if (status != sf::Socket::Done or not player.canPerformAction()) {
        
        return player.update();
        
    }
    
    if (remoteAddress == targetIP and remotePort == _clientPort) {
        
        parseRequest(player);
        
    }
    
}

void Server::parseRequest(Player & player) {
    
    std::string data(_receivedData);
    
    /* Request won't be greater than 255 bytes, so I can use an unsigned char, because it will never overflow */
    unsigned char iter = 1;
    char action = data[iter];
    
    while (action != '}') {
        
        switch (action) {
                
            case LEFT:
            case RIGHT:
                player.move(direction(action));
                break;
            case JUMP:
                player.jump();
                break;
            case ATTACK:
                player.attack();
                break;
            case DORITO:
                player.throwDorito();
                break;
                
            default:
                break;
                
        }
        
        action = data[++iter];
            
    }
    
}

void Server::sendData() {
    
    std::string dataStr = _response.generateResponse();
    const char * data   = dataStr.c_str();
    size_t dataLen      = dataStr.length();
    
    _socket.send(data, dataLen, _addr1, _clientPort);
#ifndef NO_2_PLAYERS
    _socket.send(data, dataLen, _addr2, _clientPort);
#endif
    
}

void Server::sleep(const unsigned int milliseconds) {
    
    static int timeSlept = 0;
    int timeToSleep = milliseconds - _clock.restart().asMilliseconds() + (timeSlept < 0 ? timeSlept : 0);
    std::this_thread::sleep_for( std::chrono::milliseconds(timeToSleep) );
    timeSlept = timeToSleep;
    // std::cout << "Time slept: " << timeSlept << std::endl;

}

void Server::updatePlayers() {
    
    _player1.applyForce();
    _player1.updateDorito();
    _player2.applyForce();
    _player2.updateDorito();
    
    if ( _player1.collidesWith(_player2.getSwordHitbox()) ) {
        
        _player1.takeDamage();
        _player2.resetAttackHitbox();
        
    } else if ( _player1.collidesWith(_player2.getDorito().getHitbox()) ) {
        
        _player1.takeDamage();
        _player2.resetDorito();
        
    }
    
    if (_player2.collidesWith(_player1.getSwordHitbox())) {
        
        _player2.takeDamage();
        _player1.resetAttackHitbox();
        
    } else if ( _player2.collidesWith(_player1.getDorito().getHitbox()) ) {
        
        _player2.takeDamage();
        _player1.resetDorito();
        
    }
    
    if (_player1.hp() <= 0) {
        
        _player2.incrementVictoryCounter();
        resetPlayers();
    
    } else if (_player2.hp() <= 0) {
        
        _player1.incrementVictoryCounter();
        resetPlayers();
    
    }
    
}

void Server::mainLoop() {
    
    /* Probably don't want a blocking socket anymore, so the server doesn't stop to wait for */
    /* packet if one client loses connection                                                 */
    _socket.setBlocking(false);
    
    while (true) {
        
        /* Accept and parse requests from both clients */
        acceptRequest(_addr1);
        
#ifndef NO_2_PLAYERS
        /* Trying to accept a request from 0.0.0.0 is probably pointless */
        /* Gotta save the 5 cycles                                       */
        acceptRequest(_addr2);
#endif
        
        updatePlayers();
        
        sendData();
        
        /* I hope I can just make the thread sleep */
        sleep(15);
        
    }
    
}
