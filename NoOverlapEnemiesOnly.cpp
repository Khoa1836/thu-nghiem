#include "NoOverlapEnemiesOnly.h"
#include "GameObject.h"
#include "Enemies.h"

NoOverlapEnemiesOnly::NoOverlapEnemiesOnly(std::shared_ptr<GameObject> owner, std::vector<std::shared_ptr<GameObject>>* allObjects)
    : Component(owner), allObjects(allObjects)
{
}

void NoOverlapEnemiesOnly::update(float /*deltaTime*/)
{
    if (!owner || !allObjects) return;

    // Enemies
    if (!dynamic_cast<Enemies*>(owner.get()))
        return;

    auto& ownerBox = owner->getHitbox();
    for (auto& obj : *allObjects)
    {
        if (obj == owner) continue;

        // Enemies khc
        if (!dynamic_cast<Enemies*>(obj.get()))
            continue;

        auto& otherBox = obj->getHitbox();
        if (ownerBox.getGlobalBounds().intersects(otherBox.getGlobalBounds()))
        {
            sf::FloatRect ownerRect = ownerBox.getGlobalBounds();
            sf::FloatRect otherRect = otherBox.getGlobalBounds();

            float dx = (ownerRect.left + ownerRect.width / 2) - (otherRect.left + otherRect.width / 2);
            float dy = (ownerRect.top + ownerRect.height / 2) - (otherRect.top + otherRect.height / 2);

            if (std::abs(dx) > std::abs(dy))
            {
                // x
                if (dx > 0)
                    owner->move({ otherRect.left + otherRect.width - ownerRect.left, 0.f });
                else
                    owner->move({ otherRect.left - (ownerRect.left + ownerRect.width), 0.f });
            }
            else
            {
                // y
                if (dy > 0)
                    owner->move({ 0.f, otherRect.top + otherRect.height - ownerRect.top });
                else
                    owner->move({ 0.f, otherRect.top - (ownerRect.top + ownerRect.height) });
            }
        }
    }
}