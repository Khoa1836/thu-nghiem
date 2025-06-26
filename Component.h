#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Config.h"
#include <functional>

class GameObject;

class Component
{
protected:
    std::shared_ptr<GameObject> owner; // Chủ sở hữu của component này
public:
    Component(std::shared_ptr<GameObject> owner) : owner(owner) {}
    virtual ~Component() = default;
    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) {}
};

// Component Pattern for game objects' behavior
// Thể hiện hành vi có thể gán cho game object bất kỳ
// Ví dụ khả năng di chuyển gán cho Player, Enemy, ...
// Hoặc khả năng đuổi theo người chơi gán cho các loại Enemy khác nhau
// Dễ dàng thêm bớt hoặc bật tắt, dễ debug