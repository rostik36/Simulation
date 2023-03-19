#include "wing.hpp"
#include <iostream>



Wing::Wing(sf::Vector2f pos, std::vector<sf::Vector2f> pathPoints, float scale, sf::Color color):pos_(pos), pathPoints_(pathPoints), scale_(scale){
    for (size_t i = 0; i < pathPoints_.size()-1;i++)
    {
        sf::Vector2f offsetPnt1 = pathPoints[i]*scale;
        sf::Vector2f offsetPnt2 = pathPoints[i+1]*scale;
        sf::Vector2f offsetFromOrigin = (offsetPnt1+offsetPnt2)/2.f;//(pathPoints[i+1]+pathPoints[i])*(scale/2.f);  //   ( point1 + point2  ) / 2  - >    the point in the middle
        
        Line line( pos_ + offsetFromOrigin , pos_+ offsetPnt1, pos_+ offsetPnt2, sf::Color::Red);
        path.push_back(line);
    }
}
        
    /*sf::RectangleShape rectangle;
    sf::Vector2f dir = pathPoints[i+1]-pathPoints[i];
    float distance = dir.norm();
    float size = distance*scale;*/

    //  - > *scale give the point from origin for scaled wing

    /*rectangle.setSize(sf::Vector2f(size, 0));
    rectangle.setOutlineColor(sf::Color::Red);
    rectangle.setOutlineThickness(1);
    rectangle.setOrigin(size/2.f, 0);
    //rectangle.setPosition(pos + offsetFromOrigin );
    rectangle.setRotation(std::atan2(dir.y, dir.x) * 180 / M_PI); // rotate to the angle of the direction
    //path.push_back(rectangle);*/

    //origins.push_back( Body(pos + offsetFromOrigin, 3.f, 1.f, sf::Color::Green) ); // point in the center of the line


void Wing::draw(sf::RenderTarget& target, sf::RenderStates states) const  {
    for (size_t i = 0; i < path.size(); i++){
        target.draw(path[i].getCenterPoint(), states);
    }
    for (size_t i = 0; i < path.size(); i++){
        target.draw(path[i].getLineShape(), states);
    }
}
