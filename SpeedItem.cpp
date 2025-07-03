#include "SpeedItem.h"

SpeedItem::SpeedItem(sf::Vector2f pos, float duration, float multiplier)
    : speedDuration(duration), speedMultiplier(multiplier)
{
    hitbox.setSize(sf::Vector2f(30, 30));
    hitbox.setFillColor(sf::Color::Yellow);
    hitbox.setPosition(pos);
    setTag("speed");
}

float SpeedItem::getSpeedDuration() const { return speedDuration; }
float SpeedItem::getSpeedMultiplier() const { return speedMultiplier; }

void SpeedItem::update(float deltaTime) { }
void SpeedItem::render(sf::RenderWindow& window) { window.draw(hitbox); }
