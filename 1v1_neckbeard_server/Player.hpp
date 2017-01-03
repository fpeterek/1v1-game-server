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

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Entity.hpp"

struct Player : public entity {
    
    unsigned char damage = 1;
    unsigned char moveSpeed = 5;
    unsigned char sprite;
    
    std::unordered_map<char, int> spellCooldown;
    
    void move(direction movementDirection);
    
};

#endif /* Player_hpp */
