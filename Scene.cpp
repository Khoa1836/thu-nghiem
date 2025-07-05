// Scene.cpp
#include "Scene.h"
#include "GameManager.h"
#include <iostream> // Add for debug output

void Scene::update(float deltaTime) {
    // Remove destroyed objects before update (optional, for safety)
    gameObjects.erase(
        std::remove_if(gameObjects.begin(), gameObjects.end(),
            [](const std::shared_ptr<GameObject>& obj) {
                return obj->isDestroyed();
            }),
        gameObjects.end()
    );
    // Debug: Log number of game objects in this scene (optional, can comment out if noisy)
    // std::cout << "[DEBUG] Scene GameObjects: " << gameObjects.size() << std::endl;
    for (auto& obj : gameObjects) obj->update(deltaTime);
}

void Scene::render(sf::RenderWindow& window) {
    for (auto& obj : gameObjects) obj->render(window);
}