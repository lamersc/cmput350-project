#ifndef GALAGA_H
#define GALAGA_H

#include <string>

#include "GameObject.h"
#include "MathUtil.h"

class Enemy;
class Player;

class Galaga : public CMPUT350::GameObject
{
public:
    Galaga(int width, int height);

    void Initialize(CMPUT350::GameContext* context) override;
    void Update(CMPUT350::GameContext* context) override;
    void RenderUI(CMPUT350::GameContext* context) override;
    void ReceiveNotification(const std::string& key) override;
    bool IsAlive() const override;

private:
    enum State
    {
        kWaiting,
        kStartup,
        kWaves,
        kGamePlay,
        kGameOver
    };

    void StartGame();
    void StartStage();
    void SpawnEnemy(int index);
    void SpawnPlayer();
    void HandleRespawn(CMPUT350::GameContext* context);
    bool AllEnemiesSettled(CMPUT350::GameContext* context) const;
    bool AnyEnemyEntering(CMPUT350::GameContext* context) const;
    void ScheduleAttacks(CMPUT350::GameContext* context);
    void AwardScore();
    CMPUT350::Point2D PlayerLocation() const;

    int mWidth;
    int mHeight;
    State mState;
    CMPUT350::GameContext* mContext;
    std::weak_ptr<Player> mPlayer;
    int mCredits;
    int mLives;
    int mLevel;
    int mScore;
    int mStateTimer;
    int mSpawnTimer;
    int mSpawned;
    int mAliveEnemies;
    int mAttackTimer;
    int mAttackRound;
    bool mPlayerDead;
    int mRespawnTimer;
};

#endif  // GALAGA_H
