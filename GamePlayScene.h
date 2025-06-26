// GamePlayScene.h
#pragma once

#include "Scene.h"
#include "Player.h"

class GamePlayScene : public Scene {
public:
    GamePlayScene();
    void update(float deltaTime) override;

private:
    float spawnTimer = 0.0f;
};
