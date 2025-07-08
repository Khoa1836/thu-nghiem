#pragma once
#include "Component.h"
#include <vector>
#include <memory>

class GameObject;
class HealItem;
class Stat;

class PlayerHealCollector : public Component {
public:
    PlayerHealCollector(std::shared_ptr<GameObject> owner, std::vector<std::shared_ptr<GameObject>>* gameObjects);
    void update(float deltaTime) override;
private:
    std::vector<std::shared_ptr<GameObject>>* gameObjects;
};

