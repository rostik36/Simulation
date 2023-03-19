#ifndef LINE_HPP
#define LINE_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

#include <limits>

class Line : public sf::Drawable{
    public:
    bool isInCollisionN = false;
    bool isInCollision[50] = {false};

    






    Line();


    Line(sf::Vector2f pos , sf::Vector2f point1, sf::Vector2f point2, sf::Color color = sf::Color::White, bool print = false );



    sf::Vector2f getPoint1(){
        return point1_;
    }
    sf::Vector2f getPoint2(){
        return point2_;
    }

    sf::RectangleShape getLineShape() const {
        return shape;
    }
    sf::CircleShape getCenterPoint()const {
        return centerPoint;
    }

    sf::Vector2f getPos()const {
        return pos_;
    }

    void setPos(sf::Vector2f position) {
        sf::Vector2f dif = position - pos_;
        point1_=point1_+dif; 
        point2_=point2_+dif;
        pos_ = position;
        shape.setPosition(pos_); 
        centerPoint.setPosition(pos_);
    }


    float getSlope();



    private:
    sf::Vector2f pos_;
    sf::Vector2f point1_;
    sf::Vector2f point2_;
    sf::Color color_;
    sf::RectangleShape shape;
    sf::CircleShape centerPoint;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;    
};

#endif // LINE_HPP