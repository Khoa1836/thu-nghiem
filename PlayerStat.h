#pragma once
#include "Component.h"
#include <iostream>

class PlayerStat : public Component {
    float exp = 0.f;
    int level = 1;
    float expToNextLevel = 100.f;
public:
    PlayerStat(std::shared_ptr<GameObject> owner) : Component(owner) {}

    void addExp(float amount) {
        exp += amount;
        while (exp >= expToNextLevel) {
            exp -= expToNextLevel;
            level++;
			std::cout << "Level up! New level: " << level << std::endl;
            expToNextLevel *= 1.2f; // tăng exp cần cho level tiếp theo
        }
    }

    float getExp() const { return exp; }
    int getLevel() const { return level; }
    float getExpToNextLevel() const { return expToNextLevel; }

    // Override các hàm ảo thuần túy
    void update(float) override {} // Không cần xử lý gì
    void render(sf::RenderWindow&) override {} // Không cần xử lý gì
};
