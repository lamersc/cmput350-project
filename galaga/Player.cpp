#include "Player.h"

#include <string>

#include "Bullet.h"
#include "Enemy.h"
#include "GameContext.h"

namespace
{
constexpr float playerWidth = 40.0f;
constexpr float playerHeight = 40.0f;
constexpr float heldSpeed = 6.0f;
constexpr float bulletSpeed = 24.0f;
constexpr int fireCooldown = 12;
constexpr int maxPlayerBullets = 2;
}  // namespace

Player::Player(CMPUT350::Point2D loc)
    : mLocation(loc),
      mAlive(true),
      mActive(true),
      mLeft(false),
      mRight(false),
      mFireCooldown(0),
      mWindowWidth(768)
{
    mShapes.push_back(CMPUT350::Shape(
        CMPUT350::Rect(-playerWidth / 2.0f, -playerHeight / 2.0f, playerWidth, playerHeight)));
    UpdateBounds();
}

void Player::Initialize(CMPUT350::GameContext* context)
{
    mSelf = context->CurrObject;
    mContext = context;
    CMPUT350::NotificationManager* manager = context->mNotificationManager;
    manager->Register(mSelf, "LeftDown");
    manager->Register(mSelf, "LeftUp");
    manager->Register(mSelf, "RightDown");
    manager->Register(mSelf, "RightUp");
    manager->Register(mSelf, "FireDown");
    manager->Register(mSelf, "PausePlayer");
    manager->Register(mSelf, "ResumePlayer");
}

void Player::Update(CMPUT350::GameContext* context)
{
    if (mFireCooldown > 0)
    {
        mFireCooldown--;
    }
    mWindowWidth = context->ScreenContext->GetWindowWidth();
    if (mActive)
    {
        if (mLeft)
        {
            Move(-heldSpeed);
        }
        if (mRight)
        {
            Move(heldSpeed);
        }
    }
}

void Player::ReceiveNotification(const std::string& key)
{
    if (key == "LeftDown")
    {
        mLeft = true;
    }
    else if (key == "LeftUp")
    {
        mLeft = false;
    }
    else if (key == "RightDown")
    {
        mRight = true;
    }
    else if (key == "RightUp")
    {
        mRight = false;
    }
    else if (key == "FireDown")
    {
        if (mActive && mFireCooldown <= 0)
        {
            Fire(mContext);
            mFireCooldown = fireCooldown;
        }
    }
    else if (key == "PausePlayer")
    {
        mActive = false;
    }
    else if (key == "ResumePlayer")
    {
        mActive = true;
    }
}

void Player::RenderForeground(CMPUT350::GameContext* context)
{
    const CMPUT350::Point2D nose(0, -20);
    context->ScreenContext->DrawRect(CMPUT350::Rect(CMPUT350::Point2D(-4, -18), 8, 36),
                                     CMPUT350::Colors::white);
    context->ScreenContext->DrawLine(nose, CMPUT350::Point2D(-4, -10), 2,
                                     CMPUT350::Colors::white);
    context->ScreenContext->DrawLine(nose, CMPUT350::Point2D(4, -10), 2,
                                     CMPUT350::Colors::white);
    context->ScreenContext->DrawLine(CMPUT350::Point2D(-4, 2), CMPUT350::Point2D(-20, 16), 4,
                                     CMPUT350::Colors::red);
    context->ScreenContext->DrawLine(CMPUT350::Point2D(4, 2), CMPUT350::Point2D(20, 16), 4,
                                     CMPUT350::Colors::red);
    context->ScreenContext->DrawRect(CMPUT350::Rect(CMPUT350::Point2D(-8, 14), 16, 4),
                                     CMPUT350::Colors::gray);
    context->ScreenContext->DrawCircle(CMPUT350::Point2D(0, -6), 3, CMPUT350::Colors::cyan);
}

void Player::CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj)
{
    std::shared_ptr<Bullet> bullet = std::dynamic_pointer_cast<Bullet>(obj);
    if (bullet != nullptr)
    {
        if (!bullet->IsPlayerBullet() && !bullet->IsDestroyed())
        {
            Kill();
        }
        return;
    }
    if (std::dynamic_pointer_cast<Enemy>(obj) != nullptr)
    {
        Kill();
    }
}

void Player::Kill()
{
    if (!mAlive)
    {
        return;
    }
    mAlive = false;
    mContext->mNotificationManager->Notify("PlayerDied");
}

bool Player::IsAlive() const
{
    return mAlive;
}

const CMPUT350::Rect& Player::GetBounds()
{
    return mBounds;
}

const std::vector<CMPUT350::Shape>& Player::GetShapes()
{
    return mShapes;
}

CMPUT350::Point2D Player::GetLocation() const
{
    return mLocation;
}

float Player::GetRotation() const
{
    return 0.0f;
}

void Player::UpdateBounds()
{
    mBounds = CMPUT350::Rect(mLocation, playerWidth / 2.0f);
}

void Player::Move(float distance)
{
    const float halfWidth = playerWidth / 2.0f;
    mLocation.x = std::clamp(mLocation.x + distance, halfWidth,
                             mWindowWidth - halfWidth);
    UpdateBounds();
}

void Player::Fire(CMPUT350::GameContext* context)
{
    if (ActivePlayerBullets(context) >= maxPlayerBullets)
    {
        return;
    }
    const CMPUT350::Point2D bulletStart(mLocation.x, mLocation.y - playerHeight / 2.0f);
    const CMPUT350::Point2D bulletHeading(0, -bulletSpeed);
    context->mEngineView->AddGameObject(
        std::make_shared<Bullet>(bulletStart, bulletHeading, true, mSelf));
}

int Player::ActivePlayerBullets(CMPUT350::GameContext* context)
{
    int count = 0;
    for (auto it = context->mEngineView->begin(); it != context->mEngineView->end(); ++it)
    {
        std::shared_ptr<Bullet> bullet = std::dynamic_pointer_cast<Bullet>(*it);
        if (bullet != nullptr && bullet->IsAlive() && !bullet->IsDestroyed() &&
            bullet->IsPlayerBullet())
        {
            count++;
        }
    }
    return count;
}
