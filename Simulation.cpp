
#include "line.hpp"
#include "Simulation.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

std::vector<sf::Vector2f> Simulation::loadWindCords(char* name){
    std::string filePath = "C:\\Users\\Ros\\Desktop\\simulation\\";
    filePath += name;
    std::ifstream file(filePath);
    std::vector<sf::Vector2f> coords;

    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            float x, y;
            if (iss >> x >> y)
            {
                coords.push_back(sf::Vector2f(x, y));
                std::cout << x <<","<< y <<"'\n";
            }
        }
        file.close();
    }
    else
    {
        std::cout << "Error: could not open file." << std::endl;
    }

    return coords;
}


Simulation::Simulation(sf::RenderWindow& window) : window_(window) {
    
    std::vector<sf::Vector2f> cords = loadWindCords("wing.txt");

    wing = Wing(sf::Vector2f(550, 400), cords, 900.f, sf::Color::Red);
    sf::Clock clock1;

    for (size_t i = 1; i < nuberofbodies; i++)
    {
        //particles[i] = Particle(sf::Vector2f( 250+i*35 , 443.3f ), 1.f, sf::Color::Red);
        particles[i] = Particle(sf::Vector2f( left + 5 + static_cast<int>(clock1.getElapsedTime().asSeconds()*50000*11*i)%(width-left -5),  top + 5 + static_cast<int>(clock1.getElapsedTime().asSeconds()*50000*19*i)%(height - top -5) ), 1.f, sf::Color::Green);
        particles[i].setVelocity(sf::Vector2f(50.f,0));
    }
    particles[0] = Particle(sf::Vector2f( 350 , 443.3f ), 1.f, sf::Color::Red);
    particles[0].setVelocity(sf::Vector2f(40.f,0));


    //testLine = Line(sf::Vector2f(200,400), sf::Vector2f(-1,1), sf::Vector2f(1,-1), 1500, sf::Color::White);
    // Assuming you have created a window named "window"
    //windowBounds = sf::FloatRect(0-15, 0, window.getSize().x-15, window.getSize().y-132);
    windowBounds = sf::FloatRect(left, top, width, height);
}

void Simulation::run(float sec)
{
    update(sec);
    //physics();

    window_.clear();

    window_.draw(wing);

    for(size_t i=0;i<nuberofbodies;i++)
        window_.draw(particles[i]);

    for (size_t i = 0; i < counterOfBounce; i++)
    {
        window_.draw(normalLines[i]);
        //window_.draw(bounceLines[i]);
        //window_.draw(hittedLines[i]);
    }
    
    window_.display();
}


void Simulation::physics(){
    // zero acceleration to recalculate the new ones..
    /*for(int i=0;i<nuberofbodies;i++){
        particles[i].setAcceleration(sf::Vector2f(0.f,0.f));
    }

    // calculate the forces and the new acceleration for each body based on the forces
    for(int i=0;i<nuberofbodies-1;i++){
        for(int j=i+1;j<nuberofbodies;j++){
            particles[i].attract(particles[j]);
        }
    }*/
}



