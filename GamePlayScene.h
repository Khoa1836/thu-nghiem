// GamePlayScene.h
#pragma once

#include "Scene.h"
#include "Player.h"

class GamePlayScene : public Scene {
public:
    GamePlayScene();
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window);



private:
    float spawnTimer = 0.0f;

    std::vector<std::shared_ptr<GameObject>> toAddObjects;

    void spawnRandomEnemy(); // Add this helper method
};
