#pragma once
#include <SFML/Graphics.hpp>
#include "Component.h"
#include <vector>
#include <memory>
#include "GameObject.h"

class ShooterFireComponent : public Component {
private:
    std::vector<std::shared_ptr<GameObject>>* toAddObjects;
    std::vector<std::shared_ptr<GameObject>>* gameObjects;
    float fireCooldown = 1.5f;
    float timer = 0.f;
    sf::Vector2f n_bulletVelocity;
public:
    ShooterFireComponent(
        std::shared_ptr<GameObject> owner,
        std::vector<std::shared_ptr<GameObject>>* gameObjects,
        std::vector<std::shared_ptr<GameObject>>* toAddObjects,
        float n_fireCooldown,
        sf::Vector2f n_bulletVelocity
    );
    void update(float deltaTime) override;

    std::shared_ptr<GameObject> findPlayer();
};

