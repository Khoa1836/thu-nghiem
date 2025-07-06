#include "DefaultEnemy.h"
#include <SFML/Graphics.hpp>

DefaultEnemy::DefaultEnemy() : Enemies() 
{
    hitbox.setFillColor(sf::Color(128, 0, 0)); // Use a different color for default enemy
    hitbox.setSize(sf::Vector2f(40.f, 40.f));
}



