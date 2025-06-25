#pragma once

#include "Player.h"
#include "Config.h"
#include "KeyboardMove.h"
#include "CollideWithBounds.h"
#include "Gravity.h"
#include "Stat.h"
#include "Enemies.h"

class GameObjectFactory
{
public:
	static std::shared_ptr<Player> createPlayer();
	static std::shared_ptr<Enemies> createEnemy();
};

// cái này là Factory Pattern để tạo ra các đối tượng GameObject