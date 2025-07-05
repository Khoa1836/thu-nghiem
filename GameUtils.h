#pragma once
#include <memory>
#include <vector>
#include "GameObject.h"

std::shared_ptr<GameObject> findPlayer(const std::vector<std::shared_ptr<GameObject>>& gameObjects);

std::vector<std::shared_ptr<GameObject>> findEnemies(const std::vector<std::shared_ptr<GameObject>>& gameObjects);



