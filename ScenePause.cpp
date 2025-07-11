﻿#include "ScenePause.h"
#include "Button.h"
#include "SwitchSceneCommand.h"
#include "GamePlayScene.h"
#include "MenuScene.h"
#include "SelectLevelScene.h"
#include <SFML/Graphics.hpp>
#include <sstream>

// Constructor: lưu lại gameplayScene để resume
ScenePause::ScenePause(std::shared_ptr<GamePlayScene> gameplayScene)
    : gamePlayScene(gameplayScene)
{
    // Pause clock ngay khi vào scene pause
    if (gamePlayScene && !wasPaused_) {
        gamePlayScene->pauseClock();
        wasPaused_ = true;
    }

    // Resume button: resume lại gameplayScene cũ
    gameObjects.push_back(std::make_shared<Button>(
        "Resume", 540, 250, sf::Vector2f(200.f, 60.f),
        // Resume clock khi tiếp tục
        std::make_shared<SwitchSceneCommand>([scene = gamePlayScene]() {
            if (scene) scene->resumeClock();
            return scene;
        })
    ));
    // Level button
    gameObjects.push_back(std::make_shared<Button>(
        "Menu", 540, 350, sf::Vector2f(200.f, 60.f),
        std::make_shared<SwitchSceneCommand>([]() {
            return std::make_shared<SelectLevelScene>();
        })
    ));
}

void ScenePause::update(float deltaTime) {
    for (auto& obj : gameObjects) obj->update(deltaTime);
}

void ScenePause::render(sf::RenderWindow& window) {
    // Vẽ lại gameplay scene phía sau
    if (gamePlayScene) gamePlayScene->render(window);

    // Vẽ lớp phủ bán trong suốt lên toàn bộ cửa sổ để làm mờ nền khi pause
    sf::RectangleShape overlay(sf::Vector2f(window.getSize()));
    overlay.setFillColor(sf::Color(0, 0, 0, 128)); // 128: bán trong suốt
    window.draw(overlay);

    // Hiển thị thời gian tạm dừng với định dạng MM:SS
    if (gamePlayScene) {
        int elapsed = static_cast<int>(gamePlayScene->getElapsedTime());
        int minutes = elapsed / 60;
        int seconds = elapsed % 60;
        sf::Font font;
        font.loadFromFile("arial.ttf");
        std::ostringstream oss;
        oss << "Time: ";
        if (minutes < 10) oss << '0';
        oss << minutes << ":";
        if (seconds < 10) oss << '0';
        oss << seconds;
        sf::Text text(oss.str(), font, 28);
        text.setFillColor(sf::Color::White);
        text.setPosition(555, 180);
        window.draw(text);
    }

    // Sau đó vẽ các đối tượng giao diện (nút Resume, Menu) lên trên lớp phủ
    for (auto& obj : gameObjects) obj->render(window);
}
