#include "PlayerItemCollector.h"
#include "GameObject.h"
#include "HealItem.h"
#include "ShieldItem.h"
#include "SpeedItem.h"
#include "Stat.h"
#include "Player.h"
#include <iostream>

PlayerItemCollector::PlayerItemCollector(std::shared_ptr<GameObject> owner, std::vector<std::shared_ptr<GameObject>>* gameObjects)
    : Component(owner), gameObjects(gameObjects), shieldActive(false), shieldTimer(0.f), shieldDuration(0.f), speedActive(false), speedTimer(0.f), speedDuration(0.f), speedMultiplier(1.f) {}

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
        // SpeedItem: tăng tốc 5s
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
    // Xử lý thời gian khiên bảo vệ
    if (shieldActive) {
        shieldTimer += deltaTime;
        if (shieldTimer >= shieldDuration) {
            shieldActive = false;
        }
    }
    // Xử lý thời gian buff speed
    if (speedActive) {
        speedTimer += deltaTime;
        if (speedTimer >= speedDuration) {
            speedActive = false;
            speedMultiplier = 1.f;
        }
    }
}

void PlayerItemCollector::render(sf::RenderWindow& window)
{
    // Lấy vị trí player
    sf::Vector2f basePos = owner->getHitbox().getPosition();
    float barWidth = 100.f;
    float barHeight = 10.f;
    float spacing = 5.f;
    int barCount = 0;

    // Shield bar
    if (shieldActive && shieldDuration > 0.f) {
        float percent = 1.f - (shieldTimer / shieldDuration);
        if (percent < 0.f) percent = 0.f;
        sf::RectangleShape shieldBar(sf::Vector2f(barWidth * percent, barHeight));
        shieldBar.setFillColor(sf::Color::Cyan);
        shieldBar.setPosition(basePos.x, basePos.y - 30.f - barCount * (barHeight + spacing));
        window.draw(shieldBar);

        // Viền
        sf::RectangleShape border(sf::Vector2f(barWidth, barHeight));
        border.setFillColor(sf::Color::Transparent);
        border.setOutlineColor(sf::Color::White);
        border.setOutlineThickness(1.f);
        border.setPosition(basePos.x, basePos.y - 30.f - barCount * (barHeight + spacing));
        window.draw(border);

        barCount++;
    }

    // Speed bar
    if (speedActive && speedDuration > 0.f) {
        float percent = 1.f - (speedTimer / speedDuration);
        if (percent < 0.f) percent = 0.f;
        sf::RectangleShape speedBar(sf::Vector2f(barWidth * percent, barHeight));
        speedBar.setFillColor(sf::Color::Yellow);
        speedBar.setPosition(basePos.x, basePos.y - 30.f - barCount * (barHeight + spacing));
        window.draw(speedBar);

        // Viền
        sf::RectangleShape border(sf::Vector2f(barWidth, barHeight));
        border.setFillColor(sf::Color::Transparent);
        border.setOutlineColor(sf::Color::White);
        border.setOutlineThickness(1.f);
        border.setPosition(basePos.x, basePos.y - 30.f - barCount * (barHeight + spacing));
        window.draw(border);

        barCount++;
    }
}