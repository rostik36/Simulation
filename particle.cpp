#include "particle.hpp"

#include <iostream>


Particle::Particle(sf::Vector2f pos, float mass,sf::Color color, int numberOfParticles ): pos_(pos), mass_(mass){
    //shape.setOrigin(radius_, radius_);

    isInCollision = new bool[numberOfParticles];
    for (size_t i = 0; i < numberOfParticles; i++)
    {
        isInCollision[i] = false;
    }
    

    shape = sf::RectangleShape(sf::Vector2f(3.f,3.f));
    //radius_ = 3;
    //radiusPow2 = radius_*radius_;
    //shape.setSize(sf::Vector2f(0,0));
    shape.setFillColor(color);
    shape.setPosition(pos_);
    velocity_ = sf::Vector2f(0.f,0.f);
    acceleration_ = sf::Vector2f(0.f,0.f);
}


void Particle::draw(sf::RenderTarget& target, sf::RenderStates states) const  {
    target.draw(shape, states);
}


void Particle::setPos(sf::Vector2f pos) {
  pos_ = pos;
  shape.setPosition(pos_);
}


void Particle::run(float sec) {
    velocity_ += acceleration_*sec;//(particles[i].getVelocity()+particles[i].getAcceleration());
    setPos(pos_ + velocity_*sec); 

    /*if(shape.getFillColor() == sf::Color::Green){
        std::cout<<"acc :";
        std::cout<<acceleration_.x<<","<<acceleration_.y;
        std::cout<<"\n";
        std::cout<<"vec :";
        std::cout<<velocity_.x<<","<<velocity_.y;
        std::cout<<"\n";
        std::cout<<"pos :";
        std::cout<<pos_.x<<","<<pos_.y;
        std::cout<<"\n";
    }*/
}


void Particle::attract(Particle& body){
    float forceMagnitude = 6.674e-11 * mass_ * body.getMass() / distancePaw2(body.getPos()); // G*m1*m2 / r_magnitude^2
    float accelerationMagnitude_Particle1 = forceMagnitude / mass_; // f_magnitude / m1
    float accelerationMagnitude_Particle2 = forceMagnitude / body.getMass(); // f_magnitude / m2
    sf::Vector2f forceDirection = (body.getPos()-pos_).normalize(); // r/|r|  give the direction of the force
    acceleration_ += accelerationMagnitude_Particle1 * forceDirection; // accelerationMagnitude_Particle1 * forceDirection(in this case acceleration direction)
    body.setAcceleration(body.getAcceleration() - accelerationMagnitude_Particle2 * forceDirection); // accelerationMagnitude_Particle2 * forceDirection(in this case acceleration direction)
}



std::vector<Line*> Particle::intersects(std::vector<Line*>* path, bool* isInside){ //bool Particle::intersects(std::vector<Line>& path){
    int intersections = 0;
    std::vector<Line*> lines;
    
    for (size_t i = 0; i < path->size(); i++)
    {
        if( (*(*path)[i]).getPoint1().x <= pos_.x && pos_.x <= (*(*path)[i]).getPoint2().x ){ // point1.x <= point2.x
            /*if( path[i].getPoint1().y <= pos_.y || path[i].getPoint2().y <= pos_.y){ // the particle in under the line
                intersections++;
                lines.push_back(path[i]);
            }*/
            lines.push_back((*path)[i]); // on the y axis intersects with this line

            float intersect_y = (*(*path)[i]).getSlope()*( pos_.x - (*(*path)[i]).getPoint1().x) + (*(*path)[i]).getPoint1().y;  // y = m( x - x1 ) + y1    <-  y - y1 = m( x - x1 )    one of the line points (x1,y1), m - line slope

            if(intersect_y <= pos_.y){
                *isInside=!(*isInside);
                //intersections++;
            }
        }
    }
    //std::cout<<"up inter: "<<intersections<<"\n";
    // check if there is intersections
    // no - return false;
    // yes - if number is odd       intersections % 2
    //       yes - return true      result
    //       no - return false      result

    //return intersections ? intersections%2 : false;
    //std::cout<<lines.size()<<"\n";
    return lines; /// return all the lines that are intersecting
}




