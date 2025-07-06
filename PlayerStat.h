#pragma once
#include "Component.h"
#include <iostream>

class PlayerStat : public Component {
    int exp = 0;
    int level = 0;
    int expToNextLevel = 100;
public:
    PlayerStat(std::shared_ptr<GameObject> owner) : Component(owner) {}

    void addExp(int amount) {
        exp += amount;
        while (exp >= expToNextLevel) {
            exp -= expToNextLevel;
            level++;
            std::cout << "Level up! New level: " << level << std::endl;
            expToNextLevel = static_cast<int>(expToNextLevel * 1.2f);
        }
    }

    int getExp() const { return exp; }
    int getLevel() const { return level; }
    int getExpToNextLevel() const { return expToNextLevel; }

    void update(float) override {
        addExp(0); // luôn kiểm tra lên level mỗi frame
    }
    void render(sf::RenderWindow&) override {}
};
