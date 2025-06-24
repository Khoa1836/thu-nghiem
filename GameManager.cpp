// GameManager.cpp
#include "GameManager.h"

GameManager::GameManager() {}
GameManager::~GameManager() {}

GameManager& GameManager::getInstance() {
    static GameManager instance;
    return instance;
}

bool GameManager::isMousePressed()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (!holding)
        {
            return holding = true;
            
        }
        return false;
    }
    else  
    return holding = false;
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