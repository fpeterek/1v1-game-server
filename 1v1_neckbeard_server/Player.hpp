//
//  Player.hpp
//  1v1_server
//
//  Created by Filip Peterek on 12/12/2016.
//  Copyright © 2016 Filip Peterek. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include <unordered_map>
#include <functional>

#include "Entity.hpp"
#include "World.hpp"

struct Player : public entity {
    
    unsigned char damage    = 1;
    unsigned char moveSpeed = 5;
    unsigned char sprite    = 0;
    /* Force that affects the player, negative force brings the player up, positive force brings the player down */
    float force = 0;
    constexpr static const float terminalVelocity = 7.f;
    
    std::reference_wrapper<World> world;
    
    sf::RectangleShape hitbox;
    
    std::unordered_map<char, int> spellCooldown;
    
    void move(direction movementDirection, bool changeDirection = true);
    void jump();
    void gravity();
    
    Player(World & newWorld);
    
};

#endif /* Player_hpp */
