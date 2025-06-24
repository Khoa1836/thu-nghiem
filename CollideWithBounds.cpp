#include "CollideWithBounds.h"
#include "GameObject.h"

CollideWithBounds::CollideWithBounds(std::shared_ptr<GameObject> owner) :
	Component(owner)
{
}

void CollideWithBounds::sayHello()
{
	std::cout << "hello";
}

void CollideWithBounds::update(float deltaTime)
{
	if (!owner) return;
	sf::RectangleShape& hitbox = this->owner->getHitbox();
	sf::Vector2f position = hitbox.getPosition();
	sf::Vector2f size = hitbox.getSize();
	// Kiểm tra va chạm với biên giới của cửa sổ
	if (position.x < 0) {
		hitbox.setPosition(0, position.y);
	}
	else if (position.x + size.x > WINDOW_WIDTH) {
		hitbox.setPosition(WINDOW_WIDTH - size.x, position.y);
	}
	if (position.y < 0) {
		hitbox.setPosition(position.x, 0);
	}
	else if (position.y + size.y > WINDOW_HEIGHT) {
		hitbox.setPosition(position.x, WINDOW_HEIGHT - size.y);
	}
}