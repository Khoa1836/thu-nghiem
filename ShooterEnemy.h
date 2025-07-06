#pragma once
#include "Enemies.h"

class ShooterEnemy : public Enemies {
public:
    ShooterEnemy();
    virtual ~ShooterEnemy() = default;
    void render(sf::RenderWindow& window);
};
