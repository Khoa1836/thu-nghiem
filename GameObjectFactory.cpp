#include "GameObjectFactory.h"
#include "GameObject.h"
#include "FireComponent.h"
#include "CollideWithBullet.h"
#include "ShooterEnemy.h"
#include "ShooterFireComponent.h"
#include "CollideWithEnemyBullet.h"
#include "PlayerItemCollector.h"

std::shared_ptr<Player> GameObjectFactory::createPlayer(
    std::vector<std::shared_ptr<GameObject>>* gameObjects,
    std::vector<std::shared_ptr<GameObject>>* toAddObjects)
{
    auto player = std::make_shared<Player>();
    player->setTag("player");
    player->addComponent(std::make_shared<KeyboardMove>(player, PLAYER_SPEED));
    player->addComponent(std::make_shared<CollideWithBounds>(player));
    player->addComponent(std::make_shared<Stat>(player, 100, 50));

    auto fireComponent = std::make_shared<FireComponent>(
        player, gameObjects,toAddObjects,1.f,sf::Vector2f(0.f,-600.f));
        player,
        gameObjects,
        toAddObjects,
        0.8f,
        sf::Vector2f(0.f,-600.f)
    );

    player->addComponent(fireComponent);
    player->addComponent(std::make_shared<CollideWithEnemyBullet>(player, gameObjects));
    player->addComponent(std::make_shared<PlayerItemCollector>(player, gameObjects));

    return player;
}


std::shared_ptr<Enemies> GameObjectFactory::createEnemy(std::shared_ptr<GameObject> player,
std::vector<std::shared_ptr<GameObject>>* gameObjects,
std::vector<std::shared_ptr<GameObject>>* toAddObjects )
{
	auto enemies = std::make_shared<Enemies>();
    enemies->setTag("enemies");

	// add enemy component 
	enemies->addComponent(std::make_shared<CollideWithBounds>(enemies));
	enemies->addComponent(std::make_shared<Stat>(enemies, 100, 20));
	enemies->addComponent(std::make_shared<DamageOnContact>(enemies, player, 10.f, 1.0f));
	enemies->addComponent(std::make_shared<FollowTarget>(enemies, player, 80.f));
	enemies->addComponent(std::make_shared<NoOverlapEnemiesOnly>(enemies, gameObjects));
    /*enemies->addComponent(std::make_shared<CollideWithBullet>(enemies, gameObjects, 10));*/

    enemies->addComponent(std::make_shared<CollideWithBullet>(enemies, gameObjects, 10.f, toAddObjects));
	return enemies;
}

std::shared_ptr<ShooterEnemy> GameObjectFactory::createShooterEnemy(
    std::shared_ptr<GameObject> player,
    std::vector<std::shared_ptr<GameObject>>* gameObjects,
    std::vector<std::shared_ptr<GameObject>>* toAddObjects)
{
    auto shooter = std::make_shared<ShooterEnemy>();
    shooter->setTag("enemies");

    shooter->addComponent(std::make_shared<CollideWithBounds>(shooter));
    shooter->addComponent(std::make_shared<Stat>(shooter, 100, 20));
    shooter->addComponent(std::make_shared<DamageOnContact>(shooter, player, 10.f, 1.0f));
    shooter->addComponent(std::make_shared<FollowTarget>(shooter, player, 80.f));
    shooter->addComponent(std::make_shared<NoOverlapEnemiesOnly>(shooter, gameObjects));
    shooter->addComponent(std::make_shared<CollideWithBullet>(shooter, gameObjects, 10.f, toAddObjects));
    shooter->addComponent(std::make_shared<ShooterFireComponent>(
        shooter,
        gameObjects,
        toAddObjects,
        2.0f, // cooldown
        sf::Vector2f(0.f, 600.f) // hướng mặc định, sẽ được tính lại về phía player
    ));
    return shooter;
}



