#pragma once

#include <SFML/Graphics.hpp>
#include "Config.h"
#include "MenuScene.h"
#include "GameManager.h"
#include <vector>

class Game
{
private:
	sf::RenderWindow* window;

	void pollEvent();
	void updateMousePosition();
public:
	Game();
	virtual ~Game();

	void run();

	void update(float deltaTime);
	void render(sf::RenderWindow& window);
};