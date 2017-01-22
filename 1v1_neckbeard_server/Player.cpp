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
    /* and the dagger needs to completely penetrate the body                 */
    _attackHitbox.setSize(sf::Vector2f(64, 6));
    _attackHitbox.setPosition(0, 0);

    resetDorito();
    
}

void Player::incrementVictoryCounter() {
    ++_gamesWon;
}

unsigned short Player::victoryCounter() {
    return _gamesWon;
}

bool Player::canPerformAction() {
    
    return not(_attackCounter or _doritoCounter);
    
}

void Player::resetAttackHitbox() {
    
    _attackHitbox.setPosition(0, 0);
    
}

void Player::resetAttack() {
    
    resetAttackHitbox();
    _attackCounter = 0;
    
}

void Player::updateDorito() {
    
    _dorito.move();
    
    if ( _world.get().checkCollision(_dorito.getHitbox()) ) {
        resetDorito();
    }
    
}

void Player::resetDorito() {
    
    _dorito.direction() = direction::right;
    _dorito.position().x = 0;
    _dorito.position().y = -100;
    
}

void Player::throwDorito() {
    
    /* Doritos can be thrown mid-jump but not mid-attack or before the previous dorito ceases to exist */
    if (_attackCounter or _dorito.position().y > 0) {
        return;
    }
    
    ++_doritoCounter;
    _sprite = (_doritoCounter / 30) + 8;
    
    if (_doritoCounter == 119) {
        
        _dorito.direction()  = _dir;
        /* +-15 so it spawns right next to the players hand */
        _dorito.position().x = _pos.x + (15 * (_dir == direction::left ? -1 : 1) );
        /* +40 so it matches the animation */
        _dorito.position().y = _pos.y + 40;
        _doritoCounter = 0;
        
    }
    
}

void Player::attack() {
    
    /* Can't attack mid-jump or mid-dorito throw */
    if (_force or _doritoCounter) {
        return;
    }
    
    /* It feels weird if the hitbox moves as soon as the sprite changes, as the blade doesn't even touch the opponent */
    /* Moving the hitbox 5 loop iterations after the sprite changes should hopefully make the game feel better        */
    if (_attackCounter == (75 + 10) or _attackCounter == (25 + 10)) {
        
        _attackHitbox.setRotation( 180 * (_dir == direction::left) );
        _attackHitbox.setPosition(_pos.x + 15 /* So it starts in the middle of the player hitbox */, _pos.y + 96 / 2);
        
    }
    
    ++_attackCounter;
    _frameCounter = _attackCounter;
    _sprite = (_attackCounter / 25) + 4;
    
    if (_attackCounter == 99) {
        resetAttack();
    }
    
}

void Player::update() {
    
    if (_attackCounter) {
        attack();
    } else if (_doritoCounter) {
        throwDorito();
    } else {
        resetSprite();
    }
    
}

Dorito & Player::getDorito() {
    
    return _dorito;
    
}

sf::RectangleShape & Player::getHitbox() {
    
    return _hitbox;
    
}

void Player::resetSprite() {
    
    _frameCounter = 0;
    _sprite = 0;
    
}

void Player::move(enum direction movementDirection) {
    
    _sprite = (int)ceilf(_frameCounter / 27.f) % 4;
    ++_frameCounter;
    
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
        _force = -3.2f;
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
    if (not _doritoCounter) {
        resetSprite();
    }
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
