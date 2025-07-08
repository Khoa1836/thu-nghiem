#include "DamageOnContact.h"
#include "GameObject.h"
#include "Stat.h"
#include "PlayerShieldCollector.h"

DamageOnContact::DamageOnContact(std::shared_ptr<GameObject> owner, std::shared_ptr<GameObject> target, float damage, float cooldown)
    : Component(owner), target(target), damage(damage), cooldown(cooldown), timer(0.0f)
{
}

void DamageOnContact::update(float deltaTime)
{
    timer -= deltaTime;
    if (timer > 0.0f) return;

    auto targetPtr = target.lock();
    if (!owner || !targetPtr) return;

    if (owner->getHitbox().getGlobalBounds().intersects(targetPtr->getHitbox().getGlobalBounds())) {
        auto stat = targetPtr->getComponent<Stat>();
        if (stat) {
            auto collector = targetPtr->getComponent<PlayerShieldCollector>();
            if (collector && collector->isShieldActive()) {
                // Bỏ qua sát thương
            } else {
                stat->takeDamage(damage);
                timer = cooldown;
            }
        }
    }
}