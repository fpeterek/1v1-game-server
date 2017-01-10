//
//  main.cpp
//  1v1_server
//
//  Created by Filip Peterek on 12/12/2016.
//  Copyright © 2016 Filip Peterek. All rights reserved.
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "ResourcePath.hpp"

#include "Server.hpp"


int main(int argc, const char * argv[]) {
    
    try {
    
        Server(PORT_CLIENT, PORT_SERVER);
    
    } catch (std::runtime_error & e) {
    
        std::cout << e.what() << std::endl;
    
    }
    
}
