#include "ShieldItem.h"

ShieldItem::ShieldItem(sf::Vector2f pos, float duration)
    : shieldDuration(duration)
{
    hitbox.setSize(sf::Vector2f(30, 30));
    hitbox.setFillColor(sf::Color::Cyan);
    hitbox.setPosition(pos);
    setTag("shield");
}

float ShieldItem::getShieldDuration() const 
{
    return shieldDuration; 
}

void ShieldItem::update(float deltaTime) {

}

void ShieldItem::render(sf::RenderWindow& window) {
    window.draw(hitbox);
}
