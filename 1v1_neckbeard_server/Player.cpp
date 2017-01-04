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
        move(movementDirection == direction::left ? direction::right : direction::left, false);
        hitbox.setPosition(pos.x, pos.y);
    }
    
}

void Player::jump() {
    
    if (not force) {
        force = -7.f;
    }
    
}

void Player::gravity() {
    
    if (not force) {
        /* Try to move player down by 8, if it doesn't collide with anything, it means player is airborne */
        /* and we should apply gravity                                                                    */
        pos.y += 8;
        hitbox.setPosition(pos.x, pos.y);
        if (not world.get().checkCollision(hitbox)) {
            force = 0.5;
        }
        pos.y -= 8;
        hitbox.setPosition(pos.x, pos.y);
    }
    /* If force is still zero, that means player is standing on the ground and we can return */
    if (not force) {
        return;
    }
    
    if (force < 0.1 and force > -0.1) {
        force = 0;
    }
    
    float addedForce = fabsf(force) / 5;
    force += addedForce;
    
    pos.y += force;
    hitbox.setPosition(pos.x, pos.y);
    
    /* No collision occured, we can return */
    if (not world.get().checkCollision(hitbox)) {
        return;
    }
    
    /* Collision occured                                                                             */
    /* Try to go back by half of what the player moved, if player hitbox still intersects with land, */
    /* go back by half one more time, otherwise return                                               */
    for (int i = 0; i < 2; ++i) {
        
        if (world.get().checkCollision(hitbox)) {
            pos.y -= force / 2;
            hitbox.setPosition(pos.x, pos.y);
            return;
        }
        
    }
    
    /* Player probably hit something, reset force to 0, if player still hasn't landed on the ground, */
    /* force will be reapplied next iteration of main loop                                           */
    force = 0;
    
}
