#pragma once
#include "Scene.h"
#include <memory>

class GamePlayScene;

class SceneLose : public Scene
{
public:
    // Nhận shared_ptr<GamePlayScene> để render phía sau nếu muốn
    SceneLose(std::shared_ptr<GamePlayScene> n_gameplayScene);
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
private:
    std::shared_ptr<GamePlayScene> gamePlayScene;
    std::string timeString; // Thêm biến lưu thời gian
};