#include "GameEngine.h"

#include "CollisionObject.h"
#include "GameContext.h"

namespace CMPUT350 {
#include "FontData.h"

/**
 * @brief Creates the game window, the font, and the game context.
 * @param width Window width in pixels.
 * @param height Window height in pixels.
 * @param name Window title text.
 * @return No return value.
 */
GameEngine::GameEngine(unsigned int width, unsigned int height, const std::string& name)
    : mFont(std::make_shared<sf::Font>()) {
    if (!mFont->openFromMemory(&_font, _font_len))
    {
    	fprintf(stderr, "WARNING: Font did not load.\n");
    }

    mWindow = std::make_shared<sf::RenderWindow>(
        sf::RenderWindow(sf::VideoMode(
            sf::Vector2u(width, height)), name));
    mWindow->setFramerateLimit(30);
    mWindow->setKeyRepeatEnabled(false);

    mGameContext.mEngineView = this;
    mGameContext.ScreenContext = new DrawContext(mWindow, mFont);
}

/**
 * @brief Closes the window and releases the draw context.
 * @param None.
 * @return No return value.
 */
GameEngine::~GameEngine() {
    delete mGameContext.ScreenContext;
    mWindow->close();
}

/**
 * @brief Queues a game object for activation on the next frame.
 * @param gameObject Shared pointer to the object to add.
 * @return No return value.
 */
void GameEngine::AddGameObject(std::shared_ptr<GameObject> gameObject) {
    mPendingObjects.push_back(gameObject);
}

/**
 * @brief Runs the main loop until the window closes.
 * @param None.
 * @return No return value. The method returns after the window closes.
 * @details The loop removes dead objects, activates pending objects, processes events,
 * updates objects, tests collisions, runs late updates, then renders background and foreground.
 */
void GameEngine::Run() {
    while (mWindow->isOpen()) {
        // 0. Remove dead objects. A new list avoids mutation during iteration.

        std::vector<std::shared_ptr<GameObject>> aliveObjects;
        for (const std::shared_ptr<GameObject>& gameObject : mGameObjects) {
            if (gameObject) {
                if (gameObject->IsAlive()) {
                    aliveObjects.push_back(gameObject);
                }
            }
        }
        std::swap(mGameObjects, aliveObjects);

        // 1. Activate pending objects. Deferred activation keeps the main list stable.
        for (const std::shared_ptr<GameObject>& pendingGameObject : mPendingObjects) {
            if (pendingGameObject) {
                pendingGameObject->Initialize(&mGameContext);
            }
            mGameObjects.push_back(pendingGameObject);
        }
        mPendingObjects.clear();

        // 2. Process events. Only lowercase text and space reach game objects.
        while (const std::optional<sf::Event> event = mWindow->pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                mWindow->close();
                continue;
            }
            if (const auto* keyPressed = event->getIf<sf::Event::TextEntered>()) {
                if (std::islower(keyPressed->unicode) || keyPressed->unicode == ' ') {
                    for (const std::shared_ptr<GameObject>& gameObjectPtr : mGameObjects) {
                        if (GameObject* gameObject = gameObjectPtr.get()) {
                            gameObject->HandleKeyEvent(&mGameContext, keyPressed->unicode);
                        }
                    }
                }
            }
        }

        // 3. Update game objects
        for (const std::shared_ptr<GameObject>& gameObjectPtr : mGameObjects) {
            if (GameObject* gameObject = gameObjectPtr.get()) {
                gameObject->Update(&mGameContext);
            }
        }


        // 4. Test each unordered object pair once for bounding-box overlap.
        for (long int i = 0; i < mGameObjects.size(); i++) {
            std::shared_ptr<CollisionObject> collisionGameObject = std::dynamic_pointer_cast<CollisionObject>(mGameObjects[i]);
            if (collisionGameObject) {
                for (long int k = i + 1; k < mGameObjects.size(); k++) {
                    std::shared_ptr<CollisionObject> otherCollisionGameObject = std::dynamic_pointer_cast<CollisionObject>(mGameObjects[k]);
                    if (otherCollisionGameObject) {
                        Rect intersection = collisionGameObject->GetBounds();
                        intersection &= otherCollisionGameObject->GetBounds();
                        if (intersection.width <= 0 || intersection.height <= 0) {
                            continue;
                        }
                        collisionGameObject->CollisionEnter(otherCollisionGameObject);
                        otherCollisionGameObject->CollisionEnter(collisionGameObject);
                    }
                }
            }
        }

        // 5. Late updates
        for (const std::shared_ptr<GameObject>& gameObjectPtr : mGameObjects) {
            if (GameObject* gameObject = gameObjectPtr.get()) {
                gameObject->LateUpdate(&mGameContext);
            }
        }

        // Clear window
        mWindow->clear();

        // 6. Render background
        for (const std::shared_ptr<GameObject>& gameObjectPtr : mGameObjects) {
            std::shared_ptr<GraphicsObject> graphicsObject = std::dynamic_pointer_cast<GraphicsObject>(gameObjectPtr);
            if (graphicsObject) {
                graphicsObject->RenderBackground(&mGameContext);
            }
        }

        // 7. Render foreground
        for (const std::shared_ptr<GameObject>& gameObjectPtr : mGameObjects) {
            std::shared_ptr<GraphicsObject> graphicsObject = std::dynamic_pointer_cast<GraphicsObject>(gameObjectPtr);
            if (graphicsObject) {
                graphicsObject->RenderForeground(&mGameContext);
            }
        }

        // Actually render to window
        mWindow->display();
    }
}

// Sample code for processing events

// bool GameEngine::ProcessEvents(GameContext *context)
//{
//	while (const std::optional event = mWindow->pollEvent())
//	{
//		if (event->is<sf::Event::Closed>())
//		{
//		}
//		else if (event->is<sf::Event::Resized>())
//		{
//		}
//		else if (const auto* keyPressed = event->getIf<sf::Event::TextEntered>())
//		{
//			// use keyPressed->unicode to get character
//		}
//	}
// }

}  // namespace CMPUT350
