#include "KeyboardMove.h"
#include <SFML/Window/Keyboard.hpp>
#include "CollideWithBounds.h"
#include "GameManager.h"
#include "PlayerItemCollector.h"

KeyboardMove::KeyboardMove(std::shared_ptr<GameObject> owner, float speed, std::string mode)
    : Component(owner),
    speed(speed),
    mode(mode)
{
	if (mode == "arrows")
	{
		up = sf::Keyboard::Up;
		down = sf::Keyboard::Down;
		left = sf::Keyboard::Left;
		right = sf::Keyboard::Right;
	}
    else
    {
        // Mặc định là WASD nếu mode không hợp lệ
        up = sf::Keyboard::W;
        down = sf::Keyboard::S;
        left = sf::Keyboard::A;
        right = sf::Keyboard::D;
    }
}

void KeyboardMove::update(float deltaTime)
{
    if (!owner) return;

    // Debug: Optionally log player position or movement
    // if (owner->getTag() == "player") {
    //     std::cout << "[DEBUG] Player position: " 
    //               << owner->getHitbox().getPosition().x << ", "
    //               << owner->getHitbox().getPosition().y << std::endl;
    // }

    // Truy cập và di chuyển hitbox của GameObject
    sf::Vector2f movement(0.f, 0.f);

    auto collector = owner->getComponent<PlayerItemCollector>();
    float realSpeed = speed;
    if (collector && collector->isSpeedActive())
        realSpeed *= collector->getSpeedMultiplier();

    if (sf::Keyboard::isKeyPressed(this->up))
        movement.y -= realSpeed * deltaTime;
    if (sf::Keyboard::isKeyPressed(this->down))
        movement.y += realSpeed * deltaTime;
    if (sf::Keyboard::isKeyPressed(this->left))
        movement.x -= realSpeed * deltaTime;
    if (sf::Keyboard::isKeyPressed(this->right))
        movement.x += realSpeed * deltaTime;

    this->owner->move(movement);
}

