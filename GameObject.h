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

    void move(sf::Vector2f offset);
    sf::RectangleShape& getHitbox();

    virtual void update(float deltaTime);
    virtual void render(sf::RenderWindow& window);
};