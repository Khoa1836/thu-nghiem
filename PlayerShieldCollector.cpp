#include "PlayerShieldCollector.h"
#include "GameObject.h"
#include "ShieldItem.h"

PlayerShieldCollector::PlayerShieldCollector(std::shared_ptr<GameObject> owner, std::vector<std::shared_ptr<GameObject>>* gameObjects)
    : Component(owner), gameObjects(gameObjects) {}

void PlayerShieldCollector::update(float deltaTime)
{
    for (auto& obj : *gameObjects)
    {
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
    if (shieldActive) {
        shieldTimer += deltaTime;
        if (shieldTimer >= shieldDuration) {
            shieldActive = false;
        }
    }
}
