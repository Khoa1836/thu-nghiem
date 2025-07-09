
// GamePlayScene.cpp
#include "GamePlayScene.h"
#include "SelectLevelScene.h"
#include "SwitchSceneCommand.h"
#include "Button.h"

GamePlayScene::GamePlayScene() {
    gameObjects.push_back(std::make_shared<Button>(
        "Back", 100, 600, sf::Vector2f(50.f, 50.f),
        std::make_shared<SwitchSceneCommand>([]() {
            return std::make_shared<SelectLevelScene>();
            })
    ));
    
    // add player
	gameObjects.push_back(GameObjectFactory::createPlayer());
    //gameObjects.push_back(GameObjectFactory::createEnemy());

	gameObjects.push_back(GameObjectFactory::createDog());
}

void GamePlayScene::update(float deltaTime)
{
    Scene::update(deltaTime);

	this->camera.update(deltaTime, GameManager::getInstance().currentPlayer->getHitbox().getPosition());

	// spawn enemies when press space bar
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (holding == false)
		{
			holding = true;
			auto dog = GameObjectFactory::createDog();
			dog->getHitbox().setPosition(sf::Vector2f(rand() % (WINDOW_WIDTH - 50), rand() % (WINDOW_HEIGHT - 50)));
			gameObjects.push_back(dog);
			GameManager::getInstance().justPressed = false;
		}
	}
	else holding = false;

	// spawn bullet when press mouse left button
	if (GameManager::getInstance().isMousePressed())
	{
		auto player = GameManager::getInstance().currentPlayer;
		if (player)
		{
			auto bullet = GameObjectFactory::createBullet(player->getHitbox().getPosition().x, player->getHitbox().getPosition().y);
			gameObjects.push_back(bullet);
		}
	}
}
