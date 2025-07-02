#pragma once

#include "Component.h"

class ShootComponent : public Component
{
    float shootCooldown;
    float timeSinceLastShot;
public:
    ShootComponent(std::shared_ptr<GameObject> owner, float cooldown)
        : Component(owner), shootCooldown(cooldown), timeSinceLastShot(0.0f) {}

    void update(float deltaTime) override;
    void render(sf::RenderWindow&) override {}
    void shoot();
};

