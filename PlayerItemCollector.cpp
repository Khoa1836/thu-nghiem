#include "PlayerItemCollector.h"
#include "GameObject.h"
#include "HealItem.h"
#include "ShieldItem.h"
#include "Stat.h"
#include "Player.h"
#include <iostream>

void PlayerItemCollector::update(float deltaTime)
{
    for (auto& obj : *gameObjects)
    {
        if (obj->getTag() == "heal" && owner->getHitbox().getGlobalBounds().intersects(obj->getHitbox().getGlobalBounds()))
        {
            auto heal = std::dynamic_pointer_cast<HealItem>(obj);
            if (heal) {
                auto stat = owner->getComponent<Stat>();
                if (stat) stat->takeDamage(-heal->getHealAmount()); // H?i máu
                obj->markForDestroy();
            }
        }
        if (obj->getTag() == "shield" && owner->getHitbox().getGlobalBounds().intersects(obj->getHitbox().getGlobalBounds()))
        {
            auto shield = std::dynamic_pointer_cast<ShieldItem>(obj);
            if (shield) {
                shieldActive = true;
                shieldTimer = 0.f;
                shieldDuration = shield->getShieldDuration();
                obj->markForDestroy();
            }
        }
    }
    // X? lý th?i gian khiên b?o v?
    if (shieldActive) {
        shieldTimer += deltaTime;
        if (shieldTimer >= shieldDuration) {
            shieldActive = false;
        }
    }
}