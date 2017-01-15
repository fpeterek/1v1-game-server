//
//  Dorito.cpp
//  1v1_neckbeard_server
//
//  Created by Filip Peterek on 13/01/2017.
//  Copyright © 2017 Filip Peterek. All rights reserved.
//

#include "Dorito.hpp"


unsigned short Dorito::victoryCounter() {
    return 0;
}

void Dorito::move(enum direction dir) {
    
    _pos.x += Dorito::speed * (dir == direction::left ? -1 : 1);
    _hitbox.setPosition(_pos);
    
}
