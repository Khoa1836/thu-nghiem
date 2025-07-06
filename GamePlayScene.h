// GamePlayScene.h
#pragma once

#include "Scene.h"
#include "Player.h"
#include "SceneLose.h" // Ensure SceneLose is included
#include "Clock.h" // Include Clock
#include <memory>
#include <vector>

class GameObject;

class GamePlayScene : public Scene, public std::enable_shared_from_this<GamePlayScene> { // Kế thừa enable_shared_from_this
public:
    GamePlayScene();
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

    // Thêm hàm kiểm tra player còn sống
    bool alivePlayer();
    float getElapsedTime() const; // Thêm hàm lấy thời gian đã chơi
    void pauseClock();   // Thêm
    void resumeClock();  // Thêm

private:
    std::vector<std::shared_ptr<GameObject>> enemyPool; // Pool lưu trữ các enemy không hoạt động
    int maxEnemies = 50; // Số lượng kẻ thù tối đa
    float spawnTimer = 0.0f;
    std::vector<std::shared_ptr<GameObject>> toAddObjects;

    void spawnRandomEnemy(bool isShooter); // Add this helper method

    // Thêm hàm tiện ích để lấy player theo tag
    //std::shared_ptr<GameObject> findPlayer();

    std::shared_ptr<Clock> clockInGame; // Thay đổi từ ClockInGame sang Clock
    static sf::Font font;
    static bool fontLoaded;
};
