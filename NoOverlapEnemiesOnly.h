#pragma once

#include "Component.h"
#include <vector>
#include <memory>

class NoOverlapEnemiesOnly : public Component
{
private:
    std::vector<std::shared_ptr<GameObject>>* allObjects;

public:
    NoOverlapEnemiesOnly(std::shared_ptr<GameObject> owner, std::vector<std::shared_ptr<GameObject>>* allObjects);
    void update(float deltaTime) override;
};
