#include "SceneLose.h"
#include "SwitchSceneCommand.h"
#include "Button.h"
#include "GamePlayScene.h"
#include "SelectLevelScene.h"
#include "MenuScene.h"
#include <SFML/Graphics.hpp>
#include <sstream>


SceneLose::SceneLose(std::shared_ptr<GamePlayScene> n_gameplayScene)
    : gamePlayScene(n_gameplayScene)
{
    // Lấy thời gian chơi từ gameplayScene và định dạng MM:SS
    int elapsed;
    if (gamePlayScene) {
        elapsed = static_cast<int>(gamePlayScene->getElapsedTime());
    }
    else {
        elapsed = 0;
    }
    int minutes = elapsed / 60;
    int seconds = elapsed % 60;
    std::ostringstream oss;
    oss << "Time: ";
    if (minutes < 10) oss << '0';
    oss << minutes << ":";
    if (seconds < 10) oss << '0';
    oss << seconds;
    timeString = oss.str();

    // Nút Retry: tạo lại GamePlayScene mới
    gameObjects.push_back(std::make_shared<Button>(
        "Retry", 540, 250, sf::Vector2f(200.f, 60.f),
        std::make_shared<SwitchSceneCommand>([]() {
            return std::make_shared<GamePlayScene>();
        })
    ));
    // Nút Menu: về menu chính
    gameObjects.push_back(std::make_shared<Button>(
        "Menu", 540, 350, sf::Vector2f(200.f, 60.f),
        std::make_shared<SwitchSceneCommand>([]() {
            return std::make_shared<MenuScene>();
        })
    ));
}

void SceneLose::update(float deltaTime) {
    for (auto& obj : gameObjects) obj->update(deltaTime);
}

void SceneLose::render(sf::RenderWindow& window) {
    // Vẽ lại gameplay scene phía sau nếu muốn
    if (gamePlayScene) gamePlayScene->render(window);

    // Vẽ lớp phủ bán trong suốt lên toàn bộ cửa sổ để làm mờ nền khi thua
    sf::RectangleShape overlay(sf::Vector2f(window.getSize()));
    overlay.setFillColor(sf::Color(0, 0, 0, 180)); // 180: bán trong suốt, tối hơn pause
    window.draw(overlay);

    // Hiển thị chữ "Game Over" ở trên cùng
    sf::Font font;
    font.loadFromFile("arial.ttf"); // Đảm bảo có font này
    sf::Text gameOverText("Game Over", font, 48);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setStyle(sf::Text::Bold);
    gameOverText.setPosition(530,  40);
    window.draw(gameOverText);

    // Hiển thị thời gian chơi với định dạng MM:SS
    sf::Text text(timeString, font, 32);
    text.setFillColor(sf::Color::Red);
    text.setPosition(550, 180);
    window.draw(text);

    // Sau đó vẽ các đối tượng giao diện (nút Retry, Menu) lên trên lớp phủ
    for (auto& obj : gameObjects) obj->render(window);
}