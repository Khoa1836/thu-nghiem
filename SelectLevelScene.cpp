
// SelectLevelScene.cpp
#include "SelectLevelScene.h"
#include "GamePlayScene.h"
#include "SwitchSceneCommand.h"
#include "Button.h"

SelectLevelScene::SelectLevelScene() {
    gameObjects.push_back(std::make_shared<Button>(
        "Start Game", 300, 400,
        std::make_shared<SwitchSceneCommand>([]() {
            return std::make_shared<GamePlayScene>();
            })
    ));
}