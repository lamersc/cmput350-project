#include "Bullet.h"

#include "Enemy.h"
#include "Player.h"

namespace
{
constexpr float bulletWidth = 4.0f;
constexpr int explodeFrames = 6;
constexpr float explodeRadius = 8.0f;
}  // namespace

Bullet::Bullet(CMPUT350::Point2D location, CMPUT350::Point2D heading, bool player,
               std::weak_ptr<CMPUT350::GameObject> parent)
    : mLocation(location),
      mPreviousLocation(location),
      mHeading(heading),
      mCollisionPoint(0, 0),
      mPlayerBullet(player),
      mParent(parent),
      mAlive(true),
      mDestroyed(false),
      mExplodeTimer(0)
{
    mShapes.push_back(
        CMPUT350::Shape(CMPUT350::Line(CMPUT350::Point2D(0, 0), CMPUT350::Point2D(0, 0))));
    UpdateBounds();
}

bool Bullet::IsPlayerBullet()
{
    return mPlayerBullet;
}

bool Bullet::IsDestroyed() const
{
    return mDestroyed;
}

void Bullet::Update(CMPUT350::GameContext* context)
{
    if (mDestroyed)
    {
        if (++mExplodeTimer >= explodeFrames)
        {
            Kill();
        }
        return;
    }
    if (mParent.expired())
    {
        Kill();
        return;
    }
    mPreviousLocation = mLocation;
    mLocation += mHeading;
    if (mLocation.y < -30 || mLocation.y > context->ScreenContext->GetWindowHeight() + 30)
    {
        Kill();
        return;
    }
    mShapes[0] = CMPUT350::Shape(
        CMPUT350::Line(mPreviousLocation - mLocation, CMPUT350::Point2D(0, 0)));
    UpdateBounds();
}

void Bullet::LateUpdate(CMPUT350::GameContext* context)
{
}

void Bullet::RenderForeground(CMPUT350::GameContext* context)
{
    if (mDestroyed)
    {
        context->ScreenContext->DrawCircle(
            mCollisionPoint, explodeRadius,
            mPlayerBullet ? CMPUT350::Colors::white : CMPUT350::Colors::red);
        return;
    }
    context->ScreenContext->DrawLine(mPreviousLocation - mLocation, CMPUT350::Point2D(0, 0),
                                      bulletWidth,
                                      mPlayerBullet ? CMPUT350::Colors::white
                                                    : CMPUT350::Colors::red);
}

bool Bullet::IsAlive() const
{
    return mAlive;
}

void Bullet::Kill()
{
    mAlive = false;
}

const std::vector<CMPUT350::Shape>& Bullet::GetShapes()
{
    return mShapes;
}

void Bullet::CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj)
{
    CollisionEnter(obj, CMPUT350::Point2D(0, 0));
}

void Bullet::CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj,
                             const CMPUT350::Point2D& collisionPoint)
{
    if (mDestroyed)
    {
        if (collisionPoint.y > mCollisionPoint.y)
        {
            mCollisionPoint = collisionPoint;
        }
        return;
    }
    if (std::dynamic_pointer_cast<Bullet>(obj) != nullptr)
    {
        return;
    }
    if (mPlayerBullet && std::dynamic_pointer_cast<Player>(obj) != nullptr)
    {
        return;
    }
    if (!mPlayerBullet && std::dynamic_pointer_cast<Enemy>(obj) != nullptr)
    {
        return;
    }
    mCollisionPoint = collisionPoint;
    mDestroyed = true;
}

const CMPUT350::Rect& Bullet::GetBounds()
{
    return mBounds;
}

CMPUT350::Point2D Bullet::GetLocation() const
{
    return mLocation;
}

float Bullet::GetRotation() const
{
    return 0.0f;
}

void Bullet::UpdateBounds()
{
    mBounds = CMPUT350::Rect(mPreviousLocation, mLocation);
    mBounds.topLeft -= CMPUT350::Point2D(bulletWidth / 2.0f, bulletWidth / 2.0f);
    mBounds.width += bulletWidth;
    mBounds.height += bulletWidth;
}
