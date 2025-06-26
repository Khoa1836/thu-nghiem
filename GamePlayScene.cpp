// GamePlayScene.cpp
#include <random>
#include "GamePlayScene.h"
#include "SelectLevelScene.h"
#include "SwitchSceneCommand.h"
#include "Button.h"
#include "DamageOnContact.h"
#include "FollowTarget.h"
#include "NoOverlapEnemiesOnly.h"

GamePlayScene::GamePlayScene() {
    gameObjects.push_back(std::make_shared<Button>(
        "Back", 100, 600, sf::Vector2f(50.f, 50.f),
        std::make_shared<SwitchSceneCommand>([]() {
            return std::make_shared<SelectLevelScene>();
        })
    ));

    auto player = GameObjectFactory::createPlayer();
    auto enemy = GameObjectFactory::createEnemy();

    enemy->addComponent(std::make_shared<DamageOnContact>(enemy, player, 10.f, 1.0f));
    enemy->addComponent(std::make_shared<FollowTarget>(enemy, player, 80.f));
    enemy->addComponent(std::make_shared<NoOverlapEnemiesOnly>(enemy, &gameObjects));

    gameObjects.push_back(player);
    gameObjects.push_back(enemy);
}

void GamePlayScene::update(float deltaTime) {
    for (auto& obj : gameObjects) {
        obj->update(deltaTime);
    }

    spawnTimer += deltaTime;
    if (spawnTimer >= 3.0f) {
        spawnTimer = 0.0f;

        // Random trong 1280x720
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<float> distX(0.f, 1230.f); // 1280 
        std::uniform_real_distribution<float> distY(0.f, 670.f);  // 720 

        auto player = gameObjects[1];
        auto newEnemy = GameObjectFactory::createEnemy();
        newEnemy->getHitbox().setPosition(distX(gen), distY(gen));
        newEnemy->addComponent(std::make_shared<DamageOnContact>(newEnemy, player, 10.f, 1.0f));
        newEnemy->addComponent(std::make_shared<FollowTarget>(newEnemy, player, 80.f));
        newEnemy->addComponent(std::make_shared<NoOverlapEnemiesOnly>(newEnemy, &gameObjects));
        gameObjects.push_back(newEnemy);
    }
}