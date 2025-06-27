#pragma once
#include <SFML/Graphics.hpp>
#include "Component.h"
class FireComponent :public Component
{
private:
	std::vector<std::shared_ptr<GameObject>>* toAddObjects;
	std::vector<std::shared_ptr<GameObject>>* gameObjects;
	float fireCooldown = 0.3f;
	float timer = 0.f;
	sf::Vector2f n_bulletVelocity;
public:
	FireComponent(std::shared_ptr<GameObject> owner,
		std::vector<std::shared_ptr<GameObject>>* gameObjects,
		std::vector<std::shared_ptr<GameObject>>* toAddObjects ,
	              float n_fireCoolDown, sf::Vector2f n_bulletVelocity);
	void update(float deltaTime);

	std::shared_ptr<GameObject> findClosestEnemy();
};

