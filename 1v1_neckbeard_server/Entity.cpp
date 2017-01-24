//
//  Entity.cpp
//  1v1_neckbeard_server
//
//  Created by Filip Peterek on 01/01/2017.
//  Copyright © 2017 Filip Peterek. All rights reserved.
//

#include "Entity.hpp"


unsigned short entity::victoryCounter() {
    return 0;
}

unsigned char & entity::sprite() {
    return _sprite;
}

direction & entity::getDirection() {
    return _dir;
}


char & entity::hp() {
    return _hp;
}

sf::Vector2f & entity::position() {
    return _pos;
}
