#include "ScenePause.h"
#include "Button.h"
#include "SwitchSceneCommand.h"
#include "GamePlayScene.h"
#include "MenuScene.h"

// Constructor: add resume and menu buttons
ScenePause::ScenePause(std::shared_ptr<GamePlayScene> gameplayScene)
    : gameplayScene(gameplayScene)
{
    // Resume button
    gameObjects.push_back(std::make_shared<Button>(
        "Resume", 540, 250, sf::Vector2f(200.f, 60.f),
        std::make_shared<SwitchSceneCommand>([gameplayScene]() {
            return gameplayScene; // Quay lại scene gameplay cũ
            })
    ));
    // Menu button
    gameObjects.push_back(std::make_shared<Button>(
        "Menu", 540, 350, sf::Vector2f(200.f, 60.f),
        std::make_shared<SwitchSceneCommand>([]() {
            return std::make_shared<MenuScene>();
            })
    ));
}

void ScenePause::update(float deltaTime) {
    for (auto& obj : gameObjects) obj->update(deltaTime);
}

void ScenePause::render(sf::RenderWindow& window) {
    // Vẽ lại gameplay scene phía sau
    if (gameplayScene) gameplayScene->render(window);

    // Vẽ lớp phủ bán trong suốt lên toàn bộ cửa sổ để làm mờ nền khi pause
    sf::RectangleShape overlay(sf::Vector2f(window.getSize()));
    overlay.setFillColor(sf::Color(0, 0, 0, 128)); // 128: bán trong suốt
    window.draw(overlay);

    // Sau đó vẽ các đối tượng giao diện (nút Resume, Menu) lên trên lớp phủ
    for (auto& obj : gameObjects) obj->render(window);
}
