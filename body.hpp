//#pragma once

#include <SFML/Graphics.hpp>

#include <cmath>


class Body : public sf::Drawable{
    public:
    
    Body(sf::Vector2f pos = sf::Vector2f(0, 0), float mass = 0.f,sf::Color color = sf::Color::Green );

    void setPosition(sf::Vector2f pos);
    void run();

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
    sf::Vector2f& getVelocityPaw2()  {
        return velocity_*velocity_;
    }
    void setVelocity(sf::Vector2f velocity) {
        velocity_ = velocity;
    }
    sf::Vector2f getAcceleration()  {
        return acceleration_;
    }
    void setAcceleration(sf::Vector2f acceleration) {
        acceleration_ = acceleration;
    }

    float distance(sf::Vector2f& v2) {
        float dx = v2.x - pos_.x;
        float dy = v2.y - pos_.y;
        return std::sqrt(dx*dx + dy*dy);
    }
    float distancePaw2(sf::Vector2f& v2) {
        float dx = v2.x - pos_.x;
        float dy = v2.y - pos_.y;
        return dx*dx + dy*dy;
    }
    
    float dot(sf::Vector2f v1, sf::Vector2f v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }

    float getRadius() {
        return shape.getRadius();
    }

    bool isColliding(Body& body){
        return shape.getRadius()+body.getRadius() >  distance(body.getPos());
    }


    void attract(Body& body);

    //m1*v1^2+m2*v2^2=m1*u1^2+m2*u2^2
    //v1-v2 = - (u1-u2);
    
    // (m1*v1^2+m2*v2^2 -m2*u2^2 ) / m1 = u1^2
    // v1-v2 + u1 = u2

    //(m1*v1^2+m2*v2^2 -m2*(v1-v2 + u1)^2 ) / m1 = u1^2
    void elasticCollision(Body& body);

    private:
    sf::Vector2f pos_;
    sf::Vector2f velocity_;
    sf::Vector2f acceleration_;
    float mass_;
    sf::CircleShape shape;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
};