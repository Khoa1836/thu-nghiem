#include "CollideWithEnemyBullet.h"
#include "GameObject.h"
#include "Stat.h"
#include "BulletOfEnemy.h"
#include <memory>
#include "playeritemcollector.h"

CollideWithEnemyBullet::CollideWithEnemyBullet(
    std::shared_ptr<GameObject> owner,
    std::vector<std::shared_ptr<GameObject>>* n_gameObjects)
    : Component(owner), gameObjects(n_gameObjects)
{
}

void CollideWithEnemyBullet::update(float deltaTime)
{
    auto stat = owner->getComponent<Stat>();
    if (!stat) return;

    for (auto& bullet : *gameObjects)
    {
        if (bullet->getTag() != "enemy_bullet" || bullet->isDestroyed()) continue;
        if (bullet->getHitbox().getGlobalBounds().intersects(owner->getHitbox().getGlobalBounds()))
        {
            float damage = 10.f;
            auto bulletPtr = std::dynamic_pointer_cast<BulletOfEnemy>(bullet);
            if (bulletPtr) damage = bulletPtr->getDamage();

            auto collector = owner->getComponent<PlayerItemCollector>();
            if (collector && collector->isShieldActive())
            {
                // Bỏ qua sát thương
            }
            else
            {
                stat->takeDamage(damage);
            }

            bullet->markForDestroy();
            std::cout << "Player hit by enemy bullet! HP: " << stat->getHealth() << std::endl;
        }
    }
}