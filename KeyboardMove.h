#pragma once

#include "Component.h"
#include "GameObject.h"

class KeyboardMove : public Component
{
private:
	float speed;
public:
	KeyboardMove(std::shared_ptr<GameObject> owner, float speed);
	void update(float deltaTime) override;
};

