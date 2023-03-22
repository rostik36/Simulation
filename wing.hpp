#ifndef WING_HPP
#define WING_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>
#include "line.hpp"
#include <vector>

class Wing : public sf::Drawable{
    public:
    sf::Vector2f& pos_;
    float scale_;
    
    //bool isInCollisionN = false;
    
    //bool isInCollision[50] = {false};
    

    Wing(sf::Vector2f pos, std::vector<sf::Vector2f*> pathPoints, float, sf::Color color);

    void setOrigin();
    
    std::vector<Line*>* getPath(){
        return &path;
    }

    ~Wing();


    private:
    std::vector<sf::Vector2f*> pathPoints_;
    std::vector<Line*> path; // the path that defines the wing shape 
    //std::vector<Body> origins;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // WING_HPP