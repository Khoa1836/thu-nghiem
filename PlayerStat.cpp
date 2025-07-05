#include "PlayerStat.h"

void PlayerStat::addExp(float amount) 
{
    exp += amount;
    while (exp >= expToNextLevel) {
        exp -= expToNextLevel;
        level++;
        std::cout << "Level up! New level: " << level << std::endl;
        expToNextLevel *= 1.2f; // t?ng exp c?n cho level ti?p theo
    }
}