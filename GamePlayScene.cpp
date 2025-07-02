// GamePlayScene.cpp
#include <random>
#include "GamePlayScene.h"
#include "SelectLevelScene.h"
#include "SwitchSceneCommand.h"
#include "Button.h"
#include "DamageOnContact.h"
#include "FollowTarget.h"
#include "NoOverlapEnemiesOnly.h"
#include "GameObject.h"
#include "ScenePause.h"
#include "GameManager.h"
#include "SceneLose.h"
#include <sstream>

// Hàm tiện ích để tìm player theo tag
std::shared_ptr<GameObject> GamePlayScene::findPlayer() {
    for (auto& obj : gameObjects) {
        if (obj->getTag() == "player") {
            return obj;
        }
    }
    return nullptr;
}

//check player is alive or not, player died if health <= 0;
bool GamePlayScene::alivePlayer()
{
    for (auto& obj : gameObjects)
    {
        if (obj->getTag() == "player")
        {
            auto stat = obj->getComponent<Stat>();
            if (stat && stat->getHealth() > 0) {
                return true;
            }
        }
    }
    return false;
}

// Helper function to spawn and randomize enemy position
void GamePlayScene::spawnRandomEnemy() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distX(0.f, 1230.f); // 1280 
    std::uniform_real_distribution<float> distY(0.f, 670.f);  // 720 


    auto player = findPlayer(); // Sử dụng hàm tiện ích để lấy player
    auto newEnemy = GameObjectFactory::createEnemy(player, &gameObjects);
    auto player = gameObjects[1];
    auto newEnemy = GameObjectFactory::createEnemy(player, &gameObjects, &toAddObjects);
    newEnemy->getHitbox().setPosition(distX(gen), distY(gen));
    gameObjects.push_back(newEnemy);
}

void GamePlayScene::spawnRandomShooterEnemy(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distX(0.f, 1230.f);
    std::uniform_real_distribution<float> distY(0.f, 670.f);

    auto player = gameObjects[1];
    auto newShooter = GameObjectFactory::createShooterEnemy(player, &gameObjects, &toAddObjects);
    newShooter->getHitbox().setPosition(distX(gen), distY(gen));
    gameObjects.push_back(newShooter);
}

GamePlayScene::GamePlayScene() {
    // clock
    clockInGame = std::make_shared<Clock>();

    gameObjects.push_back(std::make_shared<Button>(
        "Back", 100, 600, sf::Vector2f(50.f, 50.f),
        std::make_shared<SwitchSceneCommand>([]() {
            return std::make_shared<SelectLevelScene>();
        })
    ));

    gameObjects.push_back(std::make_shared<Button>(
        "Pause", 100, 100, sf::Vector2f(50.f, 50.f),
        std::make_shared<SwitchSceneCommand>([this]() {
            // Truyền shared_from_this() vào ScenePause
            return std::make_shared<ScenePause>(shared_from_this());
        })
    ));

    auto player = GameObjectFactory::createPlayer(&gameObjects, &toAddObjects);
    player->setTag("player"); // Đảm bảo player có tag là "player"
    gameObjects.push_back(player);

    spawnRandomEnemy(); // Use helper for initial enemy
}

void GamePlayScene::update(float deltaTime) {
    // Update all objects
    for (auto& obj : gameObjects) obj->update(deltaTime);

	// delete destroyed objects
    gameObjects.erase(
        std::remove_if(gameObjects.begin(), gameObjects.end(),
            [](const std::shared_ptr<GameObject>& obj) {
                return obj->isDestroyed();
            }),
        gameObjects.end()
    );

    //add bullet to game
    for (auto& obj : toAddObjects) {
        if (obj->getTag().empty()) // chỉ set tag nếu chưa có
            obj->setTag("bullet");
        gameObjects.push_back(obj);
    }
    toAddObjects.clear();

    // Nếu player chết thì chuyển sang SceneLose
    if (!alivePlayer()) {
        GameManager::getInstance().setScene(std::make_shared<SceneLose>(shared_from_this()));
        return;
    }

    //update enemy
    spawnTimer += deltaTime;
    if (spawnTimer >= 3.0f) {
        spawnTimer = 0.0f;
        // Spawn cả enemy thường và shooter enemy mỗi lần
        spawnRandomEnemy();
        spawnRandomShooterEnemy();
    }

    if (clockInGame && !clockInGame->isPaused()) clockInGame->update(deltaTime);
}


// clock and time
float GamePlayScene::getElapsedTime() const {
    if (clockInGame)
    {
        return clockInGame->getElapsedSeconds();
    }
    return 0.f;
}

void GamePlayScene::pauseClock() {
    if (clockInGame) clockInGame->pause();
}

void GamePlayScene::resumeClock() {
    if (clockInGame) clockInGame->resume();
}

void GamePlayScene::render(sf::RenderWindow& window) {
    for (auto& obj : gameObjects) {
        obj->render(window);
    }

    // Hiển thị thời gian chơi ở góc trên bên trái với định dạng MM:SS
    static sf::Font font;
    static bool fontLoaded = false;
    if (!fontLoaded) {
        fontLoaded = font.loadFromFile("arial.ttf"); // Đảm bảo file font tồn tại
    }
    if (fontLoaded) {
        int elapsed = static_cast<int>(getElapsedTime());
        int minutes = elapsed / 60;
        int seconds = elapsed % 60;
        std::ostringstream oss;
        oss << "Time: ";
        if (minutes < 10) oss << '0';
        oss << minutes << ":";
        if (seconds < 10) oss << '0';
        oss << seconds;
        sf::Text text(oss.str(), font, 24);
        text.setFillColor(sf::Color::Green);
        text.setPosition(10, 10); // Góc trên bên trái
        window.draw(text);
    }
}