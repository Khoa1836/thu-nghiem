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
    bool wasMouseDown = false;
    std::shared_ptr<ICommand> command;

public:
    Button(const std::string& text, float x, float y, std::shared_ptr<ICommand> command);

    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
};
