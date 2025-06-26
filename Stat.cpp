#include "Stat.h"
#include "GameObject.h"

Stat::Stat(std::shared_ptr<GameObject> owner, float health, float damage) :
	Component(owner), health(health), damage(damage)
{
	this->healthBar.setSize(sf::Vector2f(100, 20));
	this->healthBar.setFillColor(sf::Color::Red);
}

void Stat::update(float deltaTime)
{
	auto hitbox = this->owner->getHitbox();
	sf::Vector2f position;
	position.x = hitbox.getPosition().x + hitbox.getSize().x / 2 - this->healthBar.getSize().x / 2;
	position.y = hitbox.getPosition().y - this->healthBar.getSize().y - 5;

	this->healthBar.setPosition(position);
}

void Stat::render(sf::RenderWindow& window)
{
	window.draw(this->healthBar);
}

void Stat::takeDamage(float amount)
{
    health -= amount;
    if (health < 0) health = 0;

	float percent = health / 100.f;
	if (percent < 0) percent = 0;
	healthBar.setSize(sf::Vector2f(100 * percent, 20));
}
