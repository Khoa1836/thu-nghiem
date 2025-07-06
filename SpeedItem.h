#pragma once
#include "GameObject.h"

class SpeedItem : public GameObject {
    float speedDuration;
    float speedMultiplier;
public:
    SpeedItem(sf::Vector2f pos, float duration = 5.0f, float multiplier = 1.5f);
    float getSpeedDuration() const;
    float getSpeedMultiplier() const;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
};

