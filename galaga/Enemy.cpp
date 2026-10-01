#include "Enemy.h"

#include "Bullet.h"

namespace
{
constexpr int enemyWidth = 40;
constexpr int enemyHeight = 30;
}  // namespace

Enemy::Enemy(CMPUT350::Point2D loc) : mLocation(loc), mBounds(), mAlive(true)
{
    UpdateBounds();
}

void Enemy::Initialize(CMPUT350::GameContext* context)
{
}

void Enemy::Update(CMPUT350::GameContext* context)
{
}

void Enemy::LateUpdate(CMPUT350::GameContext* context)
{
}

bool Enemy::HandleKeyEvent(CMPUT350::GameContext* context, char key)
{
    return false;
}

void Enemy::RenderBackground(CMPUT350::GameContext* context)
{
}

void Enemy::RenderForeground(CMPUT350::GameContext* context)
{
    context->ScreenContext->DrawRect(mBounds, CMPUT350::Colors::green);
}

void Enemy::CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj)
{
    std::shared_ptr<Bullet> bullet = std::dynamic_pointer_cast<Bullet>(obj);
    if (bullet == nullptr
        || !bullet->IsPlayerBullet())
    {
        return;
    }

    Kill();

}

void Enemy::Kill()
{
    mAlive = false;
}

bool Enemy::IsAlive() const
{
    return mAlive;
}

const CMPUT350::Rect& Enemy::GetBounds()
{
    return mBounds;
}

void Enemy::UpdateBounds()
{
    mBounds = CMPUT350::Rect(
        CMPUT350::Point2D(mLocation.x - enemyWidth / 2.0f, mLocation.y - enemyHeight / 2.0f),
        enemyWidth,
        enemyHeight);
}
