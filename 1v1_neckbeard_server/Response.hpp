//
//  Response.hpp
//  1v1_neckbeard_server
//
//  Created by Filip Peterek on 01/01/2017.
//  Copyright © 2017 Filip Peterek. All rights reserved.
//

#ifndef Response_hpp
#define Response_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <array>
#include <functional>
#include <sstream>

#include "Player.hpp"

class Response {
    
    std::vector<std::reference_wrapper<entity>> _entities;
    
public:
    
    void addEntity(entity & newEntity);
    std::string generateResponse();
    
};

#endif /* Response_hpp */
