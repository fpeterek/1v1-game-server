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
        sf::RectangleShape rect( sf::Vector2f(320, 32 - 6) );
        rect.setOrigin(320 / 2, 0);
        rect.setPosition(400, 220 + 6);
        _colliders.emplace_back(rect);
        
    }
    
    /* Ground */ {
        
        /* I want the actual hitbox to be lower than the grass, so the player can walk in the grass, not on top of it */
        sf::RectangleShape rect( sf::Vector2f(800, 64 - 6) );
        rect.setPosition(0, 450 - 64 + 6);
        _colliders.emplace_back(rect);
        
    }
    
    /* Crates */ {
        
        auto initCrate = [this](int x, int y) -> void {
        
            sf::RectangleShape rect( sf::Vector2f(32, 32) );
            rect.setPosition(x, y);
            _colliders.emplace_back(rect);
        
        };
        
        /* Left spawn */
        initCrate(96 + 32, 354 - 32);
        initCrate(96 + 64, 354);
        initCrate(96, 354 - 64);
        /* Right spawn */
        initCrate(800 - 96 - 96, 354);
        initCrate(800 - 96 - 64, 354 - 32);
        initCrate(800 - 96 - 32, 354 - 64);
        /* Middle */
        initCrate(400 - 50 - 32, 354);
        initCrate(400 + 50, 354);
        /* Top */
        initCrate(400 - 32, 194);
        initCrate(400 - 64, 194 - 32);
        initCrate(400 - 96, 194);
        initCrate(400, 194);
        initCrate(400 + 32, 194 - 32);
        initCrate(400 + 64, 194);
        
    }
    
}

bool World::checkCollision(const sf::Shape & shape) {
    
    for (auto & i : _colliders) {
        
        if (shape.getGlobalBounds().intersects(i.getGlobalBounds())) {
            return true;
        }
        
    }
    
    return false;
    
}
