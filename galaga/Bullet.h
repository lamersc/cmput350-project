#ifndef BULLET_H
#define BULLET_H

#include "CollisionObject.h"
#include "GameContext.h"

class Bullet : public CMPUT350::CollisionObject
{
public:
    Bullet(CMPUT350::Point2D location, CMPUT350::Point2D heading, bool player);
    bool IsPlayerBullet();

    void Initialize(CMPUT350::GameContext* context) override;
    void Update(CMPUT350::GameContext* context) override;
    void LateUpdate(CMPUT350::GameContext* context) override;
    bool HandleKeyEvent(CMPUT350::GameContext* context, char key) override;
    bool IsAlive() const override;
    void Kill() override;

    void RenderBackground(CMPUT350::GameContext* context) override;
    void RenderForeground(CMPUT350::GameContext* context) override;

    void CollisionEnter(const std::shared_ptr<CollisionObject>& obj) override;
    const CMPUT350::Rect& GetBounds() override;

private:
    CMPUT350::Point2D mLocation;
    CMPUT350::Point2D mPreviousLocation;
    CMPUT350::Point2D mDirection;
    CMPUT350::Rect mBounds;
    bool mPlayerBullet;
    bool mAlive;
};
#endif  // BULLET_H
