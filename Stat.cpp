#include "Stat.h"
#include "GameObject.h"

Stat::Stat(std::shared_ptr<GameObject> owner, float health, float damage):
	Component(owner),
	health(health),
	damage(damage)
{
	healthBar.setSize(sf::Vector2f(20.f, 100.f));
	healthBar.setFillColor(sf::Color::Red);
}

Stat::Stat(std::shared_ptr<GameObject> owner, float health, float damage, sf::RectangleShape healthBar):
Component(owner),
health(health),
damage(damage)
{
	healthBar.setSize(sf::Vector2f(20.f, 100.f));
	healthBar.setFillColor(sf::Color::Red);
}

void Stat::update(float deltaTime)
{
	auto hitbox = this->owner->getHitbox();
	sf::Vector2f position;
	position.x = hitbox.getPosition().x + hitbox.getSize().x/2 - healthBar.getSize().x/2;
	position.y = hitbox.getPosition().y - 30;

}

//void Stat::render(sf::RenderWindow& window)
//{
//	window.draw(healthBar);
//}