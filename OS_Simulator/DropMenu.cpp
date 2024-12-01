#include "DropMenu.h"

DropMenu::DropMenu()
{
	active = false;

	menu.setSize(sf::Vector2f(0.f, 0.f));
	menu.setFillColor(sf::Color::Transparent);
	menu.setPosition(0,0);
}


DropMenu::DropMenu(int dropdowns, sf::Vector2f pos)
{
	active = false; 

	menu.setSize(sf::Vector2f(150.f, 25.f));
	menu.setFillColor(sf::Color(0,0,0));
	menu.setOutlineThickness(-2);
	menu.setOutlineColor(sf::Color::Transparent);	
	menu.setPosition(pos);

	for (int i = 0; i < dropdowns; i++)
	{
		options.push_back(sf::RectangleShape(sf::Vector2f(150.f, 50.f)));
		options[i].setFillColor(sf::Color::Transparent);

		if (i == 0)
			options[i].setPosition(pos.x, pos.y + 25.f);
		else
			options[i].setPosition(pos.x, pos.y + (i * 50.f) + 25.f);

		options[i].setOutlineThickness(-2);
		options[i].setOutlineColor(sf::Color::Transparent);
	}
}


DropMenu::~DropMenu()
{
}


void DropMenu::activateMenu()
{
	active = true;
	for (auto& x : options)
		x.setFillColor(sf::Color(0,0,0));
}


void DropMenu::deactivateMenu()
{
	active = false;
	for (auto& x : options)
		x.setFillColor(sf::Color::Transparent);
}


void DropMenu::showMenu(sf::RenderWindow* window)
{
	window->draw(menu);
	if(active)
		for (auto& x : options)
			window->draw(x);
}


sf::RectangleShape DropMenu::getMenu()
{
	return menu;
}


void DropMenu::handleInput(sf::Vector2f pos)
{
	auto inRange = [](sf::Vector2f pos, sf::RectangleShape shape) -> bool
		{
			return pos.x >= shape.getPosition().x && pos.x <= (shape.getPosition().x + shape.getSize().x)
				&& pos.y >= shape.getPosition().y && pos.y <= (shape.getPosition().y + shape.getSize().y);
				
		};

	if (inRange(pos, menu))
	{
		// show selection visuals if mouse is hovering over menu
		menu.setOutlineColor(sf::Color::White);
		menu.setFillColor(sf::Color(0,0,0,125));

		// check for input and activate drop menu accordingly
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			activateMenu();
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			deactivateMenu();
	}
	else
	{
		// hide selection visuals if mouse not hovering over menu
		menu.setOutlineColor(sf::Color::Transparent);
		menu.setFillColor(sf::Color(0, 0, 0, 255));
	}


	for (int i = 0; i < options.size(); i++)
	{
		if (inRange(pos, options[i]) && active)
		{
			// show selection visuals for 
			options[i].setOutlineColor(sf::Color::White);
			options[i].setFillColor(sf::Color(0, 0, 0, 125));

			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
				std::cout << "Box: " << i << std::endl;
		}
		else
		{
			// hide selection visuals 
			options[i].setOutlineColor(sf::Color::Transparent);
			options[i].setFillColor(sf::Color(0, 0, 0, 255));
		}
	}

}