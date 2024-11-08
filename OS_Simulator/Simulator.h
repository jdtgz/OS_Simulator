/*
 * Simulator class will be the central class
 * Will handle window and juggle visual/implented features 
 */

#include <iostream>
#include <SFML/Graphics.hpp>
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

		// run a popUp window
		void runPopUp(sf::RenderWindow&);

		// Main window 
		sf::RenderWindow* window;
		sf::RenderWindow* menu1; 

		// Testing window obj
		sf::RectangleShape popUp;
};

