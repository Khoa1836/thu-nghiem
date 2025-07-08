#include "PlayerBuffBar.h"
#include "PlayerShieldCollector.h"
#include "PlayerSpeedCollector.h"
#include "GameObject.h"

PlayerBuffBar::PlayerBuffBar(std::shared_ptr<GameObject> owner, const sf::Font& font)
    : owner(owner), font(font) {}

void PlayerBuffBar::render(sf::RenderWindow& window)
{
    float barWidth = 100.f;
    float barHeight = 10.f;
    float spacing = 5.f;
    int barCount = 0;
    float baseX = window.getSize().x - barWidth - 20.f;
    float baseY = 20.f;

    // Shield bar
    auto shield = owner->getComponent<PlayerShieldCollector>();
    if (shield && shield->isShieldActive() && shield->getShieldDuration() > 0.f) {
        float percent = 1.f - (shield->getShieldTimer() / shield->getShieldDuration());
        if (percent < 0.f) percent = 0.f;
        sf::RectangleShape shieldBar(sf::Vector2f(barWidth * percent, barHeight));
        shieldBar.setFillColor(sf::Color::Cyan);
        shieldBar.setPosition(baseX, baseY + barCount * (barHeight + spacing));
        window.draw(shieldBar);

        sf::RectangleShape border(sf::Vector2f(barWidth, barHeight));
        border.setFillColor(sf::Color::Transparent);
        border.setOutlineColor(sf::Color::White);
        border.setOutlineThickness(2.f);
        border.setPosition(baseX, baseY + barCount * (barHeight + spacing));
        window.draw(border);

        // Draw countdown text
        float remain = shield->getShieldDuration() - shield->getShieldTimer();
        if (remain < 0.f) remain = 0.f;
        int remainInt = static_cast<int>(std::ceil(remain));
        sf::Text countdown(std::to_string(remainInt), font, 16);
        countdown.setFillColor(sf::Color::Blue);
        countdown.setPosition(baseX + barWidth + 8.f, baseY + barCount * (barHeight + spacing) - 2.f);
        window.draw(countdown);

        barCount++;
    }

    // Speed bar
    auto speed = owner->getComponent<PlayerSpeedCollector>();
    if (speed && speed->isSpeedActive() && speed->getSpeedDuration() > 0.f) {
        float percent = 1.f - (speed->getSpeedTimer() / speed->getSpeedDuration());
        if (percent < 0.f) percent = 0.f;
        sf::RectangleShape speedBar(sf::Vector2f(barWidth * percent, barHeight));
        speedBar.setFillColor(sf::Color::Yellow);
        speedBar.setPosition(baseX, baseY + barCount * (barHeight + spacing));
        window.draw(speedBar);

        sf::RectangleShape border(sf::Vector2f(barWidth, barHeight));
        border.setFillColor(sf::Color::Transparent);
        border.setOutlineColor(sf::Color::White);
        border.setOutlineThickness(2.f);
        border.setPosition(baseX, baseY + barCount * (barHeight + spacing));
        window.draw(border);

        // Draw countdown text
        float remain = speed->getSpeedDuration() - speed->getSpeedTimer();
        if (remain < 0.f) remain = 0.f;
        int remainInt = static_cast<int>(std::ceil(remain));
        sf::Text countdown(std::to_string(remainInt), font, 16);
        countdown.setFillColor(sf::Color::Yellow);
        countdown.setPosition(baseX + barWidth + 8.f, baseY + barCount * (barHeight + spacing) - 2.f);
        window.draw(countdown);

        barCount++;
    }
}