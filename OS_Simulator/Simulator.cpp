#include "Simulator.h"


Simulator::Simulator()
{
    windowSize.x = 1500.f;
    windowSize.y = 900.f;

    window = new sf::RenderWindow(sf::VideoMode(windowSize.x, windowSize.y), "Scheduling Simulator",
        sf::Style::Titlebar | sf::Style::Close);

    // Create the visuals for the processes
    scheduleVisuals = new VisualScheduler(windowSize, 15, 4);
}


Simulator::~Simulator()
{
	delete window;
    delete scheduleVisuals;
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

        scheduleVisuals->handleInput(sf::Vector2f(sf::Mouse::getPosition(*window)));       
    }
}


void Simulator::update()
{
  
}


void Simulator::render()
{
    window->clear(sf::Color(105,105,105));

    scheduleVisuals->showTimeLine(*window);

    window->display();
}

