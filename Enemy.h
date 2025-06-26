#pragma once

#include "GameObject.h"
#include <functional>
class Enemy : public GameObject
{
public:
    Enemy();
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
};