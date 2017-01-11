//
//  Player.cpp
//  1v1_server
//
//  Created by Filip Peterek on 12/12/2016.
//  Copyright © 2016 Filip Peterek. All rights reserved.
//

#include "Player.hpp"

Player::Player(World & newWorld) : _world(newWorld) {

    /* 10x32 are the dimensions of the sprite, but the sprite is then scaled up by 3 */
    _hitbox.setSize(sf::Vector2f(30, 96));
    
    /* 64 seems just about right - the sword needs to touch the other player */
    /* and the dagger needs to completely penetrate his body                 */
    _attackHitbox.setSize(sf::Vector2f(64, 6));
    _attackHitbox.setPosition(0, 0);

}

void Player::incrementVictoryCounter() {
    ++_gamesWon;
}

unsigned short Player::victoryCounter() {
    return _gamesWon;
}

bool Player::canPerformAction() {
    
    return not _attackCounter;
    
}

void Player::resetAttackHitbox() {
    
    _attackHitbox.setPosition(0, 0);
    
}

void Player::resetAttack() {
    
    resetAttackHitbox();
    _attackCounter = 0;
    
}

void Player::attack() {
    
    /* Can't attack mid-jump */
    if (_force) {
        return;
    }
    
    if (_attackCounter == 60 or _attackCounter == 20) {
        
        _attackHitbox.setRotation( 180 * (_dir == direction::left) );
        _attackHitbox.setPosition(_pos.x + 15 /* So it starts in the middle of the player hitbox */, _pos.y + 96 / 2);
        
    }
    
    /*
    std::cout << "Player at position [" << pos.x << ", " << pos.y << "], attack hitbox at position ["
              << _attackHitbox.getPosition().x << ", " << _attackHitbox.getPosition().y << "] Attack hitbox rotation: "
              << _attackHitbox.getRotation() << std::endl;
    */
    
    ++_attackCounter;
    _frameCounter = _attackCounter;
    _sprite = (_attackCounter / 20) + 4;
    
    if (_attackCounter == 79) {
        resetAttack();
    }
    
}

void Player::update() {
    
    if (_attackCounter) {
        attack();
    }
    else {
        resetSprite();
    }
    
}

sf::RectangleShape & Player::getHitbox() {
    
    return _hitbox;
    
}

void Player::resetSprite() {
    
    _frameCounter = 0;
    _sprite = 0;
    
}

void Player::move(enum direction movementDirection) {
    
    ++_frameCounter;
    _sprite = (int)ceilf(_frameCounter / 27.f) % 4;
    
    _dir = movementDirection;
    
    _pos.x += _moveSpeed * ((movementDirection == direction::left) ? -1 : 1 );
    _hitbox.setPosition(_pos.x, _pos.y);
    
    /* Try to move player, if player hitbox intersects with world hitbox, move opposite direction to revert movement */
    if (_world.get().checkCollision(_hitbox)) {
        _pos.x -= _moveSpeed * ((movementDirection == direction::left) ? -1 : 1 );
        _hitbox.setPosition(_pos.x, _pos.y);
    }
    
}

void Player::jump() {
    
    if (_canJump) {
        _canJump = false;
        _force = -2.8f;
    }
    
}

void Player::applyForce() {
    
    if (not _force) {
        /* Try to move player down by 1, if it doesn't collide with anything, it means player is airborne */
        /* and we should apply gravity                                                                    */
        _pos.y += 1;
        _hitbox.setPosition(_pos.x, _pos.y);
        if (not _world.get().checkCollision(_hitbox)) {
            _force = 0.5;
        }
        _pos.y -= 1;
        _hitbox.setPosition(_pos.x, _pos.y);
    }
    /* If force is still zero, that means player is standing on the ground and we can return */
    if (not _force) {
        _canJump = true;
        return;
    }
    
    if (_force < 0.1 and _force > -0.1) {
        _force = 0;
        return;
    }
    resetSprite();
    {
        float addedForce = fabsf(_force) / 25;
        _force += addedForce;
    }
    if (_force > Player::terminalVelocity) {
        _force = Player::terminalVelocity;
    }
    
    _pos.y += _force;
    _hitbox.setPosition(_pos.x, _pos.y);
    
    /* Loop should be unrolled by compiler, computer will check for collision immediately,               */
    /* if it detects no collision it returns, otherwise it                                               */
    /* tries to go back by half of what the player moved, if player hitbox still intersects with ground, */
    /* go back by half one more time                                                                     */
    for (int i = 0; i < 2; ++i) {
        
        if (_world.get().checkCollision(_hitbox)) {
            _pos.y -= (_force / 2);
            _hitbox.setPosition(_pos.x, _pos.y);
        } else {
            _force *= not i;
            return;
        }
        
    }
    /* Player probably hit something, reset force to 0, if player still hasn't landed on the ground, */
    /* force will be reapplied next iteration of main loop                                           */
    _force = 0;
    
}

bool Player::collidesWith(const sf::Shape & shape) {
    
    return _hitbox.getGlobalBounds().intersects(shape.getGlobalBounds());
    
}

const sf::RectangleShape & Player::getSwordHitbox() {
    
    return _attackHitbox;
    
}

void Player::takeDamage() {
    
    --_hp;
    
}

unsigned char & Player::sprite() {
    
    return _sprite;
    
}
