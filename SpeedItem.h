#pragma once
#include "GameObject.h"

class SpeedItem : public GameObject {
    float speedDuration;
    float speedMultiplier;
public:
    SpeedItem(sf::Vector2f pos, float duration = 5.0f, float multiplier = 2.0f);
    float getSpeedDuration() const;
    float getSpeedMultiplier() const;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
};

