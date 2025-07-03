#pragma once
#include "Component.h"
#include <vector>
#include <memory>

class PlayerCollectGemComponent : public Component {
    std::vector<std::shared_ptr<GameObject>>* gameObjects;
public:
    PlayerCollectGemComponent(std::shared_ptr<GameObject> owner,
        std::vector<std::shared_ptr<GameObject>>* gameObjects)
        : Component(owner), gameObjects(gameObjects) {}

    void update(float deltaTime) override;
};