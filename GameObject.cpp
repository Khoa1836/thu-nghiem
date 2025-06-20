#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::update(float deltaTime)
{
}

void GameObject::render(sf::RenderWindow& window)
{
	window.draw(this->hitbox);
}
