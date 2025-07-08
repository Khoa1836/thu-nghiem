// GamePlayScene.cpp
#include <random>
#include <vector>
#include <memory>
#include <iostream> 
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
#include <SFML/Graphics.hpp>
#include "GameUtils.h"
#include "PlayerStat.h"
#include "PlayerBuffBar.h"

sf::Font GamePlayScene::font;
bool GamePlayScene::fontLoaded = false;

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

// Helper function to spawn and randomize either default or shooter enemy
void GamePlayScene::spawnRandomEnemy(bool isShooter) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distX(0.f, 1230.f);
    std::uniform_real_distribution<float> distY(0.f, 670.f);

    std::shared_ptr<GameObject> newEnemy = nullptr;

    // Kiểm tra pool để tái sử dụng enemy
    for (auto& enemy : enemyPool) {
        if (enemy->isDestroyed()) {
            newEnemy = enemy;
            newEnemy->revive();
            newEnemy->onSpawn();
            break;
        }
    }

    // Nếu không có enemy nào trong pool, tạo mới
    if (!newEnemy) {
        auto player = findPlayer(gameObjects); // Không cần *
        if (isShooter) {
            newEnemy = GameObjectFactory::createShooterEnemy(player, &gameObjects, &toAddObjects);
        } else {
            newEnemy = GameObjectFactory::createEnemy(player, &gameObjects, &toAddObjects);
        }
        enemyPool.push_back(newEnemy);
    }

    // Đặt vị trí ngẫu nhiên cho enemy
    newEnemy->getHitbox().setPosition(distX(gen), distY(gen));
    gameObjects.push_back(newEnemy);
}

GamePlayScene::GamePlayScene() {
    if (!fontLoaded) {
        fontLoaded = font.loadFromFile("arial.ttf");
    }

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

    // Khởi tạo PlayerBuffBar
    playerBuffBar = std::make_unique<PlayerBuffBar>(player, font);

    spawnRandomEnemy(false); // Use helper for initial enemy
}

void GamePlayScene::update(float deltaTime) 
{
	// Xóa các đối tượng không hoạt động lâu,cải thiên hiệu hiệu suất
    if (enemyPool.size() > maxEnemies) {
        enemyPool.erase(
            std::remove_if(enemyPool.begin(), enemyPool.end(),
                [](const std::shared_ptr<GameObject>& obj) {
                    return obj->isDestroyed();
                }),
            enemyPool.end()
        );
    }

    // Update all objects
    for (auto& obj : gameObjects) obj->update(deltaTime);

    // delete destroyed objects
    // Add new objects, no bullet or enemy limit
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

    // update enemy: always spawn every 3 seconds, limit enemy count
    spawnTimer += deltaTime;

    int maxEnemies = 50; // Số lượng kẻ thù tối đa
    int currentEnemies = std::count_if(gameObjects.begin(), gameObjects.end(),
        [](const std::shared_ptr<GameObject>& obj) {
            return obj->getTag() == "default_enemies" || obj->getTag() == "shooter_enemies";
        });

    if (spawnTimer >= 3.0f) {
        spawnTimer = 0.0f;
        spawnRandomEnemy(false);  // spawn default enemy
        spawnRandomEnemy(true);   // spawn shooter enemy
    }

    if (clockInGame && !clockInGame->isPaused()) clockInGame->update(deltaTime);

    //giai phong bo nho
    gameObjects.erase(
        std::remove_if(gameObjects.begin(), gameObjects.end(),
            [](const std::shared_ptr<GameObject>& obj) {
                return obj->isDestroyed();
            }),
        gameObjects.end()
    );
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

    auto player = findPlayer(gameObjects);
    if (fontLoaded && player) {
        auto playerStat = player->getComponent<PlayerStat>();
        if (playerStat) {
            // Kích thước và vị trí thanh exp
            float barWidth = 400.f;
            float barHeight = 22.f;
            float windowWidth = window.getSize().x;
            float barX = (windowWidth - barWidth) / 2.f;
            float barY = 16.f;

            // Level box
            float levelBoxWidth = 60.f;
            float levelBoxHeight = barHeight + 8.f;
            float levelBoxX = barX - levelBoxWidth - 10.f;
            float levelBoxY = barY - 4.f;

            // Vẽ khung level
            sf::RectangleShape levelBox(sf::Vector2f(levelBoxWidth, levelBoxHeight));
            levelBox.setFillColor(sf::Color(40, 40, 40));
            levelBox.setOutlineColor(sf::Color::White);
            levelBox.setOutlineThickness(2.f);
            levelBox.setPosition(levelBoxX, levelBoxY);
            window.draw(levelBox);

            // Vẽ số level
            std::ostringstream oss;
            oss << "Lv " << playerStat->getLevel();
            sf::Text levelText(oss.str(), font, 22);
            levelText.setFillColor(sf::Color::White);
            // Căn giữa trong khung
            sf::FloatRect textRect = levelText.getLocalBounds();
            levelText.setPosition(
                levelBoxX + (levelBoxWidth - textRect.width) / 2.f,
                levelBoxY + (levelBoxHeight - textRect.height) / 2.f - 4.f
            );
            window.draw(levelText);

            // Hiển thị thanh exp
            int exp = playerStat->getExp();
            int expToNext = playerStat->getExpToNextLevel();
            float percent = static_cast<float>(exp) / expToNext;

            // Khung nền exp
            sf::RectangleShape expBarBg(sf::Vector2f(barWidth, barHeight));
            expBarBg.setFillColor(sf::Color(50, 50, 50));
            expBarBg.setPosition(barX, barY);

            // Thanh exp
            sf::RectangleShape expBar(sf::Vector2f(barWidth * percent, barHeight));
            expBar.setFillColor(sf::Color(255, 165, 0)); // Màu cam
            expBar.setPosition(barX, barY);

            window.draw(expBarBg);
            window.draw(expBar);

            // Text exp
            std::ostringstream expText;
            expText << static_cast<int>(exp) << " / " << static_cast<int>(expToNext);
            sf::Text expValue(expText.str(), font, 16);
            expValue.setFillColor(sf::Color::White);
            sf::FloatRect expRect = expValue.getLocalBounds();
            expValue.setPosition(
                barX + (barWidth - expRect.width) / 2.f,
                barY + (barHeight - expRect.height) / 2.f - 2.f
            );
            window.draw(expValue);
        }
    }

    // Vẽ buff bar
    if (playerBuffBar) playerBuffBar->render(window);
}