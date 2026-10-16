#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <string>
#include <vector>

#include "CollisionObject.h"

class Bullet;

class Player : public CMPUT350::CollisionObject
{
public:
    Player(CMPUT350::Point2D loc);

    void Initialize(CMPUT350::GameContext* context) override;
    void Update(CMPUT350::GameContext* context) override;
    void ReceiveNotification(const std::string& key) override;
    bool IsAlive() const override;
    void Kill() override;
    void RenderForeground(CMPUT350::GameContext* context) override;

    void CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj) override;
    const CMPUT350::Rect& GetBounds() override;
    const std::vector<CMPUT350::Shape>& GetShapes() override;
    CMPUT350::Point2D GetLocation() const override;
    float GetRotation() const override;

private:
    void UpdateBounds();
    void Move(float distance);
    void Fire(CMPUT350::GameContext* context);
    int ActivePlayerBullets(CMPUT350::GameContext* context);

    CMPUT350::Point2D mLocation;
    CMPUT350::Rect mBounds;
    std::vector<CMPUT350::Shape> mShapes;
    std::weak_ptr<CMPUT350::GameObject> mSelf;
    CMPUT350::GameContext* mContext;
    bool mAlive;
    bool mActive;
    bool mLeft;
    bool mRight;
    int mFireCooldown;
    int mWindowWidth;
};

#endif  // PLAYER_H
