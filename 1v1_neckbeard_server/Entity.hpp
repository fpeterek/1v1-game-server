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

struct entity {
    
    sf::Vector2i pos;
    direction dir;
    char hp;
    
};

#endif /* Entity_hpp */
