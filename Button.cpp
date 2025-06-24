// Button.cpp
#include "Button.h"

Button::Button(const std::string& text, float x, float y, std::shared_ptr<ICommand> command)
    : command(command) {
    hitbox.setSize(sf::Vector2f(200.f, 50.f));
    hitbox.setPosition(x, y);
    hitbox.setFillColor(sf::Color::Blue);
    hitbox.setOutlineThickness(2.f);
    hitbox.setOutlineColor(sf::Color::Black);
}

void Button::update(float deltaTime) {
    bool mouseNowDown = GameManager::getInstance().isMousePressed();
    sf::Vector2f mousePos = mousePosition;
    sf::Vector2f posF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    if (hitbox.getGlobalBounds().contains(posF)) {
        if (!isHovered) {
            hitbox.setFillColor(sf::Color::Green);
            isHovered = true;
        }
        if (mouseNowDown && !wasMouseDown && command)
            command->execute();
    }
    else {
        if (isHovered) {
            hitbox.setFillColor(sf::Color::Blue);
            isHovered = false;
        }
    }
    wasMouseDown = mouseNowDown;
}

void Button::render(sf::RenderWindow& window) {
    window.draw(hitbox);
}