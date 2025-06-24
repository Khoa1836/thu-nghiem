#include "Gravity.h"

Gravity::Gravity(std::shared_ptr<GameObject> owner) : Component(owner)
{
}

void Gravity::update(float deltaTime)
{
	this->owner->getHitbox().move(0, gravity * deltaTime);
}