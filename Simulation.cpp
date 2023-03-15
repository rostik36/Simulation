
#include "Simulation.hpp"
#include <iostream>
/* args */
Simulation::Simulation(sf::RenderWindow& window) : window_(window) {
    sf::Vector2f pos(300.f, 250.f);
    particles[0] = Body(pos, 100000000000.f, sf::Color::Green);
    particles[0].setVelocity(sf::Vector2f(-1.f,0.1f));
    sf::Vector2f pos1(220.f, 150.f);
    particles[1] = Body(pos1, 120000000000.f,sf::Color::Red);

    sf::Vector2f pos2(220.f, 250.f);
    particles[2] = Body(pos2, 100000000000.f,sf::Color::Blue);


    
    // Assuming you have created a window named "window"
    windowBounds = sf::FloatRect(0-15, 0-15, window.getSize().x-15, window.getSize().y-15);
}

void Simulation::run(/* args */)
{
    
    
    update();
    physics();


    window_.clear();
    for(int i=0;i<nuberofbodies;i++)
        window_.draw(particles[i]);
    
    window_.display();
}

//using namespace std;

void Simulation::physics(){
    for(int i=0;i<nuberofbodies;i++){
        particles[i].setAcceleration(sf::Vector2f(0,0));
    }
    for(int i=0;i<nuberofbodies-1;i++){
        for(int j=i+1;j<nuberofbodies;j++){
            
            float forceMagnitude = 6.674e-11 * particles[i].getMass() * particles[j].getMass() / particles[i].distancePaw2(particles[j].getPos()); // G*m1*m2 / r_magnitude^2
            float accelerationMagnitude_Particle1 = forceMagnitude / particles[i].getMass(); // f_magnitude / m1
            float accelerationMagnitude_Particle2 = forceMagnitude / particles[j].getMass(); // f_magnitude / m2
            sf::Vector2f forceDirection = (particles[j].getPos()-particles[i].getPos()).normalize(); // r/|r|  give the direction of the force
            particles[i].setAcceleration(particles[i].getAcceleration() + accelerationMagnitude_Particle1 * forceDirection); // accelerationMagnitude_Particle1 * forceDirection(in this case acceleration direction)
            particles[j].setAcceleration(particles[j].getAcceleration() - accelerationMagnitude_Particle2 * forceDirection); // accelerationMagnitude_Particle2 * forceDirection(in this case acceleration direction)
        }
    }
}
void Simulation::update(){
    for(int i=0;i<nuberofbodies-1;i++){
        for(int j=i+1;j<nuberofbodies;j++){

            if(particles[i].isColliding( particles[j])){
                //std::cout <<"Collision";
                particles[i].elasticCollision(particles[j]);
            }
            else{
                //particles[i].setVelocity(particles[i].getVelocity()+particles[i].getAcceleration());
                //particles[i].setPos(particles[i].getPos()+particles[i].getVelocity());
                //particles[j].setVelocity(particles[j].getVelocity()+particles[j].getAcceleration());
                //particles[j].setPos(particles[j].getPos()+particles[j].getVelocity());
                particles[i].run();
                particles[j].run();
                //std::cout <<"not";
            }
            /*float vec = particles[i].getMass()*particles[j].getMass()/particles[i].distancePaw2(particles[j].getPos());
            float accParticle1 = vec/particles[i].getMass();
            sf::Vector2f diff = particles[j].getPos()-particles[i].getPos();
            particles[i].setAcceleration(diff.normalize()*accParticle1);*/
        }


        
        //std::cout <<particles[i].getPos().x;
        boundaries(particles[i]);
    }
    boundaries(particles[nuberofbodies-1]);
}

void Simulation::boundaries(Body& body)
{
    if( body.getPos().x - body.getRadius() <= windowBounds.left ){
        std::cout <<"left";
        sf::Vector2f normal(1.f,0);
        float d = 2.0f * body.getVelocity().dot(normal)/ normal.dot(normal);
        body.setVelocity( body.getVelocity() - d * normal);
    }
    else if (windowBounds.width <= body.getPos().x + body.getRadius())
    {
        std::cout <<"right";
        sf::Vector2f normal(-1.f,0);
        float d = 2.0f * body.getVelocity().dot(normal)/ normal.dot(normal);
        body.setVelocity( body.getVelocity() - d * normal);
    }
    else if ( body.getPos().y - body.getRadius() <= windowBounds.top)
    {
        std::cout <<"top";
        sf::Vector2f normal(0.f,-1.f);
        float d = 2.0f * body.getVelocity().dot(normal)/ normal.dot(normal);
        body.setVelocity( body.getVelocity() - d * normal);
    }
    else if (windowBounds.height <= body.getPos().y + body.getRadius())
    {
        std::cout <<"bottom";
        sf::Vector2f normal(0.f,1.f);
        float d = 2.0f * body.getVelocity().dot(normal)/ normal.dot(normal);
        body.setVelocity( body.getVelocity() - d * normal);
    }
    
    
}

Simulation::~Simulation()
{
}