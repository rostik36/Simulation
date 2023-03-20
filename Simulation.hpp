#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "wing.hpp"
#include "particle.hpp"
#include "line.hpp"



#define nuberofbodies 2500


class Simulation
{
public:
    //float minMagVec = 90000000.f; // if we will take the norm of diagonal vector of the window this norm will be less than 90000000.f  so we defined upper boundary
    int counterOfBounce = 0;

    // simulation frame 
    int left = 50;
    int width = 1700;
    int top = 100;
    int height = 900;

    float speed = 150;


    Simulation(sf::RenderWindow& window);
    std::vector<sf::Vector2f> loadWindCords(char* name);
    void run(float sec);
    void physics();
    void update(float sec);

    void boundaries(Particle* particle);

    float rand_float(float maxValue);
    sf::Vector2f generatePosNotColliding(float left, float top, float width, float height, int numberOfParticles);

    ~Simulation();


private:
    sf::RenderWindow& window_;
    sf::FloatRect windowBounds;
    Wing* wing;
    Particle* particles;
    
    //[nuberofbodies];
    /*Line normalLines[nuberofbodies];
    Line hittedLines[nuberofbodies];
    Line bounceLines[nuberofbodies];*/

};

#endif // SIMULATION_HPP