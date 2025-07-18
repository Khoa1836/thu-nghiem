// GameManager.h
#pragma once

#include <memory>
#include "Scene.h"

class GameManager {
private:
    std::shared_ptr<Scene> currentScene;
    GameManager();
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;

    bool holding = false;
    bool justPressed = false;

public:
    ~GameManager();
    static GameManager& getInstance();
        
    bool isMousePressed();


    void setScene(std::shared_ptr<Scene> scene);
    std::shared_ptr<Scene> getCurrentScene();

    void update(float deltaTime);
    void render(sf::RenderWindow& window);
};