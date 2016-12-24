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
    
    
    // sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    /*
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text text("Hello SFML", font, 50);
    text.setColor(sf::Color::Black);
     */
    
    try {
        Server();
    } catch (std::runtime_error & e) {
        std::cout << e.what() << std::endl;
    }
    
    /*
    while (window.isOpen()) {
        
        sf::Event event;
        while (window.pollEvent(event)) {
            
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }

        }

        window.clear();
        window.display();

    }
    */
}
