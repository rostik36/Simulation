#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include "line.hpp"
#include <cmath>

static float radius_ = 1.5;
static float collisionWithOtherParticleDistance = 2*radius_;
static float collisionWithOtherParticleDistancePow2 = collisionWithOtherParticleDistance*collisionWithOtherParticleDistance;

class Particle : public sf::Drawable{
    public:
    bool isRun = true;
    bool isInCollisionN = false;
    bool* isInCollision;//[2000] = {false};
    bool isInCollisionLeftEdge = false;
    bool isInCollisionRightEdge = false;
    bool isInCollisionTopEdge = false;
    bool isInCollisionBottomEdge = false;

    
    Particle(sf::Vector2f pos = sf::Vector2f(0, 0), float mass = 0.f,sf::Color color = sf::Color::Green, int numberOfParticles = 0 );

    void setPosition(sf::Vector2f pos);
    void run(float sec);


    sf::RectangleShape getShape() {
        return shape;
    }

    sf::Vector2f& getPos()  {
        return pos_;
    }
    void setPos(sf::Vector2f pos);


    float getMass()  {
        return mass_;
    }
    void setMass(float mass) {
        mass_ = mass;
    }


    sf::Vector2f getVelocity()  {
        return velocity_;
    }
    void setVelocity(sf::Vector2f velocity) {
        velocity_ = velocity;
    }
    sf::Vector2f& getVelocityPaw2()  {
        return velocity_*velocity_;
    }


    sf::Vector2f getVelocityNew()  {
        return velocity_new;
    }
    void setVelocityNew(sf::Vector2f velocity) {
        velocity_new = velocity;
    }


    sf::Vector2f getAcceleration()  {
        return acceleration_;
    }
    void setAcceleration(sf::Vector2f acceleration) {
        acceleration_ = acceleration;
    }

    
    float dot(sf::Vector2f v1, sf::Vector2f v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }

    float distancePaw2(sf::Vector2f& v2) {
        float dx = v2.x - pos_.x;
        float dy = v2.y - pos_.y;
        return dx*dx + dy*dy;
    }

    float getRadius(){
        return radius_;
    }

    void attract(Particle& body);



    /**
     * @brief check if the particle is inside the wing area,
     * wing path is closed circle using this fact, will use the algorithm to check if the particle is inside the polygon(in this case the wing path)
     * counting the number of intersections with the path lines
     * 
     * @param path 
     * @return true - particle inside the wing area
     * @return false - outside
     */
    std::vector<Line*> intersects(std::vector<Line>* path, bool* isInside);//bool intersects(std::vector<Line>& path);
    
    sf::Vector2f vectorToClosestPointOnLine(Line* line);


    bool isColliding(Particle* particle){
        return (pos_- (*particle).getPos()).normPow2() <  collisionWithOtherParticleDistancePow2;
    }

    void elasticCollision(Particle* body);

    void correct(Particle& body);

    bool getInside(){
        return isInside;
    }
    void setInside(bool value){
        isInside = value;
    }

    /*float getRadiusPow2(){
        return radiusPow2;
    }*/


    private:
    sf::Vector2f pos_;
    sf::Vector2f velocity_;
    sf::Vector2f velocity_new;
    sf::Vector2f acceleration_;
    float mass_;
    sf::RectangleShape shape;
    

    bool isInside = false;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


#endif // PARTICLE_HPP