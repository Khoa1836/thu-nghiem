#include "Player.h"
#include "Assets.h"

Player::Player()
{
	hitbox.setSize(sf::Vector2f(39.f, 57.f));
	hitbox.setFillColor(sf::Color::Green);
	hitbox.setPosition(100.f, 100.f);

	animations.push_back(std::make_shared<Animation>(Assets::PLAYER_TEXTURE, 4, 0.1f, sf::Vector2i(13, 19)));
	animations[INT(PLAYER_STATE::IDLE)]->setScale(sf::Vector2f(3, 3));
}

Player::~Player()
{
}