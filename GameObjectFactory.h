#pragma once

#include "Player.h"
#include "Config.h"
#include "KeyboardMove.h"
#include "CollideWithBounds.h"
#include "Gravity.h"
#include "Stat.h"
#include "Enemies.h"
#include "DamageOnContact.h"
#include "FollowTarget.h"
#include "NoOverlapEnemiesOnly.h"
#include "GameObject.h"
#include "Bullet.h"

class GameObjectFactory
{
public:
	static std::shared_ptr<Player> createPlayer(
		std::vector<std::shared_ptr<GameObject>>* gameObjects,
		std::vector<std::shared_ptr<GameObject>>* toAddObjects );
	static std::shared_ptr<Enemies> createEnemy(
		std::shared_ptr<GameObject> player,
		std::vector<std::shared_ptr<GameObject>>* gameObjects);
	//static std::shared_ptr<Bullet> createBullet(sf::Vector2f pos, sf::Vector2f vel);
};

// cái này là Factory Pattern để tạo ra các đối tượng GameObject