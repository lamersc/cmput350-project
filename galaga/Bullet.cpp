#include "Bullet.h"

#include "Enemy.h"
#include "Player.h"

namespace
{

constexpr float bulletWidth = 4.0f;
}

Bullet::Bullet(CMPUT350::Point2D location, CMPUT350::Point2D heading, bool player)
    : mLocation(location),
      mPreviousLocation(location),
      mDirection(heading),
      mBounds(CMPUT350::Point2D(location.x - bulletWidth / 2, location.y - bulletWidth / 2),
              4,
              4),
      mPlayerBullet(player),
      mAlive(true)
{
}

bool Bullet::IsPlayerBullet()
{
    return mPlayerBullet;
}

void Bullet::Initialize(CMPUT350::GameContext* context)
{
}

void Bullet::Update(CMPUT350::GameContext* context)
{
    mPreviousLocation = mLocation;
    mLocation += mDirection;
    mBounds = CMPUT350::Rect(mPreviousLocation, mLocation);
    float bulletHalfWidth = bulletWidth / 2;
    mBounds.topLeft.x -= bulletHalfWidth;
    mBounds.topLeft.y -= bulletHalfWidth;
    mBounds.width += bulletWidth;
    mBounds.height += bulletWidth;
}

void Bullet::LateUpdate(CMPUT350::GameContext* context)
{
    if (mLocation.y < 0 && mPreviousLocation.y < 0)
    {
        Kill();
    }
}

bool Bullet::HandleKeyEvent(CMPUT350::GameContext* context, char key)
{
    return false;
}

void Bullet::RenderBackground(CMPUT350::GameContext* context)
{
}

void Bullet::RenderForeground(CMPUT350::GameContext* context)
{
    CMPUT350::RGBColor color = mPlayerBullet ? CMPUT350::Colors::white : CMPUT350::Colors::red;
    context->ScreenContext->DrawLine(mPreviousLocation, mLocation, bulletWidth, color);
}

void Bullet::CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj)
{
    // A fresh bullet starts inside its owner, so each side ignores its own bullets.
    if (mPlayerBullet && std::dynamic_pointer_cast<Player>(obj) != nullptr
        || !mPlayerBullet && std::dynamic_pointer_cast<Enemy>(obj) != nullptr)
    {
        return;
    }

    Kill();

}

void Bullet::Kill()
{
    mAlive = false;
}

bool Bullet::IsAlive() const
{
    return mAlive;
}

const CMPUT350::Rect& Bullet::GetBounds()
{
    return mBounds;
}
