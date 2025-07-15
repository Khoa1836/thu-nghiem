#include "FollowTarget.h"
#include "GameObject.h"

FollowTarget::FollowTarget(std::shared_ptr<GameObject> owner, std::shared_ptr<GameObject> target, float speed) :
	Component(owner), target(target), speed(speed)
{
}

FollowTarget::~FollowTarget()
{
}

void FollowTarget::update(float deltaTime)
{
	sf::Vector2f direction = target->getHitbox().getPosition() - owner->getHitbox().getPosition();
	if (std::hypot(direction.x, direction.y) > 0.1f) // Check if the target is not too close
	{
		direction /= std::hypot(direction.x, direction.y); // Normalize the direction vector
		owner->move(direction * speed * deltaTime); // Move the owner towards the target
	}
}

#include <iostream>
#include "Dog.h"
#include "Bullet.h"
void FollowTarget::onCollisionEnter(std::shared_ptr<GameObject> other)
{
	if (isType<Bullet>(this->owner) && isType<Dog>(other))
	{
		other->needDeleted = true;
		this->owner->needDeleted = true;
	}
}
