#include "MoveForward.h"
#include "GameObject.h"

MoveForward::MoveForward(std::shared_ptr<GameObject> owner, sf::Vector2f target, float speed) :
	Component(owner), target(target), speed(speed)
{
	this->direction = target - this->owner->getHitbox().getPosition();
	float length = sqrt(direction.x * direction.x + direction.y * direction.y);
	direction /= length; // Normalize the direction vector
}

MoveForward::~MoveForward()
{
}

void MoveForward::update(float deltaTime)
{
	this->owner->move(direction * speed * deltaTime);
}
