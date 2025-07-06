#pragma once
#include <SFML/Graphics.hpp>
#include "Component.h"
#include <vector>
#include <memory>
class GameObject;

class FireComponent : public Component
{
protected:
    std::vector<std::shared_ptr<GameObject>>* toAddObjects;
    std::vector<std::shared_ptr<GameObject>>* gameObjects;
    float fireCooldown = 0.3f;
    float timer = 0.f;
public:
    FireComponent(std::shared_ptr<GameObject> owner,
        std::vector<std::shared_ptr<GameObject>>* gameObjects,
        std::vector<std::shared_ptr<GameObject>>* toAddObjects,
        float n_fireCoolDown);

    void update(float deltaTime);

    std::shared_ptr<GameObject> findClosestEnemy();
};

