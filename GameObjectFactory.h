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
#include "ShooterEnemy.h"

class GameObjectFactory
{
public:
	static std::shared_ptr<Player> createPlayer(
		std::vector<std::shared_ptr<GameObject>>* gameObjects,
		std::vector<std::shared_ptr<GameObject>>* toAddObjects );

	static std::shared_ptr<Enemies> createEnemy(
		std::shared_ptr<GameObject> player,
		std::vector<std::shared_ptr<GameObject>>* gameObjects,
		std::vector<std::shared_ptr<GameObject>>* toAddObjects);

	static std::shared_ptr<ShooterEnemy> createShooterEnemy(
		std::shared_ptr<GameObject> player,
		std::vector<std::shared_ptr<GameObject>>* gameObjects,
		std::vector<std::shared_ptr<GameObject>>* toAddObjects);
};

// cái này là Factory Pattern để tạo ra các đối tượng GameObject