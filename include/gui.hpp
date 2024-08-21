#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <iomanip>

namespace Ikah {
    class GUI 
    {
    public:
        GUI(int windowWidth, int windowHeight);
        ~GUI() = default;
        void eventHandler(sf::Event &event);
        void update();
        void render(sf::RenderWindow &window);
        sf::RectangleShape getGUIBackground();

        float getRadius();
        float getCoR();
    private:
        int windowWidth, windowHeight;
        void createGUI();
        sf::Font font;
        sf::Text label(std::string text, sf::Vector2f position, int size, sf::Color color = sf::Color::White);

        //Colors
        sf::Color backgroundColor = sf::Color(0, 0, 0, 150);
        sf::Color fontColor = sf::Color::White;
        sf::Color sliderBackgroundColor = sf::Color(100, 100, 100, 255);
        sf::Color sliderColor = sf::Color(200, 200, 200, 255);

        //GUI elements
        struct Slider
        {
            sf::RectangleShape sliderHandle;
            sf::RectangleShape sliderBackground;
            sf::Text valueLabel;
            sf::Text nameLabel;
            float value;
            float min;
            float max;
            float dragOffset;
            bool isDragging = false;
            void render(sf::RenderWindow &window)
            {
                window.draw(sliderBackground);
                window.draw(sliderHandle);
                window.draw(valueLabel);
                window.draw(nameLabel);
            }
            void updateSlider(sf::Event &event);
        };
        void createSlider(Slider &slider, std::string name, sf::Vector2f position, sf::Vector2f size, float min, float max);
        
        sf::RectangleShape background;
        sf::Text radiusLabel;
        Slider radiusSlider, CoRSlider;
    };
}

#endif // GUI_HPP