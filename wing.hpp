#ifndef WING_HPP
#define WING_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>
//#include <SFML/Graphics/RectangleShape.hpp>
//#include "body.hpp"
#include "line.hpp"
#include <vector>

class Wing : public sf::Drawable{
    public:
    sf::Vector2f pos_;
    bool isInCollisionN = false;
    bool isInCollision[50] = {false};
    float scale_;

    Wing(sf::Vector2f pos = sf::Vector2f(0, 0), std::vector<sf::Vector2f> pathPoints = {sf::Vector2f(0, 0)}, float size = 1, sf::Color color = sf::Color::Green );

    void setOrigin();
    
    std::vector<Line>& getPath(){
        return path;
    }



    private:
    std::vector<sf::Vector2f> pathPoints_;
    std::vector<Line> path;
    //std::vector<Body> origins;


    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // WING_HPP