#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

class Enemies : public GameObject
{
public:
    Enemies();
    virtual ~Enemies() = default;
    void update(float deltaTime);
    virtual void render(sf::RenderWindow& window) override;
    void onSpawn() override;
    void onDestroy() override;

protected:
    sf::RectangleShape healthBar;
    float maxHealth = 100.f; // default, can be set in constructor or via Stat
};

