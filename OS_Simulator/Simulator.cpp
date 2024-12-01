#include "Simulator.h"


Simulator::Simulator()
{
    window = new sf::RenderWindow(sf::VideoMode(1000, 1000), "Scheduling Simulator",
        sf::Style::Titlebar | sf::Style::Close);

    for (int i = 0; i < 5; i++)
    {
        menus.push_back(DropMenu(5, sf::Vector2f(10.f + (i * 150.f), 10.f)));
    }

}


Simulator::~Simulator()
{
	delete window;
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

    while (window->pollEvent(event))
    {
        // Closes window in event that either the escape key has been pressed or the close option is clicked
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || event.type == sf::Event::Closed)
            window->close();

        for(auto& x : menus)
            x.handleInput(sf::Vector2f(sf::Mouse::getPosition(*window)));       
    }
}


void Simulator::update()
{
  
}


void Simulator::render()
{
    window->clear(sf::Color(105,105,105));

    for(auto& x : menus)
        x.showMenu(window);

    window->display();
}

