#pragma once
#include "GameObject.h"

class ShieldItem : public GameObject {
    float shieldDuration;
public:
    ShieldItem(sf::Vector2f pos, float duration = 5.0f);
    float getShieldDuration() const;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
};

