#include "DropMenu.h"


DropMenu::DropMenu()
{
	active = false;
}


DropMenu::DropMenu(int dropdowns, sf::Vector2f pos)
{
	active = false; 

	font.loadFromFile("./Montserrat-Regular.ttf");

	menu.setSize(sf::Vector2f(150.f, 25.f));
	menu.setFillColor(sf::Color(0,0,0));
	menu.setOutlineThickness(-2);
	menu.setOutlineColor(sf::Color::Transparent);	
	menu.setPosition(pos);

	menuTitle = "Menu";

	for (int i = 0; i < dropdowns; i++)
	{
		// Initialize all boxes
		options.push_back(sf::RectangleShape(sf::Vector2f(150.f, 50.f)));
		options[i].setFillColor(sf::Color::Transparent);

		if (i == 0)
			options[i].setPosition(pos.x, pos.y + 25.f);
		else
			options[i].setPosition(pos.x, pos.y + (i * 50.f) + 25.f);

		options[i].setOutlineThickness(-2);
		options[i].setOutlineColor(sf::Color::Transparent);


		// Initialize all box labels for options 
		labels.push_back(std::to_string(i + 1));
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


void DropMenu::setMainTitle(std::string mainTitle)
{
	menuTitle = mainTitle;
}


void DropMenu::setOptionNames(std::vector<std::string> names)
{
	for (int i = 0; i < names.size(); i++)
	{
		labels[i] = names[i];
	}
}


void DropMenu::showMenu(sf::RenderWindow& window)
{	
	window.draw(menu);
	
	if (active)
	{
		for (int i = 0; i < options.size(); i++)
		{
			window.draw(options[i]);

			sf::Text tmp(labels[i], font, 15);
			tmp.setOrigin(tmp.getGlobalBounds().width / 2, tmp.getGlobalBounds().height / 2);
			tmp.setPosition(options[i].getPosition().x + 75, options[i].getPosition().y + 22.5);
			window.draw(tmp);
		} 
	}

	sf::Text title(menuTitle, font, 15);
	title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);
	title.setPosition(menu.getPosition().x + 75, menu.getPosition().y + 10);
	window.draw(title);
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