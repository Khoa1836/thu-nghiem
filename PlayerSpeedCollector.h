#pragma once
#include "Component.h"
#include <vector>
#include <memory>

class GameObject;
class SpeedItem;

class PlayerSpeedCollector : public Component {
public:
    PlayerSpeedCollector(std::shared_ptr<GameObject> owner, std::vector<std::shared_ptr<GameObject>>* gameObjects);
    void update(float deltaTime) override;
    bool isSpeedActive() const { return speedActive; }
    float getSpeedMultiplier() const { return speedMultiplier; }
    float getSpeedTimer() const { return speedTimer; }
    float getSpeedDuration() const { return speedDuration; }
private:
    std::vector<std::shared_ptr<GameObject>>* gameObjects;
    bool speedActive = false;
    float speedTimer = 0.f;
    float speedDuration = 0.f;
    float speedMultiplier = 1.f;
};

