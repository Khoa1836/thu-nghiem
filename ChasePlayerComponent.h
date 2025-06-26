#pragma once
#include "Component.h"
#include <memory>

class GameObject;

class ChasePlayerComponent : public Component
{
    std::shared_ptr<GameObject> target;
    float speed;
public:
    ChasePlayerComponent(std::shared_ptr<GameObject> owner, std::shared_ptr<GameObject> target, float speed = 100.f)
        : Component(owner), target(target), speed(speed) {}

    void update(float deltaTime) override;
};

