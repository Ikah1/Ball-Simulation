#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Graphics.hpp>

namespace Ikah 
{
    class Ball 
    {
    public:
        Ball(sf::Vector2u windowSize, sf::Vector2f position, float radius = 5, float CoR = 0.6f);
        ~Ball() = default;
        void update(sf::Time &dt);
        void render(sf::RenderWindow &window);
    private:
        sf::CircleShape ball;
        int windowWidth, windowHeight;
        void collision();
        int randomNumber(int min = 1, int max = 50);
        sf::Vector2f velocity;
        float mass;
        const float g = 9.8f;
        float KE;
        float CoR;
    };
}

#endif