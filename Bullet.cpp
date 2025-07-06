#include "Bullet.h"

Bullet::Bullet(sf::Vector2f velocity, sf::Vector2f position, float damage) :
velocity(velocity), damage(damage)
{
	hitbox.setSize(sf::Vector2f(8.f,8.f));
	hitbox.setFillColor(sf::Color::Blue);
	hitbox.setPosition(position);
}

void Bullet::update(float deltaTime)
{
	hitbox.move(this->velocity * deltaTime);

	//giai phong cac vien dan neu cham vao thanh
	sf::Vector2f pos = getHitbox().getPosition();
	if (pos.x < 0 || pos.x > WINDOW_WIDTH || pos.y < 0 || pos.y > WINDOW_HEIGHT) {
		markForDestroy();
	}
}

void Bullet::render(sf::RenderWindow& window) 
{
	window.draw(hitbox);
}	