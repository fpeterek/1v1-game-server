//
//  Player.cpp
//  1v1_server
//
//  Created by Filip Peterek on 12/12/2016.
//  Copyright © 2016 Filip Peterek. All rights reserved.
//

#include "Player.hpp"

void Player::move(direction dir) {
    
    if (dir == direction::left) {
        
        pos.x -= moveSpeed;
        
    }
    else if (dir == direction::right) {
        
        pos.x += moveSpeed;
        
    }
    
}
