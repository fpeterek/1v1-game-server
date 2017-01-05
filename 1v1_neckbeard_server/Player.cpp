//
//  Player.cpp
//  1v1_server
//
//  Created by Filip Peterek on 12/12/2016.
//  Copyright © 2016 Filip Peterek. All rights reserved.
//

#include "Player.hpp"

Player::Player(World & newWorld) : world(newWorld) {

    /* 10x32 are the dimensions of the sprite, but the sprite is then scaled up by 3 */
    hitbox.setSize(sf::Vector2f(30, 96));

}

void Player::move(direction movementDirection, bool changeDirection) {
    
    if (changeDirection) {
        dir = movementDirection;
    }
    
    pos.x += moveSpeed * ((movementDirection == direction::left) ? -1 : 1 );
    hitbox.setPosition(pos.x, pos.y);
    
    /* Try to move player, if player hitbox intersects with world hitbox, move opposite direction to revert movement */
    if (world.get().checkCollision(hitbox)) {
        pos.x -= moveSpeed * ((movementDirection == direction::left) ? -1 : 1 );
        hitbox.setPosition(pos.x, pos.y);
    }
    
}

void Player::jump() {
    
    if (canJump) {
        canJump = false;
        force = -1.4f;
    }
    
}

void Player::applyForce() {
    
    if (not force) {
        /* Try to move player down by 1, if it doesn't collide with anything, it means player is airborne */
        /* and we should apply gravity                                                                    */
        pos.y += 1;
        hitbox.setPosition(pos.x, pos.y);
        if (not world.get().checkCollision(hitbox)) {
            force = 0.5;
        }
        pos.y -= 1;
        hitbox.setPosition(pos.x, pos.y);
    }
    /* If force is still zero, that means player is standing on the ground and we can return */
    if (not force) {
        canJump = true;
        return;
    }
    
    if (force < 0.1 and force > -0.1) {
        force = 0;
        return;
    }
    {
        float addedForce = fabsf(force) / 50;
        force += addedForce;
    }
    if (force > Player::terminalVelocity) {
        force = Player::terminalVelocity;
    }
    
    pos.y += force;
    hitbox.setPosition(pos.x, pos.y);
    
    /* Loop should be unrolled by compiler, computer will check for collision immediately,               */
    /* if it detects no collision it returns, otherwise it                                               */
    /* tries to go back by half of what the player moved, if player hitbox still intersects with ground, */
    /* go back by half one more time                                                                     */
    for (int i = 0; i < 2; ++i) {
        
        if (world.get().checkCollision(hitbox)) {
            pos.y -= (force / 2);
            hitbox.setPosition(pos.x, pos.y);
        } else {
            if (i) {
                force = 0;
            }
            return;
        }
        
    }
    /* Player probably hit something, reset force to 0, if player still hasn't landed on the ground, */
    /* force will be reapplied next iteration of main loop                                           */
    force = 0;
    
}
