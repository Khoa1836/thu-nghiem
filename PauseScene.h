
#pragma once
#include "Scene.h"
#include <memory>

    class GamePlayScene; // Forward declaration

    class ScenePause : public Scene
    {
    public:
        // Nhận thêm tham chiếu tới GamePlayScene
        ScenePause(std::shared_ptr<GamePlayScene> gameplayScene);
        void update(float deltaTime) override;
        void render(sf::RenderWindow& window) override;
    private:
        std::shared_ptr<GamePlayScene> gameplayScene;
    };

