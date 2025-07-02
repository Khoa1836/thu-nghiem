#include "ShootComponent.h"
#include "GameObject.h"
#include "Bullet.h"

extern std::vector<std::shared_ptr<GameObject>> gameObjects;

void ShootComponent::update(float deltaTime)
{
    timeSinceLastShot += deltaTime;
    if (timeSinceLastShot >= shootCooldown) {
        shoot();
        timeSinceLastShot = 0.0f;
    }
}

void ShootComponent::shoot()
{
    if (!owner) return;
    sf::Vector2f pos = owner->getHitbox().getPosition();
    sf::Vector2f size = owner->getHitbox().getSize();
    pos.x += size.x / 2 - 7.5f;
    pos.y += size.y / 2 - 7.5f;
    sf::Vector2f dir(0, 100);
    gameObjects.push_back(std::make_shared<Bullet>(pos, dir));
}
