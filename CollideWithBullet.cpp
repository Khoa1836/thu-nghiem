#include "CollideWithBullet.h"
#include "GameObject.h"
#include "Stat.h"
#include "Bullet.h"
#include "HealItem.h"
#include "ShieldItem.h"
#include <cstdlib> // rand

CollideWithBullet::CollideWithBullet(std::shared_ptr<GameObject> owner,
	std::vector<std::shared_ptr<GameObject>>* n_gameObjects,
	float n_damage,
	std::vector<std::shared_ptr<GameObject>>* n_toAddObjects)
	: Component(owner), gameObjects(n_gameObjects), damage(n_damage), toAddObjects(n_toAddObjects)
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
					{
						// 30% xác suất rớt buff
						float dropChance = 0.3f;
						if (static_cast<float>(rand()) / RAND_MAX < dropChance)
						{
							if (rand() % 2 == 0)
								toAddObjects->push_back(std::make_shared<HealItem>(enemies->getHitbox().getPosition()));
							else
								toAddObjects->push_back(std::make_shared<ShieldItem>(enemies->getHitbox().getPosition()));
						}
						enemies->markForDestroy();
					}
				}
				bullet->markForDestroy();
				break;
			}
		}
	}
}