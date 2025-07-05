#include "GameObjectFactory.h"
#include "GameObject.h"
#include "FireComponent.h"
#include "CollideWithBullet.h"
#include "ShooterEnemy.h"
#include "ShooterFireComponent.h"
#include "CollideWithEnemyBullet.h"
#include "PlayerStat.h"
#include "PlayerCollectGemComponent.h"
#include "PlayerItemCollector.h"


std::shared_ptr<Player> GameObjectFactory::createPlayer(
    std::vector<std::shared_ptr<GameObject>>* gameObjects,
    std::vector<std::shared_ptr<GameObject>>* toAddObjects)
{
    auto player = std::make_shared<Player>();
    player->setTag("player");
    player->addComponent(std::make_shared<PlayerStat>(player));
    player->addComponent(std::make_shared<KeyboardMove>(player, PLAYER_SPEED));
    player->addComponent(std::make_shared<CollideWithBounds>(player));
    player->addComponent(std::make_shared<Stat>(player, 100, 50));

    // REMOVE n_bulletVelocity argument
    player->addComponent(std::make_shared<FireComponent>(
        player, gameObjects, toAddObjects, 0.5f));

    player->addComponent(std::make_shared<PlayerCollectGemComponent>(player, gameObjects));
    player->addComponent(std::make_shared<PlayerItemCollector>(player, gameObjects));

    return player;
}



std::shared_ptr<Enemies> GameObjectFactory::createEnemy(
    std::shared_ptr<GameObject> player,
    std::vector<std::shared_ptr<GameObject>>* gameObjects, 
    std::vector<std::shared_ptr<GameObject>>* toAddObjects)
{
	auto default_enemies = std::make_shared<Enemies>();
    default_enemies->setTag("default_enemies");

	// add enemy component 
    default_enemies->addComponent(std::make_shared<CollideWithBounds>(default_enemies));
    default_enemies->addComponent(std::make_shared<Stat>(default_enemies, 100, 20));
    default_enemies->addComponent(std::make_shared<DamageOnContact>(default_enemies, player, 10.f, 1.0f));
    default_enemies->addComponent(std::make_shared<FollowTarget>(default_enemies, player, 80.f));
    default_enemies->addComponent(std::make_shared<NoOverlapEnemiesOnly>(default_enemies, gameObjects));
    default_enemies->addComponent(std::make_shared<CollideWithBullet>(default_enemies, gameObjects, 10.f, toAddObjects));
	return default_enemies;
}

std::shared_ptr<ShooterEnemy> GameObjectFactory::createShooterEnemy(
    std::shared_ptr<GameObject> player,
    std::vector<std::shared_ptr<GameObject>>* gameObjects,
    std::vector<std::shared_ptr<GameObject>>* toAddObjects)
{
    auto shooter = std::make_shared<ShooterEnemy>();
    shooter->setTag("shooter_enemies");

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
        0.5f));
    return shooter;
}



