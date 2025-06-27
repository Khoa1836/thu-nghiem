// Button.h
#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include "GameObject.h"
#include "ICommand.h"
#include "Config.h"
#include "GameManager.h"

class Button : public GameObject {
private:
    bool isHovered = false;

    std::shared_ptr<ICommand> command;

    sf::Text text;
    static sf::Font font;
public:
    Button(const std::string& n_text, float x, float y,sf::Vector2f size, std::shared_ptr<ICommand> command);

    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
};

