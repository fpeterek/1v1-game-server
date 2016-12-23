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

#define TELEPORT    't'
#define ATTACK      'a'
#define DORITO      'd'
#define MOVE        'm'
#define JUMP        'j'
#define LEFT        'l'
#define RIGHT       'r'

enum class direction {
    
    left = LEFT,
    right = RIGHT
    
};

struct position {
    int x, y;
};

struct Player {
    
    char hp;
    unsigned char damage;
    unsigned char moveSpeed;
    unsigned char sprite;
    position pos;
    std::unordered_map<char, int> spellCooldown;
    
    void move(direction dir);
    
};

#endif /* Player_hpp */
