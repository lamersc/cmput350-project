#ifndef PLAYER_H
#define PLAYER_H

#include <memory>

#include "CollisionObject.h"

class Bullet;

class Player : public CMPUT350::CollisionObject
{
public:
    Player(CMPUT350::Point2D loc);

    void Initialize(CMPUT350::GameContext* context) override;
    void Update(CMPUT350::GameContext* context) override;
    void LateUpdate(CMPUT350::GameContext* context) override;
    bool HandleKeyEvent(CMPUT350::GameContext* context, char key) override;
    bool IsAlive() const override;
    void Kill() override;

    void RenderBackground(CMPUT350::GameContext* context) override;
    void RenderForeground(CMPUT350::GameContext* context) override;

    void CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj) override;
    const CMPUT350::Rect& GetBounds() override;

private:
    void UpdateBounds();
    void Move(float distance);
    void Fire(CMPUT350::GameContext* context);

    CMPUT350::Point2D mLocation;
    CMPUT350::Rect mBounds;
    bool mAlive;
    std::weak_ptr<Bullet> mBulletSlots[2];
    int mWindowWidth;
};

#endif
