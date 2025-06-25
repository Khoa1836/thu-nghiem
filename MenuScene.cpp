// MenuScene.cpp
#include "MenuScene.h"
#include "SwitchSceneCommand.h"
#include "SelectLevelScene.h"
#include "Button.h"
#include "PrintCommand.h"
#include <SFML/Graphics.hpp>


MenuScene::MenuScene() {
    gameObjects.push_back(std::make_shared<Button>(
        "Play", 550, 200, sf::Vector2f(200.f, 100.f),
        std::make_shared<SwitchSceneCommand>([]() {
            return std::make_shared<SelectLevelScene>();
            })
    ));

    /*gameObjects.push_back(std::make_shared<Button>(
        "Print", 500, 500, sf::Vector2f(100.f, 100.f),
        std::make_shared<SwitchSceneCommand>([]()
            {
                return std::make_shared<SelectLevelScene>();
            })
    ));*/
}
