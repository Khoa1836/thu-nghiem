#pragma once

#include "Component.h"

class Stat : public Component
{
private:
	float health;
	float damage;
	sf::RectangleShape healthBar;
public:
	Stat(std::shared_ptr<GameObject> owner,float health,float damage);
	Stat(std::shared_ptr<GameObject> owner, float health, float damage, sf::RectangleShape healthBar);
	void update(float deltaTime) override;
	//void render(sf::RenderWindow& window);
};

