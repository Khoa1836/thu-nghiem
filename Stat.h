#pragma once

#include "Component.h"

class Stat : public Component
{
private:
	float health;
	float damage;

	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	sf::Vector2f deceleration; // trái nghĩa với gia tốc, giống lực ma sát cho nó dừng lại

	sf::Vector2f offset;
	sf::RectangleShape healthBar;

public:
	Stat(std::shared_ptr<GameObject> owner, float health = 100.f, float damage = 10.f);
	void takeDamage(float amount);
	void update(float deltaTime) override;
	void render(sf::RenderWindow& window) override;
<<<<<<< hieu
	void takeDamage(float amount);
};

=======
};
>>>>>>> main
