#pragma once

#include "Component.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <functional>

class ShootComponent : public Component
{
private:
    float shootCooldown;
    float timeSinceLastShot;
    std::function<void(const sf::Vector2f&, const sf::Vector2f&)> spawnBullet;
public:
    ShootComponent(std::shared_ptr<GameObject> owner, float cooldown,
                   std::function<void(const sf::Vector2f&, const sf::Vector2f&)> spawnBullet)
        : Component(owner), shootCooldown(cooldown), timeSinceLastShot(0.0f), spawnBullet(spawnBullet) {}

    void update(float deltaTime) override;
    void shoot();
};
