#include "Simulator.h"


Simulator::Simulator()
{
	window = new sf::RenderWindow(sf::VideoMode(1000, 1000), "Scheduling Simulator", 
									sf::Style::Titlebar | sf::Style::Close);
    menu1 = new sf::RenderWindow();
    
    // Initialize demo popUp input box
    popUp.setSize(sf::Vector2f(100.f, 50.f));
    popUp.setFillColor(sf::Color::White);
    popUp.move(5.f, 5.f);
}


Simulator::~Simulator()
{
	delete window;
    delete menu1;
}


void Simulator::run()
{
	while (window->isOpen())
	{
		processEvents();
		update();
        render();
	}
}


void Simulator::processEvents()
{
    sf::Event event;
    sf::Vector2i pos;

    while (window->pollEvent(event))
    {
        // Use escape to close application
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window->close();

        // Get position of mouse in accordance with window space 
        pos = sf::Mouse::getPosition(*window);

        // Check to see mouse is in [circle position [500,550] for x and y
        if ((pos.x >= popUp.getPosition().x && pos.x <= (popUp.getPosition().x + popUp.getSize().x))
            && (pos.y >= popUp.getPosition().y && pos.y <= (popUp.getPosition().y + popUp.getSize().y)))
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                runPopUp(*menu1);
    }
}


void Simulator::update()
{
}


void Simulator::render()
{
    window->clear();
    window->draw(popUp);
    window->display();
}


//Test code... possibly wont be used for actual implementation of popup windows
void Simulator::runPopUp(sf::RenderWindow& popUpWindow)
{
    // Create the window
    popUpWindow.create(sf::VideoMode(500.f, 200.f), "Scheduling Algorithms",
                        sf::Style::Titlebar | sf::Style::Close);
    
    sf::RectangleShape background(sf::Vector2f(500.f, 200.f));
    background.setFillColor(sf::Color::Red);
    background.setPosition(sf::Vector2f(0.f, 0.f));
    
    // Manage the window
    while (popUpWindow.isOpen())
    {
        sf::Event event;
        while (popUpWindow.pollEvent(event))
        {
            // Use X botton on title bar to close window
            if (event.type == sf::Event::Closed)
                popUpWindow.close();
        }

        popUpWindow.clear();
        popUpWindow.draw(background);
        popUpWindow.display();
    }

}