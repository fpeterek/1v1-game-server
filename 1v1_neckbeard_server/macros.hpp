//
//  macros.hpp
//  1v1_neckbeard_server
//
//  Created by Filip Peterek on 14/12/2016.
//  Copyright © 2016 Filip Peterek. All rights reserved.
//

#ifndef macros_hpp
#define macros_hpp

#define PORT_SERVER 60001
#define PORT_CLIENT 60002

#define TELEPORT    't'
#define ATTACK      'a'
#define DORITO      'd'
#define JUMP        'j'
#define LEFT        'l'
#define RIGHT       'r'

#define NO_2_PLAYERS // If defined, server won't wait for second player to connect, used for debugging
#define TEMPORARY_MOVE_PLAYER2 // If defined, player 2 will spawn more in the middle - useful for hitbox testing

#endif /* macros_hpp */
