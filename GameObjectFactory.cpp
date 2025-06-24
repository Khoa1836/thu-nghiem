#include "GameObjectFactory.h"

std::shared_ptr<Player> GameObjectFactory::createPlayer()
{
	auto player = std::make_shared<Player>();

	// bật tắt tùy ý các hành vi (component)
	player->addComponent(std::make_shared<KeyboardMove>(player, PLAYER_SPEED));
	player->addComponent(std::make_shared<CollideWithBounds>(player));
	player->addComponent(std::make_shared<Gravity>(player));
	player->addComponent(std::make_shared<Stat>(player));

	return player;
}
