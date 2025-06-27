#include "GameObjectFactory.h"
#include "GameObject.h"
#include "FireComponent.h"
#include "CollideWithBullet.h"
std::shared_ptr<Player> GameObjectFactory::createPlayer(
    std::vector<std::shared_ptr<GameObject>>* gameObjects,
    std::vector<std::shared_ptr<GameObject>>* toAddObjects)
{
    auto player = std::make_shared<Player>();
    player->addComponent(std::make_shared<KeyboardMove>(player, PLAYER_SPEED));
    player->addComponent(std::make_shared<CollideWithBounds>(player));
    player->addComponent(std::make_shared<Stat>(player, 100, 20));

    auto fireComponent = std::make_shared<FireComponent>(
        player,
        gameObjects,
        toAddObjects,
        1.f,
        sf::Vector2f(0.f,-600.f)
    );
    player->addComponent(fireComponent);

    return player;
}


std::shared_ptr<Enemies> GameObjectFactory::createEnemy(std::shared_ptr<GameObject> player, std::vector<std::shared_ptr<GameObject>>* gameObjects)
{
	auto enemies = std::make_shared<Enemies>();
    enemies->setTag("enemies");

	// add enemy component 
	enemies->addComponent(std::make_shared<CollideWithBounds>(enemies));
	enemies->addComponent(std::make_shared<Stat>(enemies, 100, 20));
	enemies->addComponent(std::make_shared<DamageOnContact>(enemies, player, 10.f, 1.0f));
	enemies->addComponent(std::make_shared<FollowTarget>(enemies, player, 80.f));
	enemies->addComponent(std::make_shared<NoOverlapEnemiesOnly>(enemies, gameObjects));
    enemies->addComponent(std::make_shared<CollideWithBullet>(enemies, gameObjects, 10));
	return enemies;
}



