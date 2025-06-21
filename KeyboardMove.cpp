#include "KeyboardMove.h"
#include <SFML/Window/Keyboard.hpp>

KeyboardMove::KeyboardMove(std::shared_ptr<GameObject> owner, float speed)
    : Component(owner),
    speed(speed)
{
}

void KeyboardMove::update(float deltaTime)
{
    if (!owner) return;

    // Truy cập và di chuyển hitbox của GameObject
    sf::Vector2f movement(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        movement.y -= this->speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        movement.y += this->speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        movement.x -= this->speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        movement.x += this->speed * deltaTime;

    this->owner->move(movement);
}
