/*
 * DropMenu class provides a general structure for creating any sort of drop menus
 */

#include <iostream>
#include "SFML/Graphics.hpp"


#pragma once
class DropMenu
{
	public:
		DropMenu();
		~DropMenu();

		// Creates a drop menu at a position pos with 
		// dropdowns number of options attached to it
		DropMenu(int dropdowns, sf::Vector2f pos);

		// Displays the drop menu options 
		void activateMenu();

		// Hides the drop menu options
		void deactivateMenu();

		// Change the title of the main menu
		void setMainTitle(std::string mainTitle); 

		// Change the titles of the drop menu options
		void setOptionNames(std::vector<std::string> names);

		// Draws the menu onto a window
		void showMenu(sf::RenderWindow& window);

		// takes position of mouse on window and handles the input of it 
		void handleInput(sf::Vector2f pos);

	private:
		// Keeps track of when the menu is "dropped" and reads input
		bool active;

		// Font used for labels on sections
		sf::Font font;

		// Shape on window that releases rest of dropdown menu 
		sf::RectangleShape menu;
		std::string menuTitle;

		// Outlines selection depending on where mouse is for user to visualize 
		std::vector<sf::RectangleShape> options;
		std::vector<std::string> labels;
};