void Simulation::update(float sec){

    for(int i=0;i<nuberofbodies;i++){
        particles[i].setVelocityNew(sf::Vector2f(0.f,0.f));
    }
    
    for(int i=0;i<nuberofbodies-1;i++){
        for(int j=i+1;j<nuberofbodies;j++)
        {
            if(particles[i].isColliding( &particles[j])) // check to if the particles colliding
            {
                if(!particles[i].isInCollision[j] && !particles[j].isInCollision[i] )
                {
                    //std::cout <<"Collision"<<i<<","<<j<<"\n";
                    particles[i].elasticCollision(&particles[j]);
                    particles[i].isInCollision[j] = true;
                    particles[j].isInCollision[i] = true;
                }
                else{
                    //particles[i].correct( particles[j]);
                }
            }
            else{
                //std::cout <<"not"<<i<<"\n";
                particles[i].isInCollision[j] = false;
                particles[j].isInCollision[i] = false;
            }
        }
    }
    for(int i=0;i<nuberofbodies;i++){
        if(!particles[i].getVelocityNew().isZero())
            particles[i].setVelocity(particles[i].getVelocityNew());
    }



    // loop to check for collisions with the wing or the boundaries
    for(int i=0;i<nuberofbodies;i++){
        //if(particles[i].isRun){
        
        bool isInsideTheShape = false;
        //std::cout<<"initial  "<<isInsideTheShape<<"\n";
        std::vector<Line*> lines = particles[i].intersects(&wing.getPath(), &isInsideTheShape);

        //if(lines.size()>0)
        //    std::cout<<"some line "<< lines.size()<<"\n";

        if( isInsideTheShape ){ // so the particle entered into the wing area need to calculate the bounce back vector
            //std::cout<<"inside  "<<particles[i].getInside()<<"\n";
            if(!particles[i].getInside() ){ // if the particle not been inside the wing area so enter
                //std::cout<<"setted<<<<<<<<<\n";

                float minMagVec = 90000000.f; // the diagonal of the window is smaller so this starting value is ok
                sf::Vector2f dirVecToClosestPoint(90000000.0f,0);
                sf::Vector2f temp;
                //Line theLine;
                particles[i].setInside(true); // set the state of particle true - means inside the area
                //std::cout<<i<<"   Number of lines intersects:         "<<lines.size()<<"\n\n";
                for (size_t j = 0; j < lines.size(); j++)
                {
                    temp = particles[i].vectorToClosestPointOnLine(lines[j]); // returned vector from particle pos to the closest point on the line
                    //( means this vector perpendicular to the line)
                    float tempNormPow2 = temp.normPow2();
                    //std::cout<<"    "<<tempNormPow2<<": "<<temp.x<<","<<temp.y<<"\n";
                    //std::cout<<"    "<<i<<" line :  ("<<(*lines[j]).getPoint1().x<<","<<(*lines[j]).getPoint1().y<<")---("<<(*lines[j]).getPoint2().x<<","<<(*lines[j]).getPoint2().y<<")\n";
                    //std::cout<<"calculate vec "<<temp.x<<","<<temp.y<<"\n\n";
                
                    
                    if(tempNormPow2 < minMagVec)
                    {
                        //std::cout<<"    Setted line :  ("<<(*lines[j]).getPoint1().x<<","<<(*lines[j]).getPoint1().y<<")---("<<(*lines[j]).getPoint2().x<<","<<(*lines[j]).getPoint2().y<<")  <<<<<\n\n";
                        sf::Vector2f dir = (*lines[j]).getPoint2()-(*lines[j]).getPoint1();
                        dirVecToClosestPoint = sf::Vector2f(-dir.y, dir.x);
                        minMagVec = tempNormPow2;
                        //std::cout<<i<<"\n";
                        hittedLines[i] = Line((*lines[j]).getPos(), (*lines[j]).getPoint1(), (*lines[j]).getPoint2(), sf::Color::Red );
                        hittedLines[i].setPos(hittedLines[i].getPos()+sf::Vector2f(0,10.f));
                    }
                }
                //particles[i].isRun = false;

                //std::cout<<i<<">> bounce of line: ("<<hittedLines[i].getPoint1().x<<","<<hittedLines[i].getPoint1().y<<") --- ("<<hittedLines[i].getPoint2().x<<","<<hittedLines[i].getPoint2().y<<")\n\n";
            
                //std::cout<<"dir: "<<dirVecToClosestPoint.x<<","<<dirVecToClosestPoint.y<<"\n";
                /*float d = 2.0f * particles[i].getVelocity().dot(dirVecToClosestPoint.normalize());  /// dirVecToClosestPoint.dot(dirVecToClosestPoint);
                sf::Vector2f bounceVec = particles[i].getVelocity() - d * dirVecToClosestPoint.normalize();
                particles[i].setVelocity( bounceVec);*/
                particles[i].setVelocity( particles[i].getVelocity().reflect(dirVecToClosestPoint.normalize()));

                //sf::Vector2f dir = lines[j].getPoint2()-lines[j].getPoint1();
                /*sf::Vector2f ferlected = particles[i].getVelocity().reflect(dirVecToClosestPoint);

                Line normal( (particles[i].getPos()+ particles[i].getPos()+(50.f*dirVecToClosestPoint))/2.f, particles[i].getPos()+(50.f*dirVecToClosestPoint), particles[i].getPos(), sf::Color::White, false );
                normalLines[counterOfBounce] = normal;

                Line reflectedd( (particles[i].getPos()+ particles[i].getPos()+(50.f*ferlected))/2.f, particles[i].getPos()+(50.f*ferlected), particles[i].getPos(), sf::Color::Cyan, false );
                bounceLines[counterOfBounce++] = reflectedd;  //particles[i].isInCollisionLeftEdge = true;
                */
            }
        }
        else{ // set particle out of the wing area
            //std::cout<<">>>>>>>>>.out\n";
            particles[i].setInside(false);
        }
        //}
        boundaries(&particles[i]);


        // move the body based on calculated variables
        particles[i].run(sec);
    }
    
    /*for(int i=0;i<nuberofbodies;i++){
        boundaries(particles[i]);
        //if(particles[i].isRun)
            
            
    }*/
}


