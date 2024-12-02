/*
 * Includes all the visuals necessary for entire scheduling simulation
 */

#include<SFML/Graphics.hpp>
#include "DropMenu.h"

#pragma once
class VisualScheduler
{
	public:
		VisualScheduler();
		~VisualScheduler();

		// Creates the simulation visuals based on the window size,
		VisualScheduler(sf::Vector2f windowSize, int totalTime, int noProcesses);

		// Takes the position of the mouse and handles input from it accordingly
		void handleInput(sf::Vector2f pos);

		// Draws all objects onto the window
		void showTimeLine(sf::RenderWindow& window);

	private:
		// Menus for user input
		std::vector<DropMenu> menus;

		// Shapes that make up the timeline of process executions
		std::vector<sf::RectangleShape> timeline;
		sf::CircleShape timelineArrow;

		// Text that labels each time interval 
		sf::Font font;
		std::vector<sf::Text> timelineLabels;

		// Shapes that track the progress of processes being ran
		std::vector<sf::RectangleShape> procBoxes;

		// Text that labels each process 
		std::vector<sf::Text> procNames;
};

