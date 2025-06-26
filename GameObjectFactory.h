#pragma once

#include "Player.h"
#include "Config.h"
#include "KeyboardMove.h"
#include "CollideWithBounds.h"
#include "Gravity.h"
#include "Enemy.h"
#include "Stat.h"
#include <functional>

class GameObjectFactory
{
public:
	static std::shared_ptr<Player> createPlayer();
	static std::shared_ptr<Enemy> createEnemy(
		std::shared_ptr<GameObject> player,
		std::function<void(const sf::Vector2f&, const sf::Vector2f&)> spawnBullet
	);
};