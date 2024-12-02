#include "VisualScheduler.h"


VisualScheduler::VisualScheduler()
{
}


VisualScheduler::~VisualScheduler()
{
}


VisualScheduler::VisualScheduler(sf::Vector2f windowSize, int totalTime, int noProcesses)
{
    // Initialize the drop menu for algorithm selection
    menus.push_back(DropMenu(4, sf::Vector2f(10.f, 10.f)));
    menus[0].setMainTitle("Algorithms");

    std::vector<std::string> strs;
    strs.push_back("FIFO");
    strs.push_back("RoundRobin");
    strs.push_back("SJN");
    strs.push_back("SRT");
    menus[0].setOptionNames(strs);

    // Initialize the simulation drop menu
    menus.push_back(DropMenu(3, sf::Vector2f(windowSize.x - 160.f, 10.f)));
    menus[1].setMainTitle("Simulation");
    strs.clear();
    strs.push_back("Start");
    strs.push_back("Pause");
    strs.push_back("End");
    menus[1].setOptionNames(strs);

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
    for (int i = 0; i < noProcesses; i++)
    {
        procBoxes.push_back(sf::RectangleShape(sf::Vector2f(5.f, 50.f)));
        procBoxes[i].setFillColor(sf::Color::Green);
        procBoxes[i].move(50.f, timeline[0].getPosition().y + ((i + 1) * 80.f));

        procNames.push_back(sf::Text("P" + std::to_string(i + 1), font, 20));
        procNames[i].setFillColor(sf::Color::Black);
        procNames[i].setOrigin(procNames[i].getGlobalBounds().width, 0);
        procNames[i].setPosition(procBoxes[i].getPosition().x - 10.f, procBoxes[i].getPosition().y + 10.f);
    }
}


void VisualScheduler::handleInput(sf::Vector2f pos)
{
    // Handle the input for the drop menus
    for (auto& x : menus)
    {
        x.handleInput(pos);
    }
}


void VisualScheduler::showTimeLine(sf::RenderWindow& window)
{
    // Draw the main dropmenus onto the screen 
    for (auto& x: menus)
    {
        x.showMenu(window);
    }

    // Draw the timeline along with partitions and their labels
    window.draw(timelineArrow);
    for (int i = 0; i < timeline.size(); i++)
    {
        window.draw(timeline[i]);

        if(i < timelineLabels.size())
            window.draw(timelineLabels[i]);
    }

    // Draw the process boxes along with their labels
    for (int i = 0; i < procBoxes.size(); i++)
    {
        window.draw(procBoxes[i]);
        window.draw(procNames[i]);
    }
}
