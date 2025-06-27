#include "FireComponent.h"
#include "Bullet.h"
#include "Config.h"
#include "Stat.h"
#include "GameObject.h"

FireComponent::FireComponent (std::shared_ptr<GameObject> owner,
    std::vector<std::shared_ptr<GameObject>>* n_gameObjects,
    std::vector<std::shared_ptr<GameObject>>* n_toAddObjects,
    float n_fireCooldown, sf::Vector2f n_bulletVelocity )
    : Component(owner),
    gameObjects(n_gameObjects),
    toAddObjects(n_toAddObjects),
    n_bulletVelocity(n_bulletVelocity),
    fireCooldown(n_fireCooldown)
{
}

void FireComponent::update(float deltaTime)
{
	timer += deltaTime;
	if ( timer >= fireCooldown) {
		timer = 0.f;
        std::cout << "Fire!\n";

		auto pos = owner->getHitbox().getPosition();
        auto target = findClosestEnemy();

        // Kiểm tra target và lấy component Stat nếu có
       /* float healthTarget = 0.f;
        //if (target) {
            //auto stat = target->getComponent<Stat>();
            //if (stat) {
                //healthTarget = stat->getHealth();
            //} 
        //}*/

        sf::Vector2f velocity = n_bulletVelocity;

        if (target)
        {
            auto targetPos = target->getHitbox().getPosition();
            sf::Vector2f dir = targetPos - pos;
            float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
            if (length != 0)
            {
                //chuan hoa cho viec ban enemies xa va gan voi cung van toc
                dir /= length;
                velocity = dir * BULLET_VELOCITY;
            }
        }
		toAddObjects->push_back(std::make_shared<Bullet>(velocity, pos));
	}
}

std::shared_ptr<GameObject> FireComponent::findClosestEnemy()
{
    std::shared_ptr<GameObject> closest = nullptr;
    float minDis = std::numeric_limits<float>::max();

    auto playerPos = owner->getHitbox().getPosition();

    for (auto& obj : *gameObjects)
    {
        // kiểm tra xem đã đi tới đúng đối tượng đang sở hữu FireComponent
        // tránh trường hợp nhận chính nó dẫn đến dis = 0;
        if (obj.get() == owner.get()) continue;

        if (obj->getTag() != "enemies") continue;
        auto enemiesPos = obj->getHitbox().getPosition();
        float dx = enemiesPos.x - playerPos.x;
        float dy = enemiesPos.y - playerPos.y;
        
        float dis = dx * dx + dy * dy;
        if (dis < minDis)
        {
            minDis = dis;
            closest = obj;
        }
    }
    return closest;
}


