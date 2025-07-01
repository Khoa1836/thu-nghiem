#include "CollideWithBullet.h"
#include "GameObject.h"
#include "Stat.h"
#include "Bullet.h"

CollideWithBullet::CollideWithBullet(std::shared_ptr<GameObject> owner,
	std::vector<std::shared_ptr<GameObject>>* n_gameObjects,
	float n_damage):
	Component(owner), gameObjects(n_gameObjects),
	damage(n_damage)
{
}

void CollideWithBullet::update(float deltaTime)
{
	for (auto& bullet : *gameObjects)
	{
		if (bullet->getTag() != "bullet" || bullet->isDestroyed()) continue;
		float damage = 10.f;
		auto bulletPtr = std::dynamic_pointer_cast<Bullet>(bullet);
		if (bulletPtr) {
			damage = bulletPtr->getDamage();
		}
		for (auto& enemies : *gameObjects)
		{
			if (enemies->getTag() != "enemies" || enemies->isDestroyed()) continue;
			if (bullet->getHitbox().getGlobalBounds().intersects(enemies->getHitbox().getGlobalBounds()))
			{
				auto stat = enemies->getComponent<Stat>();
				if (stat)
				{
					stat->takeDamage(damage);
					if (stat->getHealth() <= 0.0f)
						enemies->markForDestroy();
				}
				bullet->markForDestroy();
				break;
			}
		}
	}
}