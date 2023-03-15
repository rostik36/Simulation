#include "body.hpp"
#include <iostream>

Body::Body(sf::Vector2f pos, float mass,sf::Color color ): pos_(pos), mass_(mass){
    shape.setRadius(7.f);// = new sf::CircleShape(5.f);
    shape.setFillColor(color);
    shape.setPosition(pos_);
    velocity_ = sf::Vector2f(0,0);
    acceleration_ = sf::Vector2f(0,0);
}



void Body::draw(sf::RenderTarget& target, sf::RenderStates states) const  {
    target.draw(shape, states);
}

void Body::setPos(sf::Vector2f pos) {
  pos_ = pos;

  shape.setPosition(pos_);
}

void Body::run() {
    velocity_+=acceleration_;//(particles[i].getVelocity()+particles[i].getAcceleration());
    setPos(pos_+velocity_);
}


void Body::attract(Body& body){
    float forceMagnitude = 6.674e-11 * mass_ * body.getMass() / particles[i].distancePaw2(particles[j].getPos()); // G*m1*m2 / r_magnitude^2
    float accelerationMagnitude_Particle1 = forceMagnitude / particles[i].getMass(); // f_magnitude / m1
    float accelerationMagnitude_Particle2 = forceMagnitude / particles[j].getMass(); // f_magnitude / m2
    sf::Vector2f forceDirection = (particles[j].getPos()-particles[i].getPos()).normalize(); // r/|r|  give the direction of the force
    particles[i].setAcceleration(particles[i].getAcceleration() + accelerationMagnitude_Particle1 * forceDirection); // accelerationMagnitude_Particle1 * forceDirection(in this case acceleration direction)
    particles[j].setAcceleration(particles[j].getAcceleration() - accelerationMagnitude_Particle2 * forceDirection); // accelerationMagnitude_Particle2 * forceDirection(in this case acceleration direction)
}


void Body::elasticCollision(Body& body){
        // calculate the unit normal and unit tangent vectors
        sf::Vector2f n = sf::Vector2f(pos_ - body.getPos()).normalize();
        sf::Vector2f t = sf::Vector2f(-n.y, n.x);
        //std::cout <<n.x;
        //std::cout <<n.y;
        // calculate the initial velocities in the normal and tangent directions
        float v1n = dot(velocity_, n);
        float v1t = dot(velocity_, t);
        float v2n = dot(body.getVelocity(), n);
        float v2t = dot(body.getVelocity(), t);
        
        // calculate the final velocities in the normal direction
        float m1 = mass_;
        float m2 = body.getMass();
        float v1n_final = (v1n * (m1 - m2) + 2 * m2 * v2n) / (m1 + m2);
        float v2n_final = (v2n * (m2 - m1) + 2 * m1 * v1n) / (m1 + m2);
        
        // set the final velocities for the objects
        //velocity_ = sf::Vector2f(0,0);//v1n_final * n + v1t * t;
        //body.setVelocity(sf::Vector2f(0,0));//v2n_final * n + v2t * t);
        velocity_ = (v1n_final * n + v1t * t)*0.9f;
        body.setVelocity((v2n_final * n + v2t * t)*0.9f);



        // reset the position so the object gets right about the edge out of collision..
        // Assume obj1 and obj2 are instances of some class with a position property (e.g. sf::Vector2f)
        // Calculate the center point between the two objects
        sf::Vector2f center = (pos_ + body.getPos()) / 2.f;

        // Calculate the direction from obj1 to obj2
        sf::Vector2f direction = body.getPos() - pos_;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= length; // Normalize the direction vector

        // Calculate the new positions for obj1 and obj2
        float distance = (getRadius()+body.getRadius() +0.00002f) / 2.f; // Half the desired distance between the objects
        sf::Vector2f new1 = center - direction * distance;
        sf::Vector2f new2 = center + direction * distance;

        // Set the new positions for obj1 and obj2
        pos_= new1;
        body.setPos(new2);
}
    // check if the two rectangles are colliding
    //if (rect1.getGlobalBounds().intersects(rect2.getGlobalBounds()))
    //{