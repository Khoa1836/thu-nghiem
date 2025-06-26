#include "FollowTarget.h"
#include "GameObject.h"
#include <SFML/System/Vector2.hpp>
#include <cmath>

FollowTarget::FollowTarget(std::shared_ptr<GameObject> owner, std::shared_ptr<GameObject> target, float speed)
    : Component(owner), target(target), speed(speed)
{
}

void FollowTarget::update(float deltaTime)
{
    auto targetPtr = target.lock();
    if (!owner || !targetPtr) return;

    sf::Vector2f ownerPos = owner->getHitbox().getPosition();
    sf::Vector2f targetPos = targetPtr->getHitbox().getPosition();

    sf::Vector2f direction = targetPos - ownerPos;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length > 1e-2f)
    {
        direction /= length;
        owner->getHitbox().move(direction * speed * deltaTime);
    }
}