#pragma once
#include "GameObject.h"
#include <functional>

class Bullet : public GameObject
{
    sf::Vector2f velocity;
public:
    Bullet(const sf::Vector2f& pos, const sf::Vector2f& vel)
        : velocity(vel)
    {
        hitbox.setSize(sf::Vector2f(10, 10));
        hitbox.setFillColor(sf::Color::Yellow);
        hitbox.setPosition(pos);
    }

    void update(float deltaTime) override
    {
        hitbox.move(velocity * deltaTime);
    }

    void render(sf::RenderWindow& window) override
    {
        window.draw(hitbox);
    }
};

