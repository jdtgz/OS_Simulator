#include "VisualScheduler.h"


VisualScheduler::VisualScheduler()
{
    algMenu = nullptr;
    simMenu = nullptr;
}


VisualScheduler::~VisualScheduler()
{
    delete algMenu;
    delete simMenu;
}


VisualScheduler::VisualScheduler(sf::Vector2f windowSize, int totalTime, int noProcesses)
{
    // Initialize the algorithm selection drop menu
    algMenu = new DropMenu(3, sf::Vector2f(10.f, 10.f));
    algMenu->setMainTitle("Algorithms");

    std::vector<std::string> strs;
    strs.push_back("FIFO");
    strs.push_back("RoundRobin");
    strs.push_back("SJN");
    algMenu->setOptionNames(strs);

    // Initialize the simulation drop menu
    simMenu = new DropMenu(3, sf::Vector2f(windowSize.x - 160.f, 10.f));
    simMenu->setMainTitle("Simulation");
    strs.clear();
    strs.push_back("Start");
    strs.push_back("Pause");
    strs.push_back("End");
    simMenu->setOptionNames(strs);

  
    // Initialize the main horizontal line for the timeline
    timeline.push_back( sf::RectangleShape(sf::Vector2f(windowSize.x - 100.f, 5.f)) );
    timeline[0].setFillColor(sf::Color::Black);
    timeline[0].setOrigin(timeline[0].getGlobalBounds().width / 2, timeline[0].getGlobalBounds().height / 2);
    timeline[0].move(sf::Vector2f(windowSize.x / 2, windowSize.y / 4));

    // Initilize the directional arrow at the end of timeline 
    timelineArrow.setFillColor(sf::Color::Black);
    timelineArrow.setRadius(30);
    timelineArrow.setPointCount(3);
    timelineArrow.setOrigin(30, 0);
    timelineArrow.rotate(90);
    timelineArrow.move(sf::Vector2f(timeline[0].getPosition().x +
        5.f + timeline[0].getSize().x / 2, timeline[0].getPosition().y));

    font.loadFromFile("./Montserrat-Regular.ttf");

    // Initialize all the timeline partitions and texts
    int separation = timeline[0].getSize().x / totalTime + 1;
    for (int i = 1; i < totalTime + 1; i++)
    {
        timeline.push_back(sf::RectangleShape(sf::Vector2f(5.f, 25.f)));
        timeline[i].setFillColor(sf::Color::Black);
        timeline[i].setOrigin(0, timeline[i].getGlobalBounds().height / 2);
        timeline[i].move(sf::Vector2f((50.f + (i - 1) * separation), windowSize.y / 4));

        timelineLabels.push_back(sf::Text(std::to_string(i), font, 20));
        timelineLabels[i - 1].setFillColor(sf::Color::Black);
        timelineLabels[i - 1].setOrigin(timelineLabels[i - 1].getGlobalBounds().width / 2, 0);
        timelineLabels[i - 1].setPosition(timeline[i].getPosition().x, timeline[i].getPosition().y + 10.f);
    }


    // Initialize all the process boxes and their names
    size.x = 1.f;
    size.y = 30.f;
    for (int i = 0; i < noProcesses; i++)
    {
        procBoxes.push_back(sf::RectangleShape(size));
        procBoxes[i].setFillColor(sf::Color::White);
        procBoxes[i].move(50.f, timeline[0].getPosition().y + ((i + 1) * (size.y + 15.f)));

        procNames.push_back(sf::Text("P" + std::to_string(i + 1), font, 20));
        procNames[i].setFillColor(sf::Color::Black);
        procNames[i].setOrigin(procNames[i].getGlobalBounds().width, 0);
        procNames[i].setPosition(procBoxes[i].getPosition().x - 10.f, procBoxes[i].getPosition().y + 10.f);
    }
}


void VisualScheduler::addProcessRect()
{
    procBoxes.push_back(sf::RectangleShape(size));
    procBoxes.back().setFillColor(sf::Color::White);

    procNames.push_back(sf::Text("P" + std::to_string(procBoxes.size()), font, 20));
    procNames.back().setFillColor(sf::Color::Black);
    procNames.back().setOrigin(procNames.back().getGlobalBounds().width, 0);

    if (procBoxes.size() > 1 && procNames.size() > 1)
    {
        procBoxes.back().move(50.f, procBoxes[procBoxes.size() - 2].getPosition().y + (size.y + 15.f));
    }
    else
    {
        procBoxes.back().move(50.f, timeline[0].getPosition().y + (size.y + 15.f));
    }
    
    procNames.back().setPosition(procBoxes.back().getPosition().x - 10.f, procBoxes.back().getPosition().y + 10.f);
    
}


void VisualScheduler::updateProcess(Process p, stepAction curStep)
{
    // Adjust the color according to current state
    int input = p.curState;
    switch (input)
    {
        case READY:
            
            break;
        case RUNNING:
            break;
        case BLOCKED:
            break;
        case NEW_ARRIVAL:
            break;
        case DONE:
            break;
        case AWAITING:
            break;
    }
    
    input = curStep;
    // Adjust the rectangle shape according to step taken
    switch (input)
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
}


int  VisualScheduler::algorithmInput(sf::Vector2f pos)
{
    return algMenu->handleInput(pos);
}


int VisualScheduler::simulationInput(sf::Vector2f pos)
{
    return simMenu->handleInput(pos);
}


void VisualScheduler::showTimeLine(sf::RenderWindow& window)
{
    algMenu->showMenu(window);
    simMenu->showMenu(window);

    window.draw(timelineArrow);
    for (int i = 0; i < timeline.size(); i++)
    {
        window.draw(timeline[i]);

        if(i < timelineLabels.size())
            window.draw(timelineLabels[i]);
    }

    for (int i = 0; i < procBoxes.size(); i++)
    {
        window.draw(procBoxes[i]);
        window.draw(procNames[i]);
    }
}