void Simulation::boundaries(Particle* particle)
{
    if( (*particle).getPos().x - (*particle).getRadius() <= windowBounds.left ){
        if(!(*particle).isInCollisionLeftEdge){
            std::cout <<"left\n";
            sf::Vector2f normal(1.f,0);
            float d = 2.0f * (*particle).getVelocity().dot(normal)/ normal.normPow2();
            (*particle).setVelocity( (*particle).getVelocity() + d * normal);
            (*particle).isInCollisionLeftEdge = true;
            sf::Vector2f fin = (*particle).getVelocity() + d * normal;
            std::cout <<fin.x<<","<<fin.y<<"\n\n";
        }
        
    }
    else
        (*particle).isInCollisionLeftEdge = false;

    if (windowBounds.width <= (*particle).getPos().x + (*particle).getRadius())
    {
        /*if(!(*particle).isInCollisionRightEdge){
            //std::cout <<"right";
            sf::Vector2f normal(-1.f,0);
            float d = 2.0f * (*particle).getVelocity().dot(normal)/ normal.normPow2();
            (*particle).setVelocity( (*particle).getVelocity() - d * normal);
            (*particle).isInCollisionRightEdge = true;
        }
        */
        // in this case teleport the particle to start to left corner..
        (*particle).setPos( sf::Vector2f(205, 200+ rand_float(500)) );
        (*particle).setVelocity(sf::Vector2f(50.f,0));
    }
    else
        (*particle).isInCollisionRightEdge = false;

    if ( (*particle).getPos().y - (*particle).getRadius() <= windowBounds.top)
    {
        if(!(*particle).isInCollisionTopEdge){
            //std::cout <<"top";
            sf::Vector2f normal(0.f,-1.f);
            float d = 2.0f * (*particle).getVelocity().dot(normal)/ normal.normPow2();
            (*particle).setVelocity( (*particle).getVelocity() - d * normal);
            (*particle).isInCollisionTopEdge = true;
        }

    }
    else
        (*particle).isInCollisionTopEdge = false;

    
    if (windowBounds.height <= (*particle).getPos().y + (*particle).getRadius())
    {
        if(!(*particle).isInCollisionBottomEdge){
            //std::cout <<"bottom";
            sf::Vector2f normal(0.f,1.f);
            float d = 2.0f * (*particle).getVelocity().dot(normal)/ normal.normPow2();
            (*particle).setVelocity( (*particle).getVelocity() - d * normal);
            (*particle).isInCollisionBottomEdge = true;
        }
        //std::cout<<"vec :";
        //std::cout<<body.getVelocity().x<<","<<body.getVelocity().y;
        //std::cout<<"\n";
    }
    else
        (*particle).isInCollisionBottomEdge = false;
}


float Simulation::rand_float(float maxValue) {
    // Generate a random integer between 0 and RAND_MAX
    int rand_int = rand();

    // Scale the integer to a float between 0 and 10
    float rand_float = (float(rand_int) / RAND_MAX )* maxValue;
    
    return rand_float;
}


Simulation::~Simulation()
{
}