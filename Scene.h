// Scene.h
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "Camera.h"

class Scene {
protected:
    std::vector<std::shared_ptr<GameObject>> gameObjects;
	Camera camera; // Assuming you have a Camera class for handling camera logic

public:
    virtual ~Scene() = default;
    virtual void update(float deltaTime);
    virtual void render(sf::RenderWindow& window);

	const std::vector<std::shared_ptr<GameObject>>& getGameObjects() const {
		return gameObjects;
	}
};