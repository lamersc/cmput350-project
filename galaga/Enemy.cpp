#include "Enemy.h"

#include <cmath>
#include <numbers>

#include "Bezier.h"
#include "Bullet.h"
#include "Player.h"

namespace
{
constexpr float enemyWidth = 28.0f;
constexpr float enemyHeight = 22.0f;
constexpr float enterSpeed = 5.0f;
constexpr float attackSpeed = 6.0f;
constexpr float returnSpeed = 6.0f;
constexpr float enemyBulletSpeed = 4.0f;
constexpr int firePeriod = 48;
}  // namespace

Enemy::Enemy(CMPUT350::Point2D loc, const std::vector<CMPUT350::Point2D>& path, int health,
             int pointsFormation, int pointsAttack)
    : mHomeLocation(loc),
      mEntryPath(path),
      mRotation(0.0f),
      mEntryT(0.0f),
      mAttackT(0.0f),
      mReturnT(0.0f),
      mState(kEntering),
      mHealth(health),
      mPointsFormation(pointsFormation),
      mPointsAttack(pointsAttack),
      mAlive(true),
      mScored(false)
{
    mShapes.push_back(
        CMPUT350::Shape(CMPUT350::Rect(-enemyWidth / 2.0f, -enemyHeight / 2.0f,
                                       enemyWidth, enemyHeight)));
    mLocation = CMPUT350::Bezier(mEntryPath).GetPoint(0.0f);
    UpdateBounds();
}

void Enemy::Initialize(CMPUT350::GameContext* context)
{
    mSelf = context->CurrObject;
    mContext = context;
    context->mNotificationManager->Register(mSelf, "KillEnemies");
}

void Enemy::Update(CMPUT350::GameContext* context)
{
    switch (mState)
    {
        case kEntering:
            if (FollowPath(mEntryPath, mEntryT, enterSpeed))
            {
                mState = kFormation;
            }
            break;
        case kFormation:
        {
            const float hover =
                std::sin(context->currentFrame * 0.05f) * 20.0f;
            mLocation = mHomeLocation + CMPUT350::Point2D(hover, 0);
            mRotation = 0.0f;
            UpdateBounds();
            break;
        }
        case kAttacking:
            if (FollowPath(mAttackPath, mAttackT, attackSpeed))
            {
                StartReturn();
            }
            else if (context->currentFrame % firePeriod
                     == static_cast<int>(mHomeLocation.x) % firePeriod)
            {
                Fire(context, mTarget);
            }
            break;
        case kReturning:
            if (FollowPath(mReturnPath, mReturnT, returnSpeed))
            {
                mState = kFormation;
            }
            break;
    }
}

void Enemy::ReceiveNotification(const std::string& key)
{
    if (key == "KillEnemies")
    {
        Kill();
    }
}

bool Enemy::IsAlive() const
{
    return mAlive;
}

void Enemy::Kill()
{
    if (!mAlive)
    {
        return;
    }
    mAlive = false;
    if (mContext != nullptr)
    {
        mContext->mNotificationManager->Notify("EnemyDied");
    }
}

void Enemy::CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj)
{
    std::shared_ptr<Bullet> bullet = std::dynamic_pointer_cast<Bullet>(obj);
    if (bullet != nullptr)
    {
        if (bullet->IsPlayerBullet() && !bullet->IsDestroyed())
        {
            TakeDamage();
        }
        return;
    }
    if (std::dynamic_pointer_cast<Player>(obj) != nullptr)
    {
        Kill();
    }
}

const CMPUT350::Rect& Enemy::GetBounds()
{
    return mBounds;
}

const std::vector<CMPUT350::Shape>& Enemy::GetShapes()
{
    return mShapes;
}

CMPUT350::Point2D Enemy::GetLocation() const
{
    return mLocation;
}

float Enemy::GetRotation() const
{
    return mRotation;
}

bool Enemy::IsEntering() const
{
    return mState == kEntering;
}

bool Enemy::IsInFormation() const
{
    return mState == kFormation;
}

int Enemy::GetPoints() const
{
    return mState == kFormation ? mPointsFormation : mPointsAttack;
}

bool Enemy::IsScored() const
{
    return mScored;
}

void Enemy::MarkScored()
{
    mScored = true;
}

void Enemy::Fire(CMPUT350::GameContext* context, const CMPUT350::Point2D& target)
{
    CMPUT350::Point2D heading = target - mLocation;
    heading.Normalize();
    heading *= enemyBulletSpeed;
    context->mEngineView->AddGameObject(
        std::make_shared<Bullet>(mLocation, heading, false, mSelf));
}

bool Enemy::FollowPath(const std::vector<CMPUT350::Point2D>& path, float& t, float speed)
{
    const CMPUT350::Bezier bezier(path);
    const int segments = static_cast<int>((path.size() - 1) / 3);
    CMPUT350::Point2D slope = bezier.GetSlope(std::min(t, static_cast<float>(segments)));
    const float length = std::sqrt(slope.Dot(slope));
    t += length > 1.0f ? speed / length : 0.05f;
    if (t >= segments)
    {
        t = static_cast<float>(segments);
    }
    mLocation = bezier.GetPoint(t);
    slope = bezier.GetSlope(t);
    const float slopeLength = std::sqrt(slope.Dot(slope));
    if (slopeLength > 0.001f)
    {
        mRotation = std::atan2(slope.y, slope.x) - std::numbers::pi_v<float> / 2.0f;
    }
    UpdateBounds();
    return t >= static_cast<float>(segments);
}

