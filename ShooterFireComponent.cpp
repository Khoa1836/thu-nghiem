#include "ShooterFireComponent.h"
#include "GameObject.h"
#include "Bullet.h"
#include "Config.h"
#include "Stat.h"
#include "GameUtils.h" // Thêm dòng này

ShooterFireComponent::ShooterFireComponent(
    std::shared_ptr<GameObject> owner,
    std::vector<std::shared_ptr<GameObject>>* gameObjects,
    std::vector<std::shared_ptr<GameObject>>* toAddObjects,
    float n_fireCooldown
)
    : FireComponent(owner, gameObjects, toAddObjects, n_fireCooldown)
{
}

void ShooterFireComponent::update(float deltaTime)
{

    timer += deltaTime;
    if (timer >= fireCooldown) {
        timer = 0.f;

        // Tìm player bằng GameUtils
        std::shared_ptr<GameObject> player = findPlayer(*gameObjects);
        if (!player) return;

        auto pos = owner->getHitbox().getPosition();
        auto targetPos = player->getHitbox().getPosition();
        sf::Vector2f dir = targetPos - pos;
        float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        sf::Vector2f velocity(0.f, 0.f);
        if (length != 0)
        {
            dir /= length;
            velocity = dir * BULLET_VELOCITY;
        }

        float bulletDamage = 10.f;
        auto stat = owner->getComponent<Stat>();
        if (stat) bulletDamage = stat->getDamage();
        auto bullet = std::make_shared<Bullet>(velocity, pos, bulletDamage);
        bullet->setTag("enemy_bullet");
        toAddObjects->push_back(bullet);

        std::cout << "ShooterEnemy fired a bullet!\n";
    }
}