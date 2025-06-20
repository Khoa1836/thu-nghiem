// GameManager.cpp
#include "GameManager.h"

GameManager::GameManager() {}
GameManager::~GameManager() {}

GameManager& GameManager::getInstance() {
    static GameManager instance;
    return instance;
}

void GameManager::setScene(std::shared_ptr<Scene> scene) {
    currentScene = std::move(scene);
}

std::shared_ptr<Scene> GameManager::getCurrentScene() {
    return currentScene;
}

void GameManager::update(float deltaTime) {
    if (currentScene) currentScene->update(deltaTime);
}

void GameManager::render(sf::RenderWindow& window) {
    if (currentScene) currentScene->render(window);
}