#include "CollideWithBullet.h"
#include "GameObject.h"
#include "Stat.h"

CollideWithBullet::CollideWithBullet(std::shared_ptr<GameObject> owner,
	std::vector<std::shared_ptr<GameObject>>* n_gameObjects,
	float n_damage):
	Component(owner), gameObjects(n_gameObjects),
	damage(n_damage)
{
}

void CollideWithBullet::update(float deltaTime)
{
	auto stat = owner->getComponent<Stat>();
	float damagePlayer = stat->getDamage();
	damage = damagePlayer;
	for (auto& bullet : *gameObjects)
	{
		if (bullet->getTag() != "bullet") continue;
		for (auto& enemies : *gameObjects)
		{
			if (enemies->getTag() != "enemies") continue;
			if (bullet->getHitbox().getGlobalBounds().
				intersects(enemies->getHitbox().getGlobalBounds()))
			{
				std::cout << "Bullet hit enemy!\n";
				auto stat = enemies->getComponent<Stat>();
				if (stat)
				{
					stat->takeDamage(damage);
				}

				//bullet->markForDestroy();
				// Nếu máu <= 0, có thể gọi: enemy->markForDestroy();
			}
			
		}
	}
}
