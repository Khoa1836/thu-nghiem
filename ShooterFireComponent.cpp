#include "ShooterFireComponent.h"
#include "BulletOfEnemy.h"
#include <cmath>
#include <iostream>
#include "Stat.h"

ShooterFireComponent::ShooterFireComponent(
    std::shared_ptr<GameObject> owner,
    std::vector<std::shared_ptr<GameObject>>* gameObjects,
    std::vector<std::shared_ptr<GameObject>>* toAddObjects,
    float n_fireCooldown,
    sf::Vector2f n_bulletVelocity
) : Component(owner),
    gameObjects(gameObjects),
    toAddObjects(toAddObjects),
    fireCooldown(n_fireCooldown),
    n_bulletVelocity(n_bulletVelocity),
    timer(0.f)
{
}

void ShooterFireComponent::update(float deltaTime)
{
    timer += deltaTime;
    if (timer >= fireCooldown) {
        timer = 0.f;
        std::cout << "ShooterEnemy Fire!\n";

        auto pos = owner->getHitbox().getPosition();
        auto target = findPlayer();

        sf::Vector2f velocity = n_bulletVelocity;

        if (target)
        {
            auto targetPos = target->getHitbox().getPosition();
            sf::Vector2f dir = targetPos - pos;
            float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
            if (length != 0)
            {
                dir /= length;
                velocity = dir * 200.f; // speed of the bullet
            }
        }
        
        float bulletDamage = 10.f;
        auto stat = owner->getComponent<Stat>();
        if (stat) bulletDamage = stat->getDamage();

        auto bullet = std::make_shared<BulletOfEnemy>(velocity, pos, bulletDamage);
        bullet->setTag("enemy_bullet");
        toAddObjects->push_back(bullet);
    }
}

std::shared_ptr<GameObject> ShooterFireComponent::findPlayer()
{
    for (auto& obj : *gameObjects)
    {
        if (obj->getTag() == "player")
            return obj;
    }
    return nullptr;
}