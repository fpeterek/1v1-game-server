//
//  Response.cpp
//  1v1_neckbeard_server
//
//  Created by Filip Peterek on 01/01/2017.
//  Copyright © 2017 Filip Peterek. All rights reserved.
//

#include "Response.hpp"

void Response::addEntity(entity & newEntity) {
    
    std::reference_wrapper<entity> ref = newEntity;
    _entities.emplace_back( ref );
    
}

std::string Response::generateResponse() {
    
    std::stringstream response;
    
    for (auto & e : _entities) {
        
        response << "{";
        
        response << (int)e.get().position().x << "," << (int)e.get().position().y << "," << (char)e.get().getDirection() << ","
                 << (int)e.get().hp() << "," << (int)e.get().sprite() << "," << (int)e.get().victoryCounter();
        
        response << "}";
        
    }
    
    return response.str();
    
}
