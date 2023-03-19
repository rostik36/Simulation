#include "line.hpp"
#include <iostream>

Line::Line(){}


 

Line::Line(sf::Vector2f pos , sf::Vector2f point1, sf::Vector2f point2 , sf::Color color, bool print ):pos_(pos), point1_(point1), point2_(point2), color_(color){
    
    // we want point1 x coordinate to be always smaller than point2 x coordinate, for later use to check intersections
    if(point1_.x > point2_.x){
        sf::Vector2f temp = point1_;
        point1_ = point2_;
        point2_ = temp;
    }

    sf::Vector2f dir(point2_-point1_);
    if(print)
        std::cout<<"  line: ("<<point1_.x<<","<<point1_.y<<") --- ("<<point2_.x<<","<<point2_.y<<")\n";
        
    float size = dir.norm();
    shape = sf::RectangleShape(sf::Vector2f(size, 0));
    //shape.setSize(sf::Vector2f(size, 0));
    shape.setOutlineColor(color_);
    shape.setOutlineThickness(1);
    shape.setOrigin(size/2.f, 0);                               // the origin of the line will be in the middle of it
    shape.setRotation(std::atan2(dir.y, dir.x) * 180 / M_PI);   // rotate to the angle of the direction
    shape.setPosition(pos_);                                    // the position will be in the center of the line (because we mover the origin to the center)

    float radius = 3.f;
    centerPoint = sf::CircleShape(radius);
    centerPoint.setFillColor(sf::Color::Blue);
    centerPoint.setOrigin(radius, radius);            // the origin of the circle will be in the middle of it
    centerPoint.setPosition(pos_);
}


void Line::draw(sf::RenderTarget& target, sf::RenderStates states) const  {
    target.draw(centerPoint, states);
    target.draw(shape, states);
}


float Line::getSlope() {
    //std::cout<<point2_.x<<","<<point1_.x<<"\n";
    float x_dif = point2_.x - point1_.x;
    if(x_dif != 0 )
        return (point2_.y-point1_.y)/x_dif;
    return 1000000000000;
        //return (point2_.x-point1_.x) !=0 ? (point2_.y-point1_.y)/(point2_.x-point1_.x) : std::numeric_limits<float>::max();
}