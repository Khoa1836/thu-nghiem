// Scene.h
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "GameObject.h"

class Scene {
protected:
    std::vector<std::shared_ptr<GameObject>> gameObjects;

public:
    virtual ~Scene() = default;
    virtual void update(float deltaTime);
    virtual void render(sf::RenderWindow& window);
};