sf::Vector2f Particle::vectorToClosestPointOnLine(Line* line){
    // Calculate the vector from the line start to the point
    sf::Vector2f lineVec = (*line).getPoint2() - (*line).getPoint1();
    sf::Vector2f pointVec = pos_ - (*line).getPoint1();

    // Project the point vector onto the line vector
    //float proj = (pointVec.x * lineVec.x + pointVec.y * lineVec.y) / (lineVec.x * lineVec.x + lineVec.y * lineVec.y);
    float proj = pointVec.dot(lineVec) / lineVec.normPow2();
    proj = std::max(0.f, std::min(1.f, proj)); // Clamp the projection value between 0 and 1

    // Calculate the closest point on the line
    sf::Vector2f closest = (*line).getPoint1() + proj * lineVec;
    return  closest - pos_;
    //std::cout<<"    try to calculate point on line :  ("<<line.getPoint1().x<<","<<line.getPoint1().y<<")---("<<line.getPoint2().x<<","<<line.getPoint2().y<<")\n";
    
    // Calculate the y-intercept of the line
    /*float yIntercept = line.getPoint1().y - line.getSlope() * line.getPoint1().x;

    // Calculate the slope and y-intercept of the line perpendicular to the given line
    float perpSlope = -1.f / line.getSlope();
    float perpYIntercept = pos_.y - perpSlope * pos_.x;

    // Calculate the x and y coordinates of the closest point on the given line
    float x = (perpYIntercept - yIntercept) / (line.getSlope() - perpSlope);
    float y = line.getSlope() * x + yIntercept;

    // Create a vector from the calculated coordinates
    sf::Vector2f closestPoint(x, y);
    return closestPoint - pos_;*/
}



void Particle::elasticCollision(Particle* particle){
        // calculate the unit normal and unit tangent vectors
        // creating new "grid" with new center and y, x axis directions
        sf::Vector2f n = sf::Vector2f(pos_ - (*particle).getPos()).normalize(); // direction vector  -  from one body to another
        sf::Vector2f t = sf::Vector2f(-n.y, n.x);                        // vector perpendicular to direction vector
        
        // calculate the initial velocities in the normal and tangent directions
        float v1n = dot(velocity_, n);
        float v1t = dot(velocity_, t);
        float v2n = dot((*particle).getVelocity(), n);
        float v2t = dot((*particle).getVelocity(), t);
        
        // calculate the final velocities in the normal direction
        float m1 = mass_;
        float m2 = (*particle).getMass();
        float v1n_final = (v1n * (m1 - m2) + 2 * m2 * v2n) / (m1 + m2);
        float v2n_final = (v2n * (m2 - m1) + 2 * m1 * v1n) / (m1 + m2);
        
        // set the final velocities for the objects
        //velocity_ = sf::Vector2f(0,0);//v1n_final * n + v1t * t;
        //body.setVelocity(sf::Vector2f(0,0));//v2n_final * n + v2t * t);
        velocity_new += (v1n_final * n + v1t * t);//*0.f;
        (*particle).setVelocityNew((*particle).getVelocityNew()+ (v2n_final * n + v2t * t));//*0.f);



        // reset the position so the object gets right about the edge out of collision..
        // Assume obj1 and obj2 are instances of some class with a position property (e.g. sf::Vector2f)
        // Calculate the center point between the two objects
        /*sf::Vector2f center = (pos_ + body.getPos()) / 2.f;

        // Calculate the direction from obj1 to obj2
        sf::Vector2f direction = (body.getPos() - pos_).normalize();
        
        // Calculate the new positions for obj1 and obj2
        float distance = (getRadius()+body.getRadius() +0.00002f) / 2.f; // Half the desired distance between the objects
        sf::Vector2f new1 = center - direction * distance;
        sf::Vector2f new2 = center + direction * distance;

        // Set the new positions for obj1 and obj2
        pos_= new1;
        body.setPos(new2);*/
}



void Particle::correct(Particle& body){
    // reset the position so the object gets right about the edge out of collision..
    // Assume obj1 and obj2 are instances of some class with a position property (e.g. sf::Vector2f)
    // Calculate the center point between the two objects
    sf::Vector2f center = (pos_ + body.getPos()) / 2.f;

    // Calculate the direction from obj1 to obj2
    sf::Vector2f direction = body.getPos() - pos_;
    float distance = direction.norm();
    direction = direction.normalize();
    

    // Calculate the new positions for obj1 and obj2
    float halfTheDistance = (distance + 0.0000002f) / 2.f; // Half the desired distance between the objects
    sf::Vector2f new1 = center - direction * halfTheDistance;
    sf::Vector2f new2 = center + direction * halfTheDistance;

    // Set the new positions for obj1 and obj2
    pos_= new1;
    body.setPos(new2);
}