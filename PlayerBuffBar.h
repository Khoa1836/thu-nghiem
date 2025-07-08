#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class GameObject;

class PlayerBuffBar {
public:
    PlayerBuffBar(std::shared_ptr<GameObject> owner, const sf::Font& font);

    void render(sf::RenderWindow& window);

private:
    std::shared_ptr<GameObject> owner;
    const sf::Font& font;
};

