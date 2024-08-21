#include "../include/gui.hpp"
#include <iostream>

Ikah::GUI::GUI(int windowWidth, int windowHeight)
{
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;

    // Load font
    if (!font.loadFromFile("../assets/fonts/Dosis-Regular.ttf"))
    {
        std::cerr << "Error loading font\n";
    }

    createGUI();
}

void Ikah::GUI::createGUI()
{
    // Gui background
    background = sf::RectangleShape(sf::Vector2f(windowWidth / 8, windowHeight / 4));
    background.setPosition(5, 5);
    background.setFillColor(backgroundColor);

    int backgroundVerticalDiv = background.getPosition().y + background.getSize().y / 3;

    // Radius slider
    createSlider(radiusSlider, "Radius", sf::Vector2f(10, backgroundVerticalDiv), sf::Vector2f(100, 10), 5, 100);

    // CoR slider
    createSlider(CoRSlider, "CoR", sf::Vector2f(10, backgroundVerticalDiv * 2), sf::Vector2f(100, 10), 0, 1);
}

void Ikah::GUI::eventHandler(sf::Event &event)
{
    radiusSlider.updateSlider(event);
    CoRSlider.updateSlider(event);
}

void Ikah::GUI::update()
{
}

void Ikah::GUI::render(sf::RenderWindow &window)
{
    window.draw(background);
    window.draw(radiusLabel);
    radiusSlider.render(window);
    CoRSlider.render(window);
}

sf::Text Ikah::GUI::label(std::string text, sf::Vector2f position, int size, sf::Color color)
{
    sf::Text label(text, font, size);
    label.setPosition(position);
    label.setFillColor(color);
    return label;
}

void Ikah::GUI::createSlider(Slider &slider, std::string name, sf::Vector2f position, sf::Vector2f size, float min, float max)
{
    slider.nameLabel = label(name, sf::Vector2f(position.x, position.y - slider.nameLabel.getCharacterSize()), 20, fontColor);
    slider.min = min;
    slider.max = max;
    slider.sliderBackground = sf::RectangleShape(size);
    slider.sliderBackground.setPosition(position);
    slider.sliderBackground.setFillColor(sliderBackgroundColor);
    slider.sliderHandle = sf::RectangleShape(sf::Vector2f(slider.sliderBackground.getGlobalBounds().width / 10, slider.sliderBackground.getGlobalBounds().height * 2));
    slider.sliderHandle.setPosition(slider.sliderBackground.getPosition().x, slider.sliderBackground.getPosition().y + (slider.sliderBackground.getSize().y - slider.sliderHandle.getSize().y) / 2);
    slider.sliderHandle.setFillColor(sliderColor);
    slider.value = slider.min;
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << slider.value;
    slider.valueLabel = label(ss.str(), sf::Vector2f(position.x + size.x + 10, position.y - 10), 20, fontColor);
}

void Ikah::GUI::Slider::updateSlider(sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (sliderBackground.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && event.mouseButton.button == sf::Mouse::Left)
        {
            isDragging = true;
            dragOffset = event.mouseButton.x - sliderHandle.getPosition().x;
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased)
    {
        if (isDragging && event.mouseButton.button == sf::Mouse::Left)
        {
            isDragging = false;
        }
    }
    else if (event.type == sf::Event::MouseMoved)
    {
        if (isDragging)
        {
            float newX = event.mouseMove.x - dragOffset;
            float maxX = sliderBackground.getPosition().x + sliderBackground.getSize().x - sliderHandle.getSize().x;
            float minX = sliderBackground.getPosition().x;
            newX = std::max(minX, std::min(newX, maxX));
            sliderHandle.setPosition(newX, sliderHandle.getPosition().y);
            value = min + (max - min) * ((newX - minX) / (maxX - minX));
            std::stringstream ss;
            ss << std::fixed << std::setprecision(2) << value;
            valueLabel.setString(ss.str());
        }
    }
}

sf::RectangleShape Ikah::GUI::getGUIBackground()
{
    return background;
}

float Ikah::GUI::getRadius()
{
    return radiusSlider.value;
}

float Ikah::GUI::getCoR()
{
    return CoRSlider.value;
}
