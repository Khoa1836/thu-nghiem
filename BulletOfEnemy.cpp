#include "BulletOfEnemy.h"

BulletOfEnemy::BulletOfEnemy(sf::Vector2f velocity, sf::Vector2f position, float damage)
    : velocity(velocity), damage(damage)
{
    hitbox.setSize(sf::Vector2f(8.f, 8.f));
    hitbox.setFillColor(sf::Color::Cyan);
    hitbox.setPosition(position);
}

void BulletOfEnemy::update(float deltaTime) {
    hitbox.move(this->velocity * deltaTime);
}

void BulletOfEnemy::render(sf::RenderWindow& window) {
    window.draw(hitbox);
}