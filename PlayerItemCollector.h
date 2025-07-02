#pragma once
#include "Component.h"
#include "HealItem.h"
#include "ShieldItem.h"
#include "Stat.h"
#include "GameObject.h"
#include <vector>
#include <memory>

class PlayerItemCollector : public Component
{
public:
    PlayerItemCollector(std::shared_ptr<GameObject> owner, std::vector<std::shared_ptr<GameObject>>* gameObjects);

    void update(float deltaTime) override;

    bool isShieldActive() const { return shieldActive; }
    bool isSpeedActive() const { return speedActive; }
    float getSpeedMultiplier() const { return speedMultiplier; }

private:
    std::vector<std::shared_ptr<GameObject>>* gameObjects;
    // Shield
    bool shieldActive = false;
    float shieldTimer = 0.f;
    float shieldDuration = 0.f;
    // Speed
    bool speedActive = false;
    float speedTimer = 0.f;
    float speedDuration = 0.f;
    float speedMultiplier = 1.f;
};









