//#pragma once
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <cmath>


class Body : public sf::Drawable{
    public:
    bool isInCollisionN = false;
    bool isInCollision[50] = {false};
    bool isInCollisionLeftEdge = false;
    bool isInCollisionRightEdge = false;
    bool isInCollisionTopEdge = false;
    bool isInCollisionBottomEdge = false;

    Body(sf::Vector2f pos = sf::Vector2f(0, 0), float radius = 0, float mass = 0.f,sf::Color color = sf::Color::Green );

    void setPosition(sf::Vector2f pos);
    void run(float sec);


    sf::CircleShape getShape() {
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
    sf::Vector2f& getVelocityPaw2()  {
        return velocity_*velocity_;
    }
    void setVelocity(sf::Vector2f velocity) {
        velocity_ = velocity;
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

    void correct(Body& body);

    private:
    
    sf::Vector2f pos_;
    sf::Vector2f velocity_;
    sf::Vector2f velocity_new;
    sf::Vector2f acceleration_;
    float radius_;
    float mass_;
    sf::CircleShape shape;




    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
};