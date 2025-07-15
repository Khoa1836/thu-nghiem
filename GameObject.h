// GameObject.h
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Component.h"

class GameObject {
protected:
    sf::RectangleShape hitbox;
	std::vector<std::shared_ptr<Component>> components;

public:
    GameObject();
    virtual ~GameObject();

    void addComponent(std::shared_ptr<Component> component);
	void updateComponents(float deltaTime);

    bool needDeleted = false;

    sf::Vector2f getOrigin() const;
    void onCollisionEnter(std::shared_ptr<GameObject> other);

    template<class T>
    std::shared_ptr<T> getComponent();

    void move(sf::Vector2f offset);
    sf::RectangleShape& getHitbox();

    virtual void update(float deltaTime);
    virtual void render(sf::RenderWindow& window);
};

template<class T>
inline std::shared_ptr<T> GameObject::getComponent()
{
    for (const auto& component : components)
    {
        if (isType<T>(component))
        {
            return std::dynamic_pointer_cast<T>(component);
        }
    }
    return nullptr;
}
