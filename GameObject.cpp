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
    // Debug: Optionally log tag or type if needed
    // std::cout << "[DEBUG] Updating GameObject: " << tag << std::endl;
	this->updateComponents(deltaTime);
}

void GameObject::render(sf::RenderWindow& window)
{
    this->hitbox.setFillColor(sf::Color::Red); // Ensure the hitbox color is set before rendering
    window.draw(this->hitbox);
    for (const auto& component : this->components)
    {
        if (component)
        {
            component->render(window);
        }
    }
}

void GameObject::setTag(const std::string n_tag)
{
	this->tag = n_tag;
}

std::string GameObject::getTag()
{
	return this->tag;
}
