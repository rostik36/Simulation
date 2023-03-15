
#include <SFML/Graphics.hpp>
#include "body.hpp"

#define nuberofbodies 3
class Simulation
{
private:
    sf::RenderWindow& window_;
    sf::FloatRect windowBounds;
    //const int nuberofbodies = 2;
    Body particles[nuberofbodies];


public:
    Simulation(sf::RenderWindow& window);/* args */
    void run(/* args */);
    void physics();
    void update();
    void boundaries(Body& body);
    ~Simulation();
};


