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

private:
    std::vector<std::shared_ptr<GameObject>>* gameObjects;
    bool shieldActive = false;
    float shieldTimer = 0.f;
    float shieldDuration = 0.f;
};





