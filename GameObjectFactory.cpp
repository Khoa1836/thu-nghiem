#include "GameObjectFactory.h"
#include "ChasePlayerComponent.h"
#include "Enemy.h"
#include "ShootComponent.h"

std::shared_ptr<Player> GameObjectFactory::createPlayer()
{
	auto player = std::make_shared<Player>();

	// bật tắt tùy ý các hành vi (component)
	player->addComponent(std::make_shared<KeyboardMove>(player, PLAYER_SPEED));
	player->addComponent(std::make_shared<CollideWithBounds>(player));
	/*player->addComponent(std::make_shared<Gravity>(player));*/
	player->addComponent(std::make_shared<Stat>(player, 100, 20));

	return player;
}

std::shared_ptr<Enemy> GameObjectFactory::createEnemy(
    std::shared_ptr<GameObject> player,
    std::function<void(const sf::Vector2f&, const sf::Vector2f&)> spawnBullet)
{
    auto enemy = std::make_shared<Enemy>();
    enemy->getHitbox().setSize(sf::Vector2f(40, 40));
    enemy->getHitbox().setFillColor(sf::Color::Red);
    enemy->getHitbox().setPosition(300, 100);
    /*enemy->addComponent(std::make_shared<CollideWithBounds>(enemy));*/
    enemy->addComponent(std::make_shared<ChasePlayerComponent>(enemy, player, 80.f));
    enemy->addComponent(std::make_shared<ShootComponent>(enemy, 1.0f, spawnBullet));
    return enemy;
}
