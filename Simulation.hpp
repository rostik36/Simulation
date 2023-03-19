#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "wing.hpp"
#include "particle.hpp"
#include "line.hpp"
//#include "body.hpp"

#define nuberofbodies 700



class Simulation
{
private:
    sf::RenderWindow& window_;
    sf::FloatRect windowBounds;
    Wing wing;
    Particle particles[nuberofbodies];
    /*Line normalLines[nuberofbodies];
    Line hittedLines[nuberofbodies];
    Line bounceLines[nuberofbodies];*/

public:
    //float minMagVec = 90000000.f; // if we will take the norm of diagonal vector of the window this norm will be less than 90000000.f  so we defined upper boundary
    int counterOfBounce = 0;

        
    // simulation frame 
    int left = 200;
    int width = 1300;
    int top = 200;
    int height = 700;


    Simulation(sf::RenderWindow& window);/* args */
    std::vector<sf::Vector2f> loadWindCords(char* name);
    void run(float sec);
    void physics();
    void update(float sec);

    void boundaries(Particle* particle);

    float rand_float(float maxValue);

    ~Simulation();
};

#endif // SIMULATION_HPP