#pragma once
#include "GameObject.h"

class BulletOfEnemy : public GameObject {
    sf::Vector2f velocity;
    float damage;
public:
    BulletOfEnemy(sf::Vector2f velocity, sf::Vector2f position, float damage);
    float getDamage() const { return damage; }
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
};
