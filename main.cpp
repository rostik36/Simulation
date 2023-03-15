//#include <SFML/Graphics.hpp>

#include "Simulation.hpp"

int main()
{
    
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
    //sf::CircleShape shape(100.f);
    //shape.setFillColor(sf::Color::Green);
    Simulation simulation(window);
    
    //float pos_x=0.001f;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
       

        simulation.run();
    }

    return 0;
}