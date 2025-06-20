#pragma once

#include <SFML/Graphics.hpp>
#include "Config.h"
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player();
	virtual ~Player();

	void update(float deltaTime) override;
};

