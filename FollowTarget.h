#pragma once

#include "Component.h"
#include <memory>

class FollowTarget : public Component
{
private:
	std::shared_ptr<GameObject> target;
	float speed;
public:
	FollowTarget(std::shared_ptr<GameObject> owner, std::shared_ptr<GameObject> target, float speed);
	virtual ~FollowTarget();

	void setTarget(std::shared_ptr<GameObject> newTarget) {
		target = newTarget;
	}

	void update(float deltaTime) override;
};