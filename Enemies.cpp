#include "Enemies.h"
#include "Stat.h" // Ensure you have this include if you use Stat

Enemies::Enemies()
    : GameObject()
{
    // Set up hitbox default size and color (can be overridden in subclasses)
    hitbox.setSize(sf::Vector2f(40.f, 40.f));
    hitbox.setFillColor(sf::Color::Red);

    // Set up health bar
    healthBar.setSize(sf::Vector2f(40.f, 5.f));
    healthBar.setFillColor(sf::Color::Green);
    healthBar.setPosition(hitbox.getPosition().x, hitbox.getPosition().y - 8.f);
}

void Enemies::render(sf::RenderWindow& window) {
    // Draw main body
    window.draw(hitbox);

    // Update health bar width and position before drawing
    float health = maxHealth;
    float currentHealth = maxHealth;
    auto stat = getComponent<Stat>();
    if (stat) {
        currentHealth = static_cast<float>(stat->getHealth());
        health = static_cast<float>(stat->getMaxHealth());
        maxHealth = health; // update maxHealth if Stat changes
    }
    float percent;
    if (health > 0.f) {
        percent = currentHealth / health;
    }
    else {
        percent = 0.f;
    }
    healthBar.setSize(sf::Vector2f(hitbox.getSize().x * percent, 5.f));
    healthBar.setPosition(hitbox.getPosition().x, hitbox.getPosition().y - 8.f);

    // Draw health bar
    window.draw(healthBar);
}

void Enemies::update(float deltaTime) {
    updateComponents(deltaTime);
}

void Enemies::onSpawn() {
    // Reset trạng thái của enemy khi spawn
    auto stat = getComponent<Stat>();
    if (stat) {
        stat->takeDamage(-stat->getMaxHealth()); // Hồi đầy máu
    }
    setTag("default_enemies"); // Đặt lại tag nếu cần
}

void Enemies::onDestroy() {
    // Xử lý logic khi enemy bị phá hủy
    std::cout << "Enemy destroyed!" << std::endl;
}

