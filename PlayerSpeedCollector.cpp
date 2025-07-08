#include "PlayerSpeedCollector.h"
#include "GameObject.h"
#include "SpeedItem.h"

PlayerSpeedCollector::PlayerSpeedCollector(std::shared_ptr<GameObject> owner, std::vector<std::shared_ptr<GameObject>>* gameObjects)
    : Component(owner), gameObjects(gameObjects) {}

void PlayerSpeedCollector::update(float deltaTime)
{
    for (auto& obj : *gameObjects)
    {
        if (obj->getTag() == "speed" && owner->getHitbox().getGlobalBounds().intersects(obj->getHitbox().getGlobalBounds()))
        {
            auto speed = std::dynamic_pointer_cast<SpeedItem>(obj);
            if (speed) {
                speedActive = true;
                speedTimer = 0.f;
                speedDuration = speed->getSpeedDuration();
                speedMultiplier = speed->getSpeedMultiplier();
                obj->markForDestroy();
            }
        }
    }
    if (speedActive) {
        speedTimer += deltaTime;
        if (speedTimer >= speedDuration) {
            speedActive = false;
            speedMultiplier = 3.f;
        }
    }
}
