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
