#pragma once

#include "Player.h"
#include "Config.h"
#include "KeyboardMove.h"
#include "CollideWithBounds.h"
#include "Gravity.h"
#include "Stat.h"
#include "Enemies.h"
#include "Dog.h"
#include "FollowTarget.h"
#include "Bullet.h"
#include "MoveForward.h"
#include "Animation.h"

class GameObjectFactory
{
public:
	static std::shared_ptr<Player> createPlayer();
	static std::shared_ptr<Enemies> createEnemy();
	static std::shared_ptr<Dog> createDog();
	static std::shared_ptr<Bullet> createBullet(float x, float y);
};

// cái này là Factory Pattern để tạo ra các đối tượng GameObject