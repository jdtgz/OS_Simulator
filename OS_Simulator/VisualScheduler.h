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

		// Adds a visualizer process unit
		void addProcessRect();

		// Initializes all the ids for procBoxes from pointer array
		void initIDs(int procNum, unsigned int id);

		// Updates the process based on the step 
		void updateProcess(ProcessInProgress stepProc);

		// Handle input for the algorithm selection menu
		int algorithmInput(sf::Vector2f pos);

		// Handle the input for the simulation selection menu
		int simulationInput(sf::Vector2f pos);

		// Draws all objects onto the window
		void showTimeLine(sf::RenderWindow& window);

	private:
		// Menus for user input
		DropMenu* algMenu;
		DropMenu* simMenu; 

		// Shapes that make up the timeline of process executions
		std::vector<sf::RectangleShape> timeline;
		sf::CircleShape timelineArrow;

		// Text that labels each time interval 
		sf::Font font;
		std::vector<sf::Text> timelineLabels;

		// Shapes that track the progress of processes being ran
		sf::Vector2f size;
		unsigned int* procIDs;
		std::vector<sf::RectangleShape> procBoxes;

		// Text that labels each process 
		std::vector<sf::Text> procNames;
};

