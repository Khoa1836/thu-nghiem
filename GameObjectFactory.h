#pragma once

#include "Player.h"
#include "Config.h"
#include "KeyboardMove.h"
#include "CollideWithBounds.h"

class GameObjectFactory
{
public:
	static std::shared_ptr<Player> createPlayer();
};

// cái này là Factory Pattern để tạo ra các đối tượng GameObject