#include <iostream>
#include <SFML/Graphics.hpp>


void drawRoutine(sf::RenderWindow &window){
    sf::CircleShape shape;
    shape.setRadius(40.f);
    shape.setPosition(100.f,100.f);
    shape.setFillColor(sf::Color::Cyan);

    window.clear();
    window.draw(shape);
    window.display();
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    sf::RenderWindow window(sf::VideoMode(1920,1080),"SFML App");


    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
        drawRoutine(window); 

    }
    return 0;
}

