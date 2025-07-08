#include "PlayerHealCollector.h"
#include "GameObject.h"
#include "HealItem.h"
#include "Stat.h"

PlayerHealCollector::PlayerHealCollector(std::shared_ptr<GameObject> owner, std::vector<std::shared_ptr<GameObject>>* gameObjects)
    : Component(owner), gameObjects(gameObjects) {}

void PlayerHealCollector::update(float deltaTime)
{
    auto stat = owner->getComponent<Stat>();
    for (auto& obj : *gameObjects)
    {
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
    }
}
