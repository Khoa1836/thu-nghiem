#pragma once

#include "Component.h"
#include <memory>

class DamageOnContact : public Component
{
private:
    std::weak_ptr<GameObject> target;
    float damage;
    float cooldown;
    float timer;

public:
    DamageOnContact(std::shared_ptr<GameObject> owner, std::shared_ptr<GameObject> target, float damage, float cooldown = 1.0f);
    void update(float deltaTime) override;
};
