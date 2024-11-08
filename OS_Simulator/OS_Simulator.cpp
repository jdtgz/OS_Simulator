// OS_Simulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>


void processEvents(sf::RenderWindow&);


int main()
{
    sf::RenderWindow window(sf::VideoMode(750, 800), "Scheduling Simulator", sf::Style::Titlebar | sf::Style::Close);
    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color::Green);
    shape.move(500.f, 500.f);

    while (window.isOpen())
    {
        processEvents(window);

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
    
}


void processEvents(sf::RenderWindow& w)
{ 
    sf::Event event;

    while (w.pollEvent(event))
    {
        // Use X botton on title bar to close window
        if (event.type == sf::Event::Closed)
            w.close();

        // Use escape to close application
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            w.close();
    }

    // Get position of mouse in accordance with window space 
    sf::Vector2i pos = sf::Mouse::getPosition(w);

    // Check to see mouse is in [circle position [500,550] for x and y
    if ((pos.x >= 500 && pos.x <= 600) && (pos.y >= 500 && pos.y <= 600))
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            std::cout << pos.x << " : " << pos.y << std::endl;
}