#pragma once

#include "Component.h"

class Stat : public Component
{
private:
	float health;
	float damage;
	sf::RectangleShape healthBar;

public:
	Stat(std::shared_ptr<GameObject> owner, float health = 100.f, float damage = 10.f);
	void update(float deltaTime) override;
	void render(sf::RenderWindow& window) override;
};

