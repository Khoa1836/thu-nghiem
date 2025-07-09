#pragma once
#include "Component.h"
class MoveForward : public Component
{
private:
	sf::Vector2f target;
	sf::Vector2f direction = sf::Vector2f();
	float speed;

public:
	MoveForward(std::shared_ptr<GameObject> owner, sf::Vector2f target, float speed);
	virtual ~MoveForward();

	void update(float deltaTime) override;
};

