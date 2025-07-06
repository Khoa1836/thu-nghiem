#pragma once
#include "FireComponent.h"

class ShooterFireComponent : public FireComponent
{
public:
    ShooterFireComponent(
        std::shared_ptr<GameObject> owner,
        std::vector<std::shared_ptr<GameObject>>* gameObjects,
        std::vector<std::shared_ptr<GameObject>>* toAddObjects,
        float n_fireCooldown
    );
    void update(float deltaTime) override;
};

