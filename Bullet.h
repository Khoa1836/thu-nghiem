#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
class Bullet : public GameObject
{
private:
	sf::Vector2f velocity;
public:
	Bullet(sf::Vector2f velocity, sf::Vector2f position);

	void update(float deltaTime);
	void render(sf::RenderWindow& window);
};

