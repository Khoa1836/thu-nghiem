#pragma once
#include "GameObject.h"

class HealItem : public GameObject {
    int healAmount;
public:
    HealItem(sf::Vector2f pos, int heal = 30);
    int getHealAmount() const;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
};

