#include "Player.h"

Player::Player()
{
	hitbox.setSize(sf::Vector2f(50.f, 50.f));
	hitbox.setFillColor(sf::Color::Green);
	hitbox.setPosition(100.f, 100.f);
}

Player::~Player()
{
}

void Player::update(float deltaTime)
{
	// move using wasd
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		hitbox.move(0, -PLAYER_SPEED * deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		hitbox.move(0, PLAYER_SPEED * deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		hitbox.move(-PLAYER_SPEED * deltaTime, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		hitbox.move(PLAYER_SPEED * deltaTime, 0);
	}
}