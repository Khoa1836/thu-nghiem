#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::addComponent(std::shared_ptr<Component> component)
{
	this->components.push_back(component);
}

void GameObject::updateComponents(float deltaTime)
{
	for (auto& component : this->components)
	{
		if (component)
		{
			component->update(deltaTime);
		}
	}
}

void GameObject::move(sf::Vector2f offset)
{
	this->hitbox.move(offset);
}

sf::RectangleShape& GameObject::getHitbox()
{
	return this->hitbox;
}

void GameObject::update(float deltaTime)
{
	this->updateComponents(deltaTime);
}

void GameObject::render(sf::RenderWindow& window)
{
	window.draw(this->hitbox);
}
