#ifndef ENEMY_H
#define ENEMY_H

#include <memory>
#include <vector>

#include "CollisionObject.h"
#include "GameContext.h"

class Bullet;

class Enemy : public CMPUT350::CollisionObject
{
public:
    Enemy(CMPUT350::Point2D loc, const std::vector<CMPUT350::Point2D>& path, int health,
          int pointsFormation, int pointsAttack);

    void Initialize(CMPUT350::GameContext* context) override;
    void Update(CMPUT350::GameContext* context) override;
    void ReceiveNotification(const std::string& key) override;
    bool IsAlive() const override;
    void Kill() override;
    void CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj) override;
    const CMPUT350::Rect& GetBounds() override;
    const std::vector<CMPUT350::Shape>& GetShapes() override;
    CMPUT350::Point2D GetLocation() const override;
    float GetRotation() const override;

    virtual bool Attack(CMPUT350::GameContext* context, const CMPUT350::Point2D& target) = 0;

    bool IsEntering() const;
    bool IsInFormation() const;
    int GetPoints() const;
    bool IsScored() const;
    void MarkScored();

protected:
    virtual void Fire(CMPUT350::GameContext* context, const CMPUT350::Point2D& target);
    bool FollowPath(const std::vector<CMPUT350::Point2D>& path, float& t, float speed);
    void StartReturn();
    void UpdateBounds();
    void TakeDamage();

    enum State
    {
        kEntering,
        kFormation,
        kAttacking,
        kReturning
    };

    CMPUT350::Point2D mLocation;
    CMPUT350::Point2D mHomeLocation;
    CMPUT350::Point2D mTarget;
    float mRotation;
    CMPUT350::Rect mBounds;
    std::vector<CMPUT350::Shape> mShapes;
    std::vector<CMPUT350::Point2D> mEntryPath;
    std::vector<CMPUT350::Point2D> mAttackPath;
    std::vector<CMPUT350::Point2D> mReturnPath;
    std::weak_ptr<CMPUT350::GameObject> mSelf;
    CMPUT350::GameContext* mContext;
    float mEntryT;
    float mAttackT;
    float mReturnT;
    State mState;
    int mHealth;
    int mPointsFormation;
    int mPointsAttack;
    bool mAlive;
    bool mScored;
};

class Enemy1 : public Enemy
{
public:
    Enemy1(CMPUT350::Point2D loc, const std::vector<CMPUT350::Point2D>& path)
        : Enemy(loc, path, 2, 100, 200)
    {
    }
    bool Attack(CMPUT350::GameContext* context, const CMPUT350::Point2D& target) override;
    void RenderForeground(CMPUT350::GameContext* context) override;
};

class Enemy2 : public Enemy
{
public:
    Enemy2(CMPUT350::Point2D loc, const std::vector<CMPUT350::Point2D>& path)
        : Enemy(loc, path, 1, 60, 120)
    {
    }
    bool Attack(CMPUT350::GameContext* context, const CMPUT350::Point2D& target) override;
    void RenderForeground(CMPUT350::GameContext* context) override;
};

class Enemy3 : public Enemy
{
public:
    Enemy3(CMPUT350::Point2D loc, const std::vector<CMPUT350::Point2D>& path)
        : Enemy(loc, path, 1, 40, 80)
    {
    }
    bool Attack(CMPUT350::GameContext* context, const CMPUT350::Point2D& target) override;
    void RenderForeground(CMPUT350::GameContext* context) override;
};

#endif  // ENEMY_H