void Enemy::StartReturn()
{
    const CMPUT350::Point2D start = mLocation;
    mReturnPath = {start, start + CMPUT350::Point2D(0, -350),
                   CMPUT350::Point2D(mHomeLocation.x, mHomeLocation.y + 350),
                   mHomeLocation};
    mReturnT = 0.0f;
    mState = kReturning;
}

void Enemy::UpdateBounds()
{
    mBounds = CMPUT350::Rect(mLocation.x - enemyWidth / 2.0f,
                             mLocation.y - enemyHeight / 2.0f, enemyWidth, enemyHeight);
}

void Enemy::TakeDamage()
{
    if (--mHealth <= 0)
    {
        Kill();
    }
}

bool Enemy1::Attack(CMPUT350::GameContext* context, const CMPUT350::Point2D& target)
{
    if (mState != kFormation)
    {
        return false;
    }
    mTarget = target;
    const CMPUT350::Point2D start = mLocation;
    const float bottom = context->ScreenContext->GetWindowHeight() + 80.0f;
    mAttackPath = {start,
                   start + CMPUT350::Point2D(160, 180),
                   start + CMPUT350::Point2D(-140, 420),
                   CMPUT350::Point2D(start.x, (start.y + target.y) / 2.0f),
                   CMPUT350::Point2D(target.x + 160, target.y - 220),
                   CMPUT350::Point2D(target.x - 160, target.y + 40),
                   CMPUT350::Point2D(target.x, bottom)};
    mAttackT = 0.0f;
    mState = kAttacking;
    return true;
}

void Enemy1::RenderForeground(CMPUT350::GameContext* context)
{
    const CMPUT350::RGBColor body =
        mHealth >= 2 ? CMPUT350::Colors::blue : CMPUT350::Colors::cyan;
    context->ScreenContext->DrawCircle(CMPUT350::Point2D(0, 0), 11, body);
    context->ScreenContext->DrawLine(CMPUT350::Point2D(-10, -2),
                                     CMPUT350::Point2D(-10, 12), 3,
                                     CMPUT350::Colors::white);
    context->ScreenContext->DrawLine(CMPUT350::Point2D(10, -2),
                                     CMPUT350::Point2D(10, 12), 3,
                                     CMPUT350::Colors::white);
    context->ScreenContext->DrawCircle(CMPUT350::Point2D(0, 4), 3,
                                       CMPUT350::Colors::white);
}

bool Enemy2::Attack(CMPUT350::GameContext* context, const CMPUT350::Point2D& target)
{
    if (mState != kFormation)
    {
        return false;
    }
    mTarget = target;
    const CMPUT350::Point2D start = mLocation;
    const float bottom = context->ScreenContext->GetWindowHeight() + 80.0f;
    mAttackPath = {start,
                   start + CMPUT350::Point2D(-140, 260),
                   CMPUT350::Point2D(target.x + 180, start.y + 380),
                   CMPUT350::Point2D(target.x - 60, target.y - 80),
                   CMPUT350::Point2D(target.x + 120, target.y + 150),
                   CMPUT350::Point2D(target.x - 120, bottom - 200),
                   CMPUT350::Point2D(target.x, bottom)};
    mAttackT = 0.0f;
    mState = kAttacking;
    return true;
}

void Enemy2::RenderForeground(CMPUT350::GameContext* context)
{
    context->ScreenContext->DrawRect(
        CMPUT350::Rect(-12, -8, 24, 16), CMPUT350::Colors::red);
    context->ScreenContext->DrawLine(CMPUT350::Point2D(-12, -4),
                                     CMPUT350::Point2D(12, -4), 2,
                                     CMPUT350::Colors::white);
}

bool Enemy3::Attack(CMPUT350::GameContext* context, const CMPUT350::Point2D& target)
{
    if (mState != kFormation)
    {
        return false;
    }
    mTarget = target;
    const CMPUT350::Point2D start = mLocation;
    const float bottom = context->ScreenContext->GetWindowHeight() + 80.0f;
    mAttackPath = {start,
                   CMPUT350::Point2D(start.x - 180, start.y + 180),
                   CMPUT350::Point2D(start.x + 200, start.y + 260),
                   CMPUT350::Point2D(start.x + 40, start.y + 430),
                   CMPUT350::Point2D(target.x - 180, target.y - 260),
                   CMPUT350::Point2D(target.x + 180, target.y - 60),
                   CMPUT350::Point2D(target.x, bottom)};
    mAttackT = 0.0f;
    mState = kAttacking;
    return true;
}

void Enemy3::RenderForeground(CMPUT350::GameContext* context)
{
    context->ScreenContext->DrawLine(CMPUT350::Point2D(0, 10),
                                     CMPUT350::Point2D(-12, -8), 3,
                                     CMPUT350::Colors::yellow);
    context->ScreenContext->DrawLine(CMPUT350::Point2D(0, 10),
                                     CMPUT350::Point2D(12, -8), 3,
                                     CMPUT350::Colors::yellow);
    context->ScreenContext->DrawLine(CMPUT350::Point2D(-12, -8),
                                     CMPUT350::Point2D(12, -8), 3,
                                     CMPUT350::Colors::yellow);
}
