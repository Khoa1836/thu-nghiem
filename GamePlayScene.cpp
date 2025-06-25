
// GamePlayScene.cpp
#include "GamePlayScene.h"
#include "SelectLevelScene.h"
#include "SwitchSceneCommand.h"
#include "Button.h"

GamePlayScene::GamePlayScene() {
    gameObjects.push_back(std::make_shared<Button>(
        "Back", 100, 600, sf::Vector2f(50.f, 50.f),
        std::make_shared<SwitchSceneCommand>([]() {
            return std::make_shared<SelectLevelScene>();
            })
    ));
    
    // add player
	gameObjects.push_back(GameObjectFactory::createPlayer());
    gameObjects.push_back(GameObjectFactory::createEnemy());
}