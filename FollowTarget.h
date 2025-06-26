#pragma once

#include "Component.h"
#include <memory>

class FollowTarget : public Component
{
private:
    std::weak_ptr<GameObject> target;
    float speed;

public:
    FollowTarget(std::shared_ptr<GameObject> owner, std::shared_ptr<GameObject> target, float speed);
    void update(float deltaTime) override;
};
