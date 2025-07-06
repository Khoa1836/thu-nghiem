#include "ShooterEnemy.h"

ShooterEnemy::ShooterEnemy()
    : Enemies()
{
    hitbox.setFillColor(sf::Color(0, 128, 255)); // Example: blue for shooter
    hitbox.setSize(sf::Vector2f(40.f, 40.f));
}

void ShooterEnemy::render(sf::RenderWindow& window) {
    Enemies::render(window);
}
