#include "GameEngine.h"

#include "CollisionObject.h"
#include "GameContext.h"

/// @brief
namespace CMPUT350 {
#include "FontData.h"

GameEngine::GameEngine(unsigned int width, unsigned int height, const std::string& name) : mGameContext(new GameContext()) {
    if (!mFont->openFromMemory(&_font, _font_len))
    {
    	fprintf(stderr, "WARNING: Font did not load.\n");
    }

    mWindow = std::make_shared<sf::RenderWindow>(
        sf::RenderWindow(sf::VideoMode(
            sf::Vector2u(width, height)), name));
}

GameEngine::~GameEngine() {
    mWindow->close();
}

void GameEngine::AddGameObject(std::shared_ptr<GameObject> gameObject) {
    mPendingObjects.push_back(gameObject);
}

/**
 * @method Run
 * @arguments None
 * @description Gives control to the game engine. Will not return until the game window is closed or
 * all objects have been destroyed.
 */
void GameEngine::Run() {
    while (true)  // window is open
    {
        // 0. Remove any objects that are now dead

        std::vector<std::shared_ptr<GameObject>> aliveObjects;
        for (const std::shared_ptr<GameObject>& gameObject : mGameObjects) {
            if (gameObject) {
                if (gameObject->IsAlive()) {
                    aliveObjects.push_back(gameObject);
                }
            }
        }
        std::swap(mGameObjects, aliveObjects);

        // 1. Activate and initialize any objects added during the last frame
        for (const std::shared_ptr<GameObject>& pendingGameObject : mPendingObjects) {
            if (pendingGameObject) {
                pendingGameObject->Initialize(mGameContext);
            }
            mGameObjects.push_back(pendingGameObject);
        }
        mPendingObjects.clear();

        // 2. Process events
        while (const std::optional<sf::Event> event = mWindow->pollEvent()) {
            if (const auto* keyPressed = event->getIf<sf::Event::TextEntered>()) {
                if (std::islower(keyPressed->unicode)) {
                    for (const std::shared_ptr<GameObject>& gameObjectPtr : mGameObjects) {
                        if (GameObject* gameObject = gameObjectPtr.get()) {
                            gameObject->HandleKeyEvent(mGameContext, keyPressed->unicode);
                        }
                    }
                }
            }
        }

        // 3. Update game objects
        for (const std::shared_ptr<GameObject>& gameObjectPtr : mGameObjects) {
            if (GameObject* gameObject = gameObjectPtr.get()) {
                gameObject->Update(mGameContext);
            }
        }


        // 4. Process collision events
        for (long int i = 0; i < mGameObjects.size(); i++) {
            std::shared_ptr<CollisionObject> collisionGameObject = std::dynamic_pointer_cast<CollisionObject>(mGameObjects[i]);
            if (collisionGameObject) {
                for (long int k = i + 1; k < mGameObjects.size(); k++) {
                    std::shared_ptr<CollisionObject> otherCollisionGameObject = std::dynamic_pointer_cast<CollisionObject>(mGameObjects[k]);
                    if (otherCollisionGameObject) {
                        collisionGameObject->CollisionEnter(otherCollisionGameObject);
                        otherCollisionGameObject->CollisionEnter(collisionGameObject);
                    }
                }
            }
        }

        // 5. Late updates
        for (const std::shared_ptr<GameObject>& gameObjectPtr : mGameObjects) {
            if (GameObject* gameObject = gameObjectPtr.get()) {
                gameObject->LateUpdate(mGameContext);
            }
        }

        // Clear window
        mWindow->clear();

        // 6. Render background
        for (const std::shared_ptr<GameObject>& gameObjectPtr : mGameObjects) {
            std::shared_ptr<GraphicsObject> graphicsObject = std::dynamic_pointer_cast<GraphicsObject>(gameObjectPtr);
            if (graphicsObject) {
                graphicsObject->RenderBackground(mGameContext);
            }
        }

        // 7. Render foreground
        for (const std::shared_ptr<GameObject>& gameObjectPtr : mGameObjects) {
            std::shared_ptr<GraphicsObject> graphicsObject = std::dynamic_pointer_cast<GraphicsObject>(gameObjectPtr);
            if (graphicsObject) {
                graphicsObject->RenderForeground(mGameContext);
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
