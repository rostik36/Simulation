/*sf::Vector2f pos(300.f, 250.f);
    //particles[0] = Body(pos, 10000000000.f, sf::Color::Green);
    //particles[0].setVelocity(sf::Vector2f(-1.f,0.4f));
    sf::Vector2f pos1(220.f, 150.f);
    //particles[1] = Body(pos1, 100000000000.f,sf::Color::Red);

    sf::Vector2f pos2(220.f, 250.f);
    //particles[2] = Body(pos2, 1000000000.f,sf::Color::Blue);

    for(int i=0;i<nuberofbodies-1;i++){
        particles[i] = Body(sf::Vector2f(i*20+1, 250.f+i*20), 100000000000000000.f,sf::Color::Blue);
        particles[i].setAcceleration(sf::Vector2f(0.f, 9.f));
    }
    particles[nuberofbodies-1] = Body(sf::Vector2f(500.f, 500.f), 10000000000000000000.f,sf::Color::Green);
    particles[nuberofbodies-1].setAcceleration(sf::Vector2f(0.f, 9.f));
    */
/*
    float start_x = 500.f;
    float start_y = 500.f;
    
    float edge = 200.f;

    float x_center = start_x + edge/2;
    float y_center = start_y - ((std::sqrt(3)/2.f)*edge)/3.f;

    sf::Vector2f center(x_center,y_center);


    sf::Vector2f pos(start_x, start_y);
    particles[0] = Body(pos, 100000000000000000.f, sf::Color::Green);
    //particles[0].setVelocity((center-pos).normalize()*1.f);

    sf::Vector2f pos1(start_x + edge, start_y);
    particles[1] = Body(pos1, 100000000000000000.f,sf::Color::Red);
    //particles[1].setVelocity((center-pos1).normalize()*1.f);
    

    sf::Vector2f pos2(start_x + edge/2, start_y - (std::sqrt(3)/2)*edge );
    particles[2] = Body(pos2, 100000000000000000.f,sf::Color::Blue);
    //particles[2].setVelocity((center-pos2).normalize()*1.f);
*/