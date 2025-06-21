#pragma once

#include "Component.h"

class CollideWithBounds : public Component
{
public:
	CollideWithBounds(std::shared_ptr<GameObject> owner);
	void update(float deltaTime) override;
};

