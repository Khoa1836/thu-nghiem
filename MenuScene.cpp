// MenuScene.cpp
#include "MenuScene.h"
#include "SwitchSceneCommand.h"
#include "SelectLevelScene.h"
#include "Button.h"
#include "PrintCommand.h"

MenuScene::MenuScene() {
    gameObjects.push_back(std::make_shared<Button>(
        "Play", 100, 200,
        std::make_shared<SwitchSceneCommand>([]() {
            return std::make_shared<SelectLevelScene>();
            })
    ));

    gameObjects.push_back(std::make_shared<Button>("Print", 400, 500, std::make_shared<PrintCommand>("Hello World")));
}
