#pragma once

#include "Component.h"
#include "GameObject.h"

class Gravity : public Component
{
private:
	float gravity = 981;
public:
	Gravity(std::shared_ptr<GameObject> owner);
	void update(float deltaTime) override;
};

