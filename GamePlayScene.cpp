// GamePlayScene.cpp
#include "GamePlayScene.h"
#include "SelectLevelScene.h"
#include "SwitchSceneCommand.h"
#include "Button.h"
#include "Bullet.h"
#include "chasePlayerComponent.h"
#include "ShootComponent.h"



std::vector<std::shared_ptr<GameObject>> bullets;
GamePlayScene::GamePlayScene() {

    gameObjects.push_back(std::make_shared<Button>(
        "Back", 400, 400,
        std::make_shared<SwitchSceneCommand>([]() {
            return std::make_shared<SelectLevelScene>();
            })
    ));
    
    // add player
    auto player = GameObjectFactory::createPlayer();
    gameObjects.push_back(player);

    // add bullet spawn function
    auto spawnBullet = [this](const sf::Vector2f& pos, const sf::Vector2f& vel) {
        gameObjects.push_back(std::make_shared<Bullet>(pos, vel));
    };

    // add enemies
    gameObjects.push_back(GameObjectFactory::createEnemy(player, spawnBullet));
}


void GamePlayScene::update(float deltaTime)
{
    for (auto& obj : gameObjects)
    {
        obj->update(deltaTime);
    }
}

void GamePlayScene::render(sf::RenderWindow& window)
{
    for (auto& obj : gameObjects)
    {
        obj->render(window);
    }
}