// MenuScene.cpp
#include "MenuScene.h"
#include "SwitchSceneCommand.h"
#include "SelectLevelScene.h"
#include "Button.h"

MenuScene::MenuScene() {
    gameObjects.push_back(std::make_shared<Button>(
        "Play", 100, 200,
        std::make_shared<SwitchSceneCommand>([]() {
            return std::make_shared<SelectLevelScene>();
            })
    ));
}