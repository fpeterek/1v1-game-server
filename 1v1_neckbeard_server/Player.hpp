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
#include <functional>

#include "Entity.hpp"
#include "Dorito.hpp"
#include "World.hpp"

class Player : public entity {
    
    unsigned long  _frameCounter  = 0;
    unsigned char  _moveSpeed     = 1;
    unsigned char  _attackCounter = 0;
    unsigned char  _doritoCounter = 0;
    unsigned short _gamesWon      = 0;
    bool           _canJump;
    Dorito         _dorito;
    /* Force that affects the player, negative force brings the player up, positive force brings the player down */
    float _force = 0;
    constexpr static const float terminalVelocity = 7.f;
    
    std::reference_wrapper<World> _world;
    
    sf::RectangleShape _hitbox;
    sf::RectangleShape _attackHitbox;
    
    std::unordered_map<char, int> _spellCooldown;
    
public:
    
    sf::RectangleShape & getHitbox();
    const sf::RectangleShape & getSwordHitbox();
    
    Dorito & getDorito();
    
    void move(enum direction movementDirection);
    void attack();
    void throwDorito();
    void jump();
    void applyForce();
    void resetSprite();
    void update();
    void resetAttackHitbox(); /* Only resets the hitbox */
    void resetAttack(); /* Resets the hitbox as well as the counter and stops the animation */
    void incrementVictoryCounter();
    void takeDamage();
    
    bool collidesWith(const sf::Shape & shape);
    bool canPerformAction();

    unsigned short victoryCounter() override;
    
    Player(World & newWorld);
    
};

#endif /* Player_hpp */
