#pragma once
#include "Component.h"
#include <vector>
#include <memory>

class CollideWithEnemyBullet : public Component {
private:
    std::vector<std::shared_ptr<GameObject>>* gameObjects;
public:
    CollideWithEnemyBullet(std::shared_ptr<GameObject> owner,
        std::vector<std::shared_ptr<GameObject>>* n_gameObjects);
    void update(float deltaTime) override;
};
