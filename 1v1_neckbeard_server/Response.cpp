//
//  Response.cpp
//  1v1_neckbeard_server
//
//  Created by Filip Peterek on 01/01/2017.
//  Copyright © 2017 Filip Peterek. All rights reserved.
//

#include "Response.hpp"

void Response::addEntity(entity & newEntity) {
    
    _entities.emplace_back( newEntity );
    
}

std::string Response::generateResponse() {
    
    std::stringstream response;
    
    for (auto & e : _entities) {
        
        response << "{";
        response << e.get().pos.x << "," << e.get().pos.y << "," << (char)e.get().dir << "," << (int)e.get().hp;
        response << "}";
        
    }
    
    return response.str();
    
}
