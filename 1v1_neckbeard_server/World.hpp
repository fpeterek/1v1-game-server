//
//  World.hpp
//  1v1_neckbeard_server
//
//  Created by Filip Peterek on 03/01/2017.
//  Copyright © 2017 Filip Peterek. All rights reserved.
//

#ifndef World_hpp
#define World_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <array>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "macros.hpp"

class World {
    
    std::vector<sf::RectangleShape> _colliders;
    
public:
    
    World();
    bool checkCollision(sf::Shape & shape);
    
};

#endif /* World_hpp */
