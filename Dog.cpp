#include "Dog.h"

Dog::Dog()
{
	hitbox.setSize(sf::Vector2f(50.f, 50.f));
	hitbox.setFillColor(sf::Color::Red);
	hitbox.setPosition(200.f, 200.f);
}

Dog::~Dog()
{
}
