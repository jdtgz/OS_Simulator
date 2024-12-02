/*
 * Simulator class will be the central class
 * Will handle window and juggle visual/implented features 
 */

#include <SFML/Graphics.hpp>
#include "VisualScheduler.h"

#pragma once
class Simulator
{
	public:
		// Constructor & Destructor
		Simulator();
		~Simulator();

		// Runs entire simulation
		void run();

	private:
		// Processes all input and trigger appropriate event
		void processEvents();

		// updates state of all elements on main window
		void update();

		// Render the visuals 
		void render(); 

		// Main window and its attributes
		sf::RenderWindow* window;
		sf::Vector2f windowSize;
		
		// Handles all the visuals necessary for simulation of OS scheduling
		VisualScheduler* scheduleVisuals;
};

