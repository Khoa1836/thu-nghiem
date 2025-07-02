#include "Bullet.h"

Bullet::Bullet(sf::Vector2f velocity, sf::Vector2f position, float damage) :
velocity(velocity), damage(damage)
{
	hitbox.setSize(sf::Vector2f(8.f,8.f));
	hitbox.setFillColor(sf::Color::Blue);
	hitbox.setPosition(position);
}

void Bullet::update(float deltaTime)
{
	hitbox.move(this->velocity * deltaTime);
}

void Bullet::render(sf::RenderWindow& window) 
{
	window.draw(hitbox);
}	