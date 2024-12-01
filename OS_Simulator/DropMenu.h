
#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>

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

		// Draws the menu onto a window
		void showMenu(sf::RenderWindow* window);

		// Returns the rectangle of main menu
		sf::RectangleShape getMenu();

		// takes position of mouse on window and handles the input of it 
		void handleInput(sf::Vector2f pos);

	private:
		// Keeps track of when the menu is "dropped" and reads input
		bool active;
		
		// Shape on window that releases rest of dropdown menu 
		sf::RectangleShape menu;

		// Outlines selection depending on where mouse is for user to visualize 
		std::vector<sf::RectangleShape> options;
};

