#include "ShootComponent.h"
#include "GameObject.h"

void ShootComponent::update(float deltaTime)
{
    timeSinceLastShot += deltaTime;
    // Logic để trigger shoot, ví dụ: tự động bắn hoặc bắn khi nhấn phím
    // Ở đây ví dụ enemy tự động bắn mỗi khi cooldown xong
    if (timeSinceLastShot >= shootCooldown) {
        shoot();
        timeSinceLastShot = 0.0f;
    }
}

void ShootComponent::shoot()
{
    if (!owner) return;
    sf::Vector2f pos = owner->getHitbox().getPosition();
    // Example: shoot downward, or toward player if you have the direction
    sf::Vector2f dir(0, 200); // 200 px/s downward
    if (spawnBullet) spawnBullet(pos, dir);
    // Tạo bullet mới, add vào scene hoặc gameObjects
    // Ví dụ: std::make_shared<Bullet>(owner->getPosition(), direction);
}
