    #include "GameUtils.h"

std::shared_ptr<GameObject> findPlayer(const std::vector<std::shared_ptr<GameObject>>& gameObjects) {
    for (const auto& obj : gameObjects) {
        if (obj->getTag() == "player") return obj;
    }
    return nullptr;
}

std::vector<std::shared_ptr<GameObject>> findEnemies(const std::vector<std::shared_ptr<GameObject>>& gameObjects) {
    std::vector<std::shared_ptr<GameObject>> result;
    for (const auto& obj : gameObjects) {
        if (obj->getTag() == "default_enemies" || obj->getTag() == "shooter_enemies")
            result.push_back(obj);
    }
    return result;
}
