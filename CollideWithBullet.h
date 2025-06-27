#pragma once
#include "Component.h"
class CollideWithBullet:public Component
{
private:
	std::vector<std::shared_ptr<GameObject>>* gameObjects;
	std::shared_ptr<GameObject> bullet;
	float damage;
public:
	CollideWithBullet(std::shared_ptr<GameObject> owner,
		std::vector<std::shared_ptr<GameObject>>* n_gameObjects,
		 float n_damage);
	virtual ~CollideWithBullet() = default;

	void update(float deltaTime);
};

