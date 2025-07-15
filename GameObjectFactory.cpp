#include "GameObjectFactory.h"
#include "GameManager.h"
#include "Assets.h"

std::shared_ptr<Player> GameObjectFactory::createPlayer()
{
	auto player = std::make_shared<Player>();

	// bật tắt tùy ý các hành vi (component)
	player->addComponent(std::make_shared<KeyboardMove>(player, PLAYER_SPEED));
	//player->addComponent(std::make_shared<CollideWithBounds>(player));
	//player->addComponent(std::make_shared<Gravity>(player));
	player->addComponent(std::make_shared<Stat>(player, 100, 20));

	GameManager::getInstance().currentPlayer = player;
	return player;
}

std::shared_ptr<Enemies> GameObjectFactory::createEnemy()
{
	auto enemies = std::make_shared<Enemies>();

	// bật tắt tùy ý các hành vi (component)
	enemies->addComponent(std::make_shared<KeyboardMove>(enemies, PLAYER_SPEED, "arrows"));
	enemies->addComponent(std::make_shared<CollideWithBounds>(enemies));
	//player->addComponent(std::make_shared<Gravity>(player));
	enemies->addComponent(std::make_shared<Stat>(enemies, 100, 20));

	return enemies;
}
std::shared_ptr<Dog> GameObjectFactory::createDog()
{
	auto dog = std::make_shared<Dog>();

	dog->addComponent(std::make_shared<FollowTarget>(dog, GameManager::getInstance().currentPlayer, 50.f));
	//dog->addComponent(std::make_shared<CollideWithBounds>(dog));
	dog->addComponent(std::make_shared<Stat>(dog, 100, 20));

	return dog;
}

std::shared_ptr<Bullet> GameObjectFactory::createBullet(float x, float y)
{
	auto bullet = std::make_shared<Bullet>(x, y);

	auto player = GameManager::getInstance().currentPlayer;
	// get enemy closest to player
	std::shared_ptr<GameObject> enemy = nullptr;
	float distance = 1e9;
	for (auto i : GameManager::getInstance().getCurrentScene()->getGameObjects())
	{
		if (!isType<Dog>(i)) continue;

		float tmp = hypot(i->getHitbox().getPosition().x - player->getHitbox().getPosition().x,
			i->getHitbox().getPosition().y - player->getHitbox().getPosition().y);
		if (tmp < distance)
		{
			distance = tmp;
			enemy = i;
		}
	}

	if (enemy == nullptr)
	{
		enemy = std::make_shared<GameObject>();
		// set random position for target
		enemy->getHitbox().setPosition(rand() % 10000, rand() % 10000); // Assuming a window size of 800x600
	}

	bullet->addComponent(std::make_shared<FollowTarget>(bullet, enemy, 400.f));
	//bullet->addComponent(std::make_shared<MoveForward>(bullet, enemy->getHitbox().getOrigin(), 400.f));
	
	return bullet;
}


//https://github.com/Khoa1836/thu-nghiem.git
//https://github.com/Khoa1836/thu-nghiem.git