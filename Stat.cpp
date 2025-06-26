#include "Stat.h"
#include "GameObject.h"

Stat::Stat(std::shared_ptr<GameObject> owner, float health, float damage) :
	Component(owner), health(health), damage(damage)
{
	this->healthBar.setSize(sf::Vector2f(100, 20));
	this->healthBar.setFillColor(sf::Color::Red);

	auto hitbox = this->owner->getHitbox();
	offset.x = hitbox.getPosition().x + hitbox.getSize().x / 2 - this->healthBar.getSize().x / 2;
	offset.y = hitbox.getPosition().y - this->healthBar.getSize().y - 5;
	offset = offset - hitbox.getPosition();
}

void Stat::takeDamage(float amount)
{
	health = std::max(health - amount, 0.f);

	if (health == 0) std::cout << "Died\n";
	else std::cout << "Health remain: " << health << std::endl;

	//update health bar size
	this->healthBar.setSize(sf::Vector2f(100 * (health / 100), 20));
}

void Stat::update(float deltaTime)
{
	auto hitbox = this->owner->getHitbox();

	this->healthBar.setPosition(hitbox.getPosition() + offset);
}

void Stat::render(sf::RenderWindow& window)
{
	window.draw(this->healthBar);
}
