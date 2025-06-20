// GameObject.h
#pragma once

#include <SFML/Graphics.hpp>

class GameObject {
protected:
    sf::RectangleShape hitbox;

public:
    GameObject();
    virtual ~GameObject();

    virtual void update(float deltaTime);
    virtual void render(sf::RenderWindow& window);
};