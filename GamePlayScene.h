// GamePlayScene.h
#pragma once

#include "Scene.h"
#include "Player.h"

class GamePlayScene : public Scene {
public:
    GamePlayScene();
    bool holding = false;

    void update(float deltaTime) override;
};
