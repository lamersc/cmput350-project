
#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "GameContext.h"

namespace CMPUT350 {
class GameEngine;
}

#include "CollisionObject.h"
#include "EngineView.h"
#include "GameObject.h"
#include "MathUtil.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>
#include <unordered_map>
#include <vector>

namespace CMPUT350 {

class DrawContext;

class GameEngine : public EngineView {
public:
    /**
     * @brief Creates the game window, the font, and the game context.
     * @param width Window width in pixels.
     * @param height Window height in pixels.
     * @param name Window title text.
     * @return No return value. The constructor initializes the engine.
     */
    GameEngine(unsigned int width, unsigned int height, const std::string& name);
    /**
     * @brief Closes the window and releases the draw context.
     * @param None.
     * @return No return value.
     */
    ~GameEngine();

    GameEngine(const GameEngine&) = delete;             // Prevent copy-construction
    GameEngine(GameEngine&&) = delete;                  // Prevent move-construction
    GameEngine& operator=(const GameEngine&) = delete;  // Prevent assignment
    GameEngine& operator=(GameEngine&&) = delete;       // Prevent move-assignment

    /**
     * @brief Queues a game object for activation on the next frame.
     * @param gameObject Shared pointer to the object to add.
     * @return No return value.
     */
    void AddGameObject(std::shared_ptr<GameObject> gameObject) override;
    void InstallKeyDownNotification(int key, const std::string &notification) override;
    void InstallKeyUpNotification(int key, const std::string &notification) override;
    const_iterator cbegin() const override;
    const_iterator cend() const override;
    const_iterator begin() const override;
    const_iterator end() const override;

    /**
     * @brief Runs the main loop until the window closes.
     * @param None.
     * @return No return value. The method returns after the window closes.
     */
    void Run();

private:
    Shape TransformShape(const Shape& shape);
    void ResolveCollisionPair(const std::shared_ptr<CollisionObject>& a,
                              const std::shared_ptr<CollisionObject>& b);
    Point2D ToLocal(Point2D p, Point2D offset, float rotation);

    GameContext mGameContext;
    std::vector<std::shared_ptr<GameObject>> mPendingObjects;
    std::vector<std::shared_ptr<GameObject>> mGameObjects;
    std::unordered_map<int, std::vector<std::string>> mKeyDownNotifications;
    std::unordered_map<int, std::vector<std::string>> mKeyUpNotifications;
    std::shared_ptr<sf::RenderWindow> mWindow;
    std::shared_ptr<sf::Font> mFont;
};

}  // namespace CMPUT350

#endif  // GAMEENGINE_H
