#include "Simulation.hpp"

#include <cstdlib> // needed for rand() and srand()
#include <ctime>   // needed for time()


int main()
{
    // Seed the random number generator with the current time
    srand(time(nullptr));

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
    window.setPosition(sf::Vector2i(0,0));  // start window pos

    Simulation simulation(window);
    
    sf::Clock clock; // create a clock object to measure elapsed time
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
       

        simulation.run(clock.restart().asSeconds());
    }

    return 0; 
}