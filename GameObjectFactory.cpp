#include "GameObjectFactory.h"

std::shared_ptr<Player> GameObjectFactory::createPlayer()
{
	auto player = std::make_shared<Player>();

	// bật tắt tùy ý các hành vi (component)
	player->addComponent(std::make_shared<KeyboardMove>(player, PLAYER_SPEED));
	player->addComponent(std::make_shared<CollideWithBounds>(player));
	//player->addComponent(std::make_shared<Gravity>(player));
	player->addComponent(std::make_shared<Stat>(player, 100, 20));

	return player;
}

std::shared_ptr<Enemies> GameObjectFactory::createEnemy()
{
	auto enemies = std::make_shared<Enemies>();

	// bật tắt tùy ý các hành vi (component)
	//enemies->addComponent(std::make_shared<KeyboardMove>(enemies, PLAYER_SPEED));
	enemies->addComponent(std::make_shared<CollideWithBounds>(enemies));
	//player->addComponent(std::make_shared<Gravity>(player));
	enemies->addComponent(std::make_shared<Stat>(enemies, 100, 20));

	return enemies;
}
https://github.com/Khoa1836/thu-nghiem.git
https://github.com/Khoa1836/thu-nghiem.git