#include "FireComponent.h"
#include "Bullet.h"
#include "Config.h"
#include "Stat.h"
#include "GameObject.h"

FireComponent::FireComponent (std::shared_ptr<GameObject> owner,
    std::vector<std::shared_ptr<GameObject>>* n_gameObjects,
    std::vector<std::shared_ptr<GameObject>>* n_toAddObjects,
    float n_fireCooldown)
    : Component(owner),
    gameObjects(n_gameObjects),
    toAddObjects(n_toAddObjects),
    fireCooldown(n_fireCooldown)
{
}

void FireComponent::update(float deltaTime)
{
    timer += deltaTime;
    if ( timer >= fireCooldown) {
        timer = 0.f;

        auto pos = owner->getHitbox().getPosition();
        auto target = findClosestEnemy();

        // Only fire if there is a valid enemy target
        if (!target)
            return;

        auto targetPos = target->getHitbox().getPosition();
        sf::Vector2f dir = targetPos - pos;
        float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        sf::Vector2f velocity(0.f, 0.f);
        if (length != 0)
        {
            //chuan hoa cho viec ban enemies xa va gan voi cung van toc
            dir /= length;
            velocity = dir * BULLET_VELOCITY;
        }

        float bulletDamage = 10.f;
        auto stat = owner->getComponent<Stat>();
        if (stat) bulletDamage = stat->getDamage();
        toAddObjects->push_back(std::make_shared<Bullet>(velocity, pos, bulletDamage));
    }
}

std::shared_ptr<GameObject> FireComponent::findClosestEnemy()
{
    std::shared_ptr<GameObject> closest = nullptr;
    float minDis = std::numeric_limits<float>::max();

    auto playerPos = owner->getHitbox().getPosition();

    for (auto& obj : *gameObjects)
    {
        // kiểm tra xem đã đi tới đúng đối tượng đang sở hữu FireComponent
        // tránh trường hợp nhận chính nó dẫn đến dis = 0;
        if (obj.get() == owner.get()) continue;

        if (obj->getTag() != "default_enemies" && obj->getTag() != "shooter_enemies") continue;
        auto enemiesPos = obj->getHitbox().getPosition();
        float dx = enemiesPos.x - playerPos.x;
        float dy = enemiesPos.y - playerPos.y;
        
        float dis = dx * dx + dy * dy;
        if (dis < minDis)
        {
            minDis = dis;
            closest = obj;
        }
    }
    return closest;
}


