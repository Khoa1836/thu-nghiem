#include "Enemy.h"
#include <functional>
Enemy::Enemy()
{
  
}

void Enemy::update(float deltaTime)
{
    updateComponents(deltaTime);
}

void Enemy::render(sf::RenderWindow& window)
{
    window.draw(hitbox);
}