#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
class Bullet : public GameObject
{
private:
	sf::Vector2f velocity;
	float damage;
public:
	Bullet(sf::Vector2f velocity, sf::Vector2f position, float damage);
	float getDamage() const { return damage; }
	void update(float deltaTime) override;
	void render(sf::RenderWindow& window) override;
};

