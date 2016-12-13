//
//  Player.hpp
//  1v1_server
//
//  Created by Filip Peterek on 12/12/2016.
//  Copyright © 2016 Filip Peterek. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include <unordered_map>

#define TELEPORT 't'
#define ATTACK 'a'
#define DORITO 'd'

struct position {
    int x, y;
};

struct Player {
    
    int hp;
    position pos;
    std::unordered_map<char, double> spellCooldown;
    
};

#endif /* Player_hpp */
