// GamePlayScene.cpp
#include <random>
#include "GamePlayScene.h"
#include "SelectLevelScene.h"
#include "SwitchSceneCommand.h"
#include "Button.h"
#include "DamageOnContact.h"
#include "FollowTarget.h"
#include "NoOverlapEnemiesOnly.h"

// Helper function to spawn and randomize enemy position
void GamePlayScene::spawnRandomEnemy() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distX(0.f, 1230.f); // 1280 
    std::uniform_real_distribution<float> distY(0.f, 670.f);  // 720 

    auto player = gameObjects[1];
    auto newEnemy = GameObjectFactory::createEnemy(player, &gameObjects);
    newEnemy->getHitbox().setPosition(distX(gen), distY(gen));
    gameObjects.push_back(newEnemy);
}

GamePlayScene::GamePlayScene() {
    gameObjects.push_back(std::make_shared<Button>(
        "Back", 100, 600, sf::Vector2f(50.f, 50.f),
        std::make_shared<SwitchSceneCommand>([]() {
            return std::make_shared<SelectLevelScene>();
        })
    ));

    auto player = GameObjectFactory::createPlayer(&gameObjects, &toAddObjects);
    gameObjects.push_back(player);

    spawnRandomEnemy(); // Use helper for initial enemy
}

void GamePlayScene::update(float deltaTime) {
    // Update all objects
    for (auto& obj : gameObjects) obj->update(deltaTime);

	// delete destroyed objects
    gameObjects.erase(
        std::remove_if(gameObjects.begin(), gameObjects.end(),
            [](const std::shared_ptr<GameObject>& obj) {
                return obj->isDestroyed();
            }),
        gameObjects.end()
    );

    //add bullet to game
    for (auto& obj : toAddObjects) {
        obj->setTag("bullet");
        gameObjects.push_back(obj);
    }
    toAddObjects.clear();

    //update enemy
    spawnTimer += deltaTime;
    if (spawnTimer >= 3.0f) {
        spawnTimer = 0.0f;
        spawnRandomEnemy(); // Use helper for random enemy spawn
    }
}

void GamePlayScene::render(sf::RenderWindow& window) {
    for (auto& obj : gameObjects) {
        obj->render(window);
    }
}