#include "ChasePlayerComponent.h"
#include "GameObject.h"
#include <SFML/System/Vector2.hpp>
#include <cmath>

void ChasePlayerComponent::update(float deltaTime)
{
    if (!owner || !target) return;
    sf::Vector2f pos = owner->getHitbox().getPosition();
    sf::Vector2f targetPos = target->getHitbox().getPosition();
    sf::Vector2f dir = targetPos - pos;
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (len > 1e-2f) {
        dir /= len;
        owner->move(dir * speed * deltaTime);
    }
}
