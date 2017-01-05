//
//  World.cpp
//  1v1_neckbeard_server
//
//  Created by Filip Peterek on 03/01/2017.
//  Copyright © 2017 Filip Peterek. All rights reserved.
//

#include "World.hpp"

World::World() {
    
    /* Side walls */ {
        
        sf::RectangleShape rect( sf::Vector2f(96, 352) );
        rect.setPosition(0, 450 - 352);
        _colliders.emplace_back(rect);
        
        sf::RectangleShape rect2( rect );
        rect2.setPosition(800 - 96, 450 - 352);
        _colliders.emplace_back(rect2);
        
        
    }
    
    /* Platform */ {
        
        /* I want the actual hitbox to be lower than the grass, so the player can walk in the grass, not on top of it */
        sf::RectangleShape rect( sf::Vector2f(384, 32 - 6) );
        rect.setOrigin(384 / 2, 0);
        rect.setPosition(400, 250 + 6);
        _colliders.emplace_back(rect);
        
    }
    
    /* Ground */ {
        
        /* I want the actual hitbox to be lower than the grass, so the player can walk in the grass, not on top of it */
        sf::RectangleShape rect( sf::Vector2f(800, 64 - 6) );
        rect.setPosition(0, 450 - 64 + 6);
        _colliders.emplace_back(rect);
        
    }
    
}

bool World::checkCollision(sf::Shape & shape) {
    
    for (auto & i : _colliders) {
        
        if (shape.getGlobalBounds().intersects(i.getGlobalBounds())) {
            return true;
        }
        
    }
    
    return false;
    
}
