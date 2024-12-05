/*
 * Simulator class will be the central class
 * Will handle window and juggle visual/implented features 
 */

#include "SFML/Graphics.hpp"
#include <chrono>
#include <thread>
#include "VisualScheduler.h"
#include "ProjectManagement.h"

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

		// Updates state of all elements on main window
		void update();

		// Render the visuals 
		void render(); 

		// Main window and its attributes
		sf::Vector2f windowSize;
		sf::RenderWindow* window;
		
		// Handles all the visuals necessary for simulation of OS scheduling
		VisualScheduler* scheduleVisuals;
		bool visualsLoaded;

		// simulation playback control
		bool start;
		bool paused;
		bool finished;

		// OS Management class that oversees implementation of scheduling
		ProjectManagement* os;

		bool algSelected;

		std::string file;
		std::stringstream ss;

		long time;
		long sleepDuration;
		int remainingProc;
};

