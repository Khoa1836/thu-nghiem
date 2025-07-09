// Scene.cpp
#include "Scene.h"
#include "GameManager.h"

void Scene::update(float deltaTime) {
    for (auto& obj : gameObjects) obj->update(deltaTime);
}

void Scene::render(sf::RenderWindow& window) {
    window.setView(this->camera.getView(window.getSize()));
    for (auto& obj : gameObjects) obj->render(window);
}