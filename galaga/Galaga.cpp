#include "Galaga.h"

#include <memory>
#include <vector>

#include <SFML/Window/Keyboard.hpp>

#include "Enemy.h"
#include "GameContext.h"
#include "NotificationManager.h"
#include "Player.h"

namespace
{
constexpr int enemiesPerWave = 8;
constexpr int waveCount = 5;
constexpr int totalEnemies = enemiesPerWave * waveCount;
constexpr int spawnInterval = 4;
constexpr int startupFrames = 90;
constexpr int gameOverFrames = 240;
constexpr int attackInterval = 150;
constexpr int maxAttackers = 2;
constexpr int respawnDelay = 45;
constexpr int coinsToStart = 5;
constexpr float playerBottomMargin = 200.0f;
}  // namespace

Galaga::Galaga(int width, int height)
    : mWidth(width),
      mHeight(height),
      mState(kWaiting),
      mContext(nullptr),
      mCredits(0),
      mLives(0),
      mLevel(1),
      mScore(0),
      mStateTimer(0),
      mSpawnTimer(0),
      mSpawned(0),
      mAliveEnemies(0),
      mAttackTimer(0),
      mAttackRound(0),
      mPlayerDead(false),
      mRespawnTimer(0)
{
}

void Galaga::Initialize(CMPUT350::GameContext* context)
{
    mContext = context;
    CMPUT350::EngineView* view = context->mEngineView;
    const auto install = [view](int key, bool down, const std::string& notification) {
        if (down)
        {
            view->InstallKeyDownNotification(key, notification);
        }
        else
        {
            view->InstallKeyUpNotification(key, notification);
        }
    };
    const auto scan = [](sf::Keyboard::Scancode code) {
        return static_cast<int>(code);
    };
    install(scan(sf::Keyboard::Scancode::A), true, "LeftDown");
    install(scan(sf::Keyboard::Scancode::A), false, "LeftUp");
    install(scan(sf::Keyboard::Scancode::Left), true, "LeftDown");
    install(scan(sf::Keyboard::Scancode::Left), false, "LeftUp");
    install(scan(sf::Keyboard::Scancode::D), true, "RightDown");
    install(scan(sf::Keyboard::Scancode::D), false, "RightUp");
    install(scan(sf::Keyboard::Scancode::Right), true, "RightDown");
    install(scan(sf::Keyboard::Scancode::Right), false, "RightUp");
    install(scan(sf::Keyboard::Scancode::Space), true, "FireDown");
    install(scan(sf::Keyboard::Scancode::Num5), true, "Coin");
    install(scan(sf::Keyboard::Scancode::Num1), true, "StartGame");

    CMPUT350::NotificationManager* manager = context->mNotificationManager;
    manager->Register(context->CurrObject, "Coin");
    manager->Register(context->CurrObject, "StartGame");
    manager->Register(context->CurrObject, "EnemyDied");
    manager->Register(context->CurrObject, "PlayerDied");
}

void Galaga::Update(CMPUT350::GameContext* context)
{
    CMPUT350::NotificationManager* manager = context->mNotificationManager;
    if (mState == kStartup)
    {
        manager->Notify("PausePlayer");
    }
    else if (mState == kWaves || mState == kGamePlay)
    {
        manager->Notify("ResumePlayer");
    }

    switch (mState)
    {
        case kWaiting:
            break;
        case kStartup:
            if (++mStateTimer >= startupFrames)
            {
                mState = kWaves;
                mSpawnTimer = 0;
            }
            break;
        case kWaves:
            if (mSpawned < totalEnemies)
            {
                if (mSpawnTimer > 0)
                {
                    mSpawnTimer--;
                }
                else
                {
                    SpawnEnemy(mSpawned++);
                    mSpawnTimer = spawnInterval;
                }
            }
            else if (mAliveEnemies <= 0)
            {
                StartStage();
            }
            else if (!AnyEnemyEntering(context))
            {
                mState = kGamePlay;
            }
            HandleRespawn(context);
            break;
        case kGamePlay:
            if (mAliveEnemies <= 0)
            {
                StartStage();
                break;
            }
            if (!mPlayerDead && ++mAttackTimer >= attackInterval)
            {
                mAttackTimer = 0;
                ScheduleAttacks(context);
            }
            HandleRespawn(context);
            break;
        case kGameOver:
            if (++mStateTimer >= gameOverFrames)
            {
                manager->Notify("KillEnemies");
                mState = kWaiting;
            }
            break;
    }

    if (mRespawnTimer > 0)
    {
        mRespawnTimer--;
    }
}

void Galaga::RenderUI(CMPUT350::GameContext* context)
{
    CMPUT350::DrawContext* gui = context->GUIContext;
    const CMPUT350::Point2D center(mWidth / 2.0f, mHeight / 2.0f);
    gui->DrawText("SCORE " + std::to_string(mScore), 24, CMPUT350::Point2D(10, 10),
                  CMPUT350::Colors::white);
    switch (mState)
    {
        case kWaiting:
            gui->DrawCenteredText("GALAGA", 64, center + CMPUT350::Point2D(0, -150),
                                  CMPUT350::Colors::cyan);
            gui->DrawCenteredText("PRESS 5 TO INSERT COIN", 24, center,
                                  CMPUT350::Colors::white);
            gui->DrawCenteredText("PRESS 1 TO START", 24, center + CMPUT350::Point2D(0, 60),
                                  CMPUT350::Colors::white);
            gui->DrawCenteredText("CREDITS " + std::to_string(mCredits), 24,
                                  center + CMPUT350::Point2D(0, 300),
                                  CMPUT350::Colors::white);
            break;
        case kStartup:
            gui->DrawCenteredText("STAGE " + std::to_string(mLevel), 48, center,
                                  CMPUT350::Colors::white);
            gui->DrawText("LIVES " + std::to_string(mLives), 24, CMPUT350::Point2D(10, 40),
                          CMPUT350::Colors::white);
            break;
        case kWaves:
        case kGamePlay:
            gui->DrawText("LIVES " + std::to_string(mLives), 24, CMPUT350::Point2D(10, 40),
                          CMPUT350::Colors::white);
            break;
        case kGameOver:
            gui->DrawCenteredText("GAME OVER", 48, center, CMPUT350::Colors::red);
            break;
    }
    if (mRespawnTimer > 0)
    {
        gui->DrawCenteredText("READY - LIVES " + std::to_string(mLives), 24,
                              center + CMPUT350::Point2D(0, -80), CMPUT350::Colors::yellow);
    }
}

void Galaga::ReceiveNotification(const std::string& key)
{
    if (key == "Coin")
    {
        mCredits++;
    }
    else if (key == "StartGame")
    {
        if (mState == kWaiting && mCredits >= coinsToStart)
        {
            mCredits -= coinsToStart;
            StartGame();
        }
    }
    else if (key == "EnemyDied")
    {
        mAliveEnemies--;
        if (mState == kWaves || mState == kGamePlay)
        {
            AwardScore();
        }
    }
    else if (key == "PlayerDied")
    {
        mLives--;
        if (mLives <= 0)
        {
            mState = kGameOver;
            mStateTimer = 0;
        }
        else
        {
            mPlayerDead = true;
            mRespawnTimer = 0;
        }
    }
}

bool Galaga::IsAlive() const
{
    return true;
}

void Galaga::StartGame()
{
    mScore = 0;
    mLives = 3;
    mLevel = 1;
    mSpawned = 0;
    mSpawnTimer = 0;
    mAliveEnemies = 0;
    mAttackTimer = 0;
    mAttackRound = 0;
    mPlayerDead = false;
    SpawnPlayer();
    mState = kStartup;
    mStateTimer = 0;
}

void Galaga::StartStage()
{
    mLevel++;
    mSpawned = 0;
    mSpawnTimer = 0;
    mAttackTimer = 0;
    if (mPlayerDead || mPlayer.expired())
    {
        mPlayerDead = false;
        SpawnPlayer();
        mRespawnTimer = respawnDelay;
    }
    mState = kStartup;
    mStateTimer = 0;
}

void Galaga::SpawnEnemy(int index)
{
    const int row = index / enemiesPerWave;
    const int col = index % enemiesPerWave;
    const CMPUT350::Point2D home(64.0f + col * 92.0f, 120.0f + row * 56.0f);
    const int side = (index % 2 == 0) ? -1 : 1;
    const std::vector<CMPUT350::Point2D> path = {
        CMPUT350::Point2D(mWidth / 2.0f, -50.0f),
        CMPUT350::Point2D(mWidth / 2.0f + side * 280.0f, 300.0f),
        CMPUT350::Point2D(home.x - side * 220.0f, home.y + 220.0f),
        home};
    std::shared_ptr<Enemy> enemy;
    if (row == 0)
    {
        enemy = std::make_shared<Enemy1>(home, path);
    }
    else if (row <= 2)
    {
        enemy = std::make_shared<Enemy2>(home, path);
    }
    else
    {
        enemy = std::make_shared<Enemy3>(home, path);
    }
    mContext->mEngineView->AddGameObject(enemy);
    mAliveEnemies++;
}

void Galaga::SpawnPlayer()
{
    std::shared_ptr<Player> player =
        std::make_shared<Player>(CMPUT350::Point2D(mWidth / 2.0f, mHeight - playerBottomMargin));
    mPlayer = player;
    mContext->mEngineView->AddGameObject(player);
}

void Galaga::HandleRespawn(CMPUT350::GameContext* context)
{
    if (mPlayerDead && AllEnemiesSettled(context))
    {
        mPlayerDead = false;
        SpawnPlayer();
        mRespawnTimer = respawnDelay;
    }
}

bool Galaga::AllEnemiesSettled(CMPUT350::GameContext* context) const
{
    for (auto it = context->mEngineView->begin(); it != context->mEngineView->end(); ++it)
    {
        std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(*it);
        if (enemy != nullptr && enemy->IsAlive() && !enemy->IsInFormation())
        {
            return false;
        }
    }
    return true;
}

bool Galaga::AnyEnemyEntering(CMPUT350::GameContext* context) const
{
    for (auto it = context->mEngineView->begin(); it != context->mEngineView->end(); ++it)
    {
        std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(*it);
        if (enemy != nullptr && enemy->IsAlive() && enemy->IsEntering())
        {
            return true;
        }
    }
    return false;
}

void Galaga::ScheduleAttacks(CMPUT350::GameContext* context)
{
    const CMPUT350::Point2D target = PlayerLocation();
    int ordinal = 0;
    int asked = 0;
    for (auto it = context->mEngineView->begin(); it != context->mEngineView->end(); ++it)
    {
        std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(*it);
        if (enemy == nullptr || !enemy->IsAlive() || !enemy->IsInFormation())
        {
            continue;
        }
        if ((ordinal + mAttackRound) % 5 == 0 && asked < maxAttackers)
        {
            if (enemy->Attack(context, target))
            {
                asked++;
            }
        }
        ordinal++;
    }
    mAttackRound++;
}

void Galaga::AwardScore()
{
    for (auto it = mContext->mEngineView->begin(); it != mContext->mEngineView->end(); ++it)
    {
        std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(*it);
        if (enemy != nullptr && !enemy->IsAlive() && !enemy->IsScored())
        {
            mScore += enemy->GetPoints();
            enemy->MarkScored();
        }
    }
}

CMPUT350::Point2D Galaga::PlayerLocation() const
{
    if (std::shared_ptr<Player> player = mPlayer.lock())
    {
        return player->GetLocation();
    }
    return CMPUT350::Point2D(mWidth / 2.0f, mHeight - playerBottomMargin);
}
