#pragma once
#include "Component.h"
#include <vector>
#include <memory>

class GameObject;
class ShieldItem;

class PlayerShieldCollector : public Component {
public:
    PlayerShieldCollector(std::shared_ptr<GameObject> owner, std::vector<std::shared_ptr<GameObject>>* gameObjects);
    void update(float deltaTime) override;
    bool isShieldActive() const { return shieldActive; }
    float getShieldTimer() const { return shieldTimer; }
    float getShieldDuration() const { return shieldDuration; }
private:
    std::vector<std::shared_ptr<GameObject>>* gameObjects;
    bool shieldActive = false;
    float shieldTimer = 0.f;
    float shieldDuration = 0.f;
};

