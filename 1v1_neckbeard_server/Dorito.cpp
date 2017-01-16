//
//  Dorito.cpp
//  1v1_neckbeard_server
//
//  Created by Filip Peterek on 13/01/2017.
//  Copyright © 2017 Filip Peterek. All rights reserved.
//

#include "Dorito.hpp"

Dorito::Dorito() {
    
    _hitbox.setSize( sf::Vector2f(16, 16) );
    
}

unsigned short Dorito::victoryCounter() {
    return 0;
}

void Dorito::move() {
    
    _pos.x += Dorito::speed * (_dir == direction::left ? -1 : 1);
    _hitbox.setPosition(_pos);
    
}

const sf::RectangleShape & Dorito::getHitbox() {
    
    return _hitbox;
    
}
