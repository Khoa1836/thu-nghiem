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
    return justPressed;
}


void GameManager::setScene(std::shared_ptr<Scene> scene) {
    currentScene = std::move(scene);
}

std::shared_ptr<Scene> GameManager::getCurrentScene() {
    return currentScene;
}


void GameManager::update(float deltaTime) {
    // Detect if the left mouse button is currently pressed
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (!holding) {
            justPressed = true; 
            holding = true;
        }
        else {
            justPressed = false;
        }
    }
    else {
        holding = false;
        justPressed = false;
    }

	this->getCurrentScene()->update(deltaTime);
}


void GameManager::render(sf::RenderWindow& window) {
	this->getCurrentScene()->render(window);
}