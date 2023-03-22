#include "wing.hpp"
#include <iostream>



Wing::Wing(sf::Vector2f pos, std::vector<sf::Vector2f*> pathPoints, float scale, sf::Color color):pos_(pos), pathPoints_(pathPoints), scale_(scale){
    
    // create the path line and scale them, so the wing will be in scale of [scale]
    // the pathPoints is in range of -1 to 1  x and y coordinate so wi scale them and add them to position
    for (size_t i = 0; i < pathPoints_.size()-1;i++)
    {
        sf::Vector2f offsetPnt1 = *(pathPoints[i])*scale;              // prev point
        sf::Vector2f offsetPnt2 = *(pathPoints[i+1])*scale;            // next prev
        sf::Vector2f offsetFromOrigin = (offsetPnt1+offsetPnt2)/2.f;// the point in the middle of wing
        
        // create line in pos and add the offset offsetFromOrigin
        //Line line( pos_ + offsetFromOrigin , pos_+ offsetPnt1, pos_+ offsetPnt2, sf::Color::Red);
        path.push_back( new Line( pos_ + offsetFromOrigin , pos_+ offsetPnt1, pos_+ offsetPnt2, sf::Color::Red) );//line);
    }
}


void Wing::draw(sf::RenderTarget& target, sf::RenderStates states) const  {
    for (size_t i = 0; i < path.size(); i++){
        target.draw((*path[i]).getCenterPoint(), states);
    }
    for (size_t i = 0; i < path.size(); i++){
        target.draw((*path[i]).getLineShape(), states);
    }
}


Wing::~Wing(){
    // Deallocate memory for the objects pointed to by the pointers
    for (auto point : pathPoints_) {
        delete point;
    }
    pathPoints_.clear();
    path.clear();
    //delete[] isInCollision;
}