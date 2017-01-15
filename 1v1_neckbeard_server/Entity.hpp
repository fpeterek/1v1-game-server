//
//  Entity.hpp
//  1v1_neckbeard_server
//
//  Created by Filip Peterek on 01/01/2017.
//  Copyright © 2017 Filip Peterek. All rights reserved.
//

#ifndef Entity_hpp
#define Entity_hpp

#include <stdio.h>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "macros.hpp"

enum class direction {
    
    left = LEFT,
    right = RIGHT
    
};

class entity {
    
protected:
    direction _dir;
    char _hp;
    unsigned char _sprite;
    sf::Vector2f _pos;
    
public:
    
    /* These all just return a reference since they are freely modifiable anyway and getters make no sense */
    direction & direction();
    char & hp();
    sf::Vector2f & position();
    
    /* Just for polymorphism */
    virtual unsigned char & sprite();
    virtual unsigned short victoryCounter() = 0;
    
};

#endif /* Entity_hpp */
