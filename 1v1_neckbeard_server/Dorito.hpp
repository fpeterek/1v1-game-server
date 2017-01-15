//
//  Dorito.hpp
//  1v1_neckbeard_server
//
//  Created by Filip Peterek on 13/01/2017.
//  Copyright © 2017 Filip Peterek. All rights reserved.
//

#ifndef Dorito_hpp
#define Dorito_hpp

#include <stdio.h>
#include <unordered_map>
#include <functional>

#include "Entity.hpp"
#include "World.hpp"

class Dorito : public entity {
    
    sf::RectangleShape _hitbox;
    const static constexpr float speed = 3.f;
    
public:
    
    void move(enum direction dir);
    
    unsigned short victoryCounter() override;
    
};

#endif /* Dorito_hpp */
