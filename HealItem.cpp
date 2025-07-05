#include "HealItem.h"


HealItem::HealItem(sf::Vector2f pos, int heal)
    : healAmount(heal)
{
    hitbox.setSize(sf::Vector2f(30, 30));
    hitbox.setFillColor(sf::Color::Green);
    hitbox.setPosition(pos);
    setTag("heal");
}

int HealItem::getHealAmount() const 
{
    return healAmount; 
}

void HealItem::update(float deltaTime) { /* Có thể thêm logic tự hủy sau X giây nếu muốn */ }

void HealItem::render(sf::RenderWindow& window) { window.draw(hitbox); }
