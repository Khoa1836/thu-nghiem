#include "PlayerCollectGemComponent.h"
#include "GameObject.h"
#include "PlayerStat.h"

void PlayerCollectGemComponent::update(float deltaTime) {
    auto playerStat = owner->getComponent<PlayerStat>();
    if (!playerStat) return;

    for (auto& obj : *gameObjects) {
        if (obj->getTag() != "gem" || obj->isDestroyed()) continue;
        if (obj->getHitbox().getGlobalBounds().intersects(owner->getHitbox().getGlobalBounds())) {
            playerStat->addExp(20.f); // hoặc giá trị exp mong muốn
            obj->markForDestroy();
            // Có thể thêm hiệu ứng hoặc log nếu muốn
        }
    }
}