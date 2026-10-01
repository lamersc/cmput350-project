#include "Player.h"

#include <SFML/Window/Keyboard.hpp>

#include "Bullet.h"

namespace
{
constexpr int playerWidth = 40;
constexpr int playerHeight = 40;
constexpr float heldSpeed = 6.0f;
constexpr float bulletSpeed = 14.0f;
}  // namespace

Player::Player(CMPUT350::Point2D loc)
    : mLocation(loc),
      mAlive(true)
{
    UpdateBounds();
}

void Player::Initialize(CMPUT350::GameContext* context)
{
}

void Player::Update(CMPUT350::GameContext* context)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        Move(-heldSpeed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        Move(heldSpeed);
    }
}

void Player::LateUpdate(CMPUT350::GameContext* context)
{

    mWindowWidth = context->ScreenContext->GetWindowWidth();
}

bool Player::HandleKeyEvent(CMPUT350::GameContext* context, char key)
{
    if (key == ' ')
    {
        Fire(context);
        return true;
    }
    return false;
}

void Player::RenderBackground(CMPUT350::GameContext* context)
{
}

void Player::RenderForeground(CMPUT350::GameContext* context)
{
    float centerX = mLocation.x;
    float centerY = mLocation.y;
    CMPUT350::Point2D nose(centerX, centerY - 20);
    context->ScreenContext->DrawRect(
        CMPUT350::Rect(CMPUT350::Point2D(centerX - 4, centerY - 18), 8, 36),
        CMPUT350::Colors::white);
    context->ScreenContext->DrawLine(
        nose, CMPUT350::Point2D(centerX - 4, centerY - 10), 2, CMPUT350::Colors::white);
    context->ScreenContext->DrawLine(
        nose, CMPUT350::Point2D(centerX + 4, centerY - 10), 2, CMPUT350::Colors::white);
    context->ScreenContext->DrawLine(CMPUT350::Point2D(centerX - 4, centerY + 2),
                                     CMPUT350::Point2D(centerX - 20, centerY + 16),
                                     4,
                                     CMPUT350::Colors::red);
    context->ScreenContext->DrawLine(CMPUT350::Point2D(centerX + 4, centerY + 2),
                                     CMPUT350::Point2D(centerX + 20, centerY + 16),
                                     4,
                                     CMPUT350::Colors::red);
    context->ScreenContext->DrawRect(
        CMPUT350::Rect(CMPUT350::Point2D(centerX - 8, centerY + 14), 16, 4),
        CMPUT350::Colors::gray);
    context->ScreenContext->DrawCircle(
        CMPUT350::Point2D(centerX, centerY - 6), 3, CMPUT350::Colors::cyan);
}

void Player::CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj)
{
    std::shared_ptr<Bullet> bullet = std::dynamic_pointer_cast<Bullet>(obj);
    if (bullet == nullptr
        || bullet->IsPlayerBullet())
    {
        return;
    }
    Kill();

}

void Player::Kill()
{
    mAlive = false;
}

bool Player::IsAlive() const
{
    return mAlive;
}

const CMPUT350::Rect& Player::GetBounds()
{
    return mBounds;
}

void Player::UpdateBounds()
{
    mBounds = CMPUT350::Rect(
        CMPUT350::Point2D(mLocation.x - playerWidth / 2.0f, mLocation.y - playerHeight / 2.0f),
        playerWidth,
        playerHeight);
}

void Player::Move(float distance)
{
    mLocation.x += distance;
    float halfWidth = playerWidth / 2.0f;
    if (mLocation.x < halfWidth)
    {
        mLocation.x = halfWidth;
    }
    if (mLocation.x > mWindowWidth - halfWidth)
    {
        mLocation.x = mWindowWidth - halfWidth;
    }
    UpdateBounds();
}

void Player::Fire(CMPUT350::GameContext* context)
{
    for (int i = 0; i < 2; i++)
    {
        if (mBulletSlots[i].expired())
        {
            CMPUT350::Point2D bulletTop(mLocation.x, mLocation.y - playerHeight / 2.0f);
            CMPUT350::Point2D bulletDirection(0, -bulletSpeed);
            std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(bulletTop, bulletDirection, true);
            mBulletSlots[i] = bullet;
            context->mEngineView->AddGameObject(bullet);
            return;
        }
    }
}
