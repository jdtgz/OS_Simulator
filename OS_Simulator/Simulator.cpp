#include "Simulator.h"


Simulator::Simulator()
{
    windowSize.x = 1500.f;
    windowSize.y = 900.f;

    window = new sf::RenderWindow(sf::VideoMode(windowSize.x, windowSize.y), "Scheduling Simulator",
        sf::Style::Titlebar | sf::Style::Close);

    scheduleVisuals = new VisualScheduler(windowSize, 15, 0);
    
    start = false;
    paused = true;
    finished = false;


    // Set simualtion to null since no alg has been selected
    os = nullptr;

    algSelected = false;

    file = "./procInput1.txt";

    osSimComplete = 0;
    time = 0; 
    sleepDuration = 25;
    remainingProc = 0;

}


Simulator::~Simulator()
{
	delete window;
    delete scheduleVisuals;
    delete os;
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

        sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*window));

        // Use mouse position to handle the algorithm menu and create an appropriate scheduler
        if (!algSelected)
        {
            switch (scheduleVisuals->algorithmInput(mousePos))
            {
                case 1:
                    delete os;
                    os = new ProjectManagement(Factory::createAlgorithm(FIFO, CentralProcessor()));
                    os->printScheduler();
                    os->readProcessFile(file);
                    os->printAllProcesses();
                    remainingProc = os->numProcesses();
                    algSelected = true;
                    break;
                case 2:
                    delete os;
                    os = new ProjectManagement(Factory::createAlgorithm(RR, CentralProcessor()));
                    os->printScheduler();
                    os->readProcessFile(file);
                    os->printAllProcesses();
                    remainingProc = os->numProcesses();
                    algSelected = true;
                    break;
                case 3:
                    delete os;
                    os = new ProjectManagement(Factory::createAlgorithm(SJN, CentralProcessor()));
                    os->printScheduler();
                    os->readProcessFile(file);
                    os->printAllProcesses();
                    remainingProc = os->numProcesses();
                    algSelected = true;
                    break;
                default:
                    delete os;
                    os = nullptr;
                    break;
            }

            // add visuals for processes 
            for (int i = 0; i < remainingProc; i++)
                scheduleVisuals->addProcessRect();
        }

        // Use mouse position to implement selection menu to start, pause, and restart simulation
        if (algSelected)
        {
            switch (scheduleVisuals->simulationInput(mousePos))
            {
                case 1:
                    start = true;
                    paused = false;
                    break;
                case 2:
                    paused = !paused; 
                    break;
                case 3:
                    finished = true;
                    break;
                default:
                    break;
            }
        }
    }
}


void Simulator::update()
{
    if (remainingProc > 0)
    {
        if ((start && !paused) && !finished)
        {
            ++time;

            os->activateProcesses(time);

            stepAction step = os->runStep(time);
            if (step == COMPLETE)
                remainingProc--;

            std::cout << std::setw(5) << time << "\t";
            switch (step)
            {
                case ADMIT_NEW_PROCESS:
                    std::cout << "[  admit]\t";
                    break;
                case BEGIN_RUN:
                    std::cout << "[  begin]\t";
                    break;
                case CONTINUE_RUN:
                    std::cout << "[contRun]\t";
                    break;
                case CONTEXT_SWITCH:
                    std::cout << "[  switch]\t";
                    break;
                case COMPLETE:
                    std::cout << "[ finish]\t";
                    break;
                case NO_ACT:
                    std::cout << "[*noAct*]\t";
                    break;
            }
            os->printStates();
            std::this_thread::sleep_for(std::chrono::milliseconds(sleepDuration));
        }
    }
    else if (finished && remainingProc == 0)
    {
        os->printAllProcesses();
        remainingProc = -1;
    }
    
}


void Simulator::render()
{
    window->clear(sf::Color(105,105,105));

    scheduleVisuals->showTimeLine(*window);

    window->display();
}

