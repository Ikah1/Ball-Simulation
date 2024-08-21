#include <iostream>
#include <vector>

#include "../include/ball.hpp"
#include "../include/gui.hpp"

#define RICH_GREY sf::Color(31, 32, 34, 255)

bool isInGUIBackground(sf::Vector2i mousePos, sf::RectangleShape background);

int main(int argc, char *argv[])
{
    const int WINDOW_WIDTH = 1280;
    const int WINDOW_HEIGHT = 720;
    sf::Vector2u windowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Bouncing Ball", sf::Style::Close | sf::Style::Titlebar, settings);
    window.setFramerateLimit(60);

    sf::Clock clock;
    srand(time(NULL));

    std::vector<Ikah::Ball> balls;
    
    bool isMousePressed = false;

    Ikah::GUI gui(WINDOW_WIDTH, WINDOW_HEIGHT);
    bool isMouseInGUI = false;

    sf::Event event;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isMousePressed && !isMouseInGUI)
            {
                sf::Vector2f position = sf::Vector2f(sf::Mouse::getPosition(window));
                balls.push_back(Ikah::Ball(windowSize,position, gui.getRadius(), gui.getCoR()));
                isMousePressed = true;
            }
            if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                isMousePressed = false;
            }
            gui.eventHandler(event);
        }
        // Update
        sf::Time dt = clock.restart();
        isMouseInGUI = isInGUIBackground(sf::Mouse::getPosition(window), gui.getGUIBackground());
        for (Ikah::Ball &ball : balls)
        {
            ball.update(dt);
        }
        gui.update();
        //Render
        window.clear(sf::Color(RICH_GREY));
        //Draw here

        for (Ikah::Ball &ball : balls)
        {
            ball.render(window);
        }
        gui.render(window);

        //End draw
        window.display();
    }

    return EXIT_SUCCESS;
}

bool isInGUIBackground(sf::Vector2i mousePos, sf::RectangleShape background)
{
    return background.getGlobalBounds().contains(mousePos.x, mousePos.y);
}