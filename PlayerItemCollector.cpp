#include "PlayerItemCollector.h"
#include "GameObject.h"
#include "HealItem.h"
#include "ShieldItem.h"
#include "Stat.h"
#include "Player.h"
#include <iostream>

PlayerItemCollector::PlayerItemCollector(std::shared_ptr<GameObject> owner, std::vector<std::shared_ptr<GameObject>>* gameObjects)
    : Component(owner), gameObjects(gameObjects) {}

void PlayerItemCollector::update(float deltaTime)
{
    auto stat = owner->getComponent<Stat>();
    for (auto& obj : *gameObjects)
    {
        // HealItem: hồi 30% máu tối đa
        if (obj->getTag() == "heal" && owner->getHitbox().getGlobalBounds().intersects(obj->getHitbox().getGlobalBounds()))
        {
            auto heal = std::dynamic_pointer_cast<HealItem>(obj);
            if (heal && stat) {
                float maxHealth = stat->getMaxHealth();
                float healAmount = maxHealth * 0.3f;
                float newHealth = stat->getHealth() + healAmount;
                if (newHealth > maxHealth) healAmount = maxHealth - stat->getHealth();
                if (healAmount > 0) stat->takeDamage(-healAmount);
                obj->markForDestroy();
            }
        }
        // ShieldItem: khiên bảo vệ 5s
        if (obj->getTag() == "shield" && owner->getHitbox().getGlobalBounds().intersects(obj->getHitbox().getGlobalBounds()))
        {
            auto shield = std::dynamic_pointer_cast<ShieldItem>(obj);
            if (shield) {
                shieldActive = true;
                shieldTimer = 0.f;
                shieldDuration = 5.f; // hoặc shield->getShieldDuration();
                obj->markForDestroy();
            }
        }
    }
    // Xử lý thời gian khiên bảo vệ
    if (shieldActive) {
        shieldTimer += deltaTime;
        if (shieldTimer >= shieldDuration) {
            shieldActive = false;
        }
    }
}