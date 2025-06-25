
// SelectLevelScene.cpp
#include "SelectLevelScene.h"
#include "GamePlayScene.h"
#include "SwitchSceneCommand.h"
#include "Button.h"
#include "MenuScene.h"

SelectLevelScene::SelectLevelScene() {
    gameObjects.push_back(std::make_shared<Button>(
        "Game 1", 550, 200,sf::Vector2f(200.f,100.f),
        std::make_shared<SwitchSceneCommand>([]() {
            return std::make_shared<GamePlayScene>();
            })
    ));
    
    gameObjects.push_back( std::make_shared<Button>(
        "Back 2", 300, 600, sf::Vector2f(150.f, 50.f),
        std::make_shared<SwitchSceneCommand>([]() {
            return std::make_shared<MenuScene>();
            })
    ));
}