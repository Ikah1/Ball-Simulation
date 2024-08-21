#include "../include/ball.hpp"
#include <math.h>
#include <iostream>

Ikah::Ball::Ball(sf::Vector2u windowSize, sf::Vector2f position, float radius, float CoR)
{
    this->windowWidth = windowSize.x;
    this->windowHeight = windowSize.y;
    this->ball = sf::CircleShape(radius);
    this->ball.setFillColor(sf::Color(randomNumber(255), randomNumber(255), randomNumber(255), 255));
    this->ball.setPosition(position - sf::Vector2f(ball.getRadius(), ball.getRadius()));
    this->mass = ball.getRadius() / 25;
    this->CoR = CoR;
}

void Ikah::Ball::update(sf::Time &dt)
{
    velocity.y += mass * g;
    //Floor collision
    ball.move(velocity * dt.asSeconds());
    collision();
    //std::cout << "Velocity: " << velocity.y << " initVelocity: " << initVelocity.y << "\n";
}

void Ikah::Ball::render(sf::RenderWindow &window)
{
    window.draw(ball);
}

void Ikah::Ball::collision()
{
    //Floor collision
    if (ball.getPosition().y + ball.getRadius() * 2 >= windowHeight)
    {
        ball.setPosition(ball.getPosition().x, windowHeight - ball.getRadius() * 2);
        //KE = 0.5f * (ball.getRadius() / 100) * pow(initVelocity.y, 2);
        velocity.y = -velocity.y * CoR;
    }
    //Ceiling collision
    if (ball.getPosition().y <= 0)
    {
        ball.setPosition(ball.getPosition().x, 0);
        velocity.y = -velocity.y * CoR;
    }
    //Wall collision
    if (ball.getPosition().x <= 0 || ball.getPosition().x + ball.getRadius() * 2 >= windowWidth)
    {
        ball.setPosition(0, ball.getPosition().y);
        velocity.x = -velocity.x * CoR;
    }
}

int Ikah::Ball::randomNumber(int min, int max)
{
    int range = max - min + 1;
    return rand() % range + min;
}
