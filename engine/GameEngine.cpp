#include "GameEngine.h"

#include <algorithm>

#include "CollisionObject.h"
#include "GameContext.h"

namespace CMPUT350 {
#include "FontData.h"

namespace {

void NotifyKey(NotificationManager* manager,
               const std::unordered_map<int, std::vector<std::string>>& notifications, int key) {
    const auto entry = notifications.find(key);
    if (entry == notifications.end()) {
        return;
    }
    for (const std::string& notification : entry->second) {
        manager->Notify(notification);
    }
}

bool CollideLineCircle(const Line& line, const Circle& circle, Point2D& collisionPoint) {
    const Point2D f = line.p1 - circle.center;
    if (f.x * f.x + f.y * f.y <= circle.radius * circle.radius) {
        // then collision is inside the circle
        collisionPoint = line.p1;
        return true;
    }
    const Point2D d = line.p2 - line.p1;
    const float a = d.Dot(d);
    if (a <= 0.0f) {
        return false;
    }
    const float b = 2.0f * f.Dot(d);
    const float c = f.Dot(f) - circle.radius * circle.radius;
    const float discriminant = b * b - 4.0f * a * c;
    if (discriminant < 0.0f) {
        return false;
    }
    const float t = (-b - std::sqrt(discriminant)) / (2.0f * a);
    if (t < 0.0f || t > 1.0f) {
        return false;
    }
    collisionPoint = Line::Tween(line.p1, line.p2, t);
    return true;
}

bool CollideLineRect(const Line& line, const Rect& rect, Point2D& collisionPoint) {
    if (rect.IsInside(line.p1)) {
        collisionPoint = line.p1;
        return true;
    }
    const Point2D topLeft = rect.topLeft;
    const Point2D bottomRight = rect.topLeft + Point2D(rect.width, rect.height);
    const Line edges[4] = {Line(topLeft, Point2D(bottomRight.x, topLeft.y)),
                           Line(Point2D(bottomRight.x, topLeft.y), bottomRight),
                           Line(bottomRight, Point2D(topLeft.x, bottomRight.y)),
                           Line(Point2D(topLeft.x, bottomRight.y), topLeft)};
    bool collisionFound = false;
    double firstDistance = 0.0;
    Point2D firstPoint;
    for (const Line& edge : edges) {
        Point2D crossing;
        if (edge.Crosses(line, crossing)) {
            const double distance = line.p1.Distance(crossing);
            if (!collisionFound || distance < firstDistance) { // second check is since we want the closest collision point
                collisionFound = true;
                firstDistance = distance;
                firstPoint = crossing;
            }
        }
    }
    if (collisionFound) {
        collisionPoint = firstPoint;
        return true;
    }
    return false;
}

bool CollideCircleCircle(const Circle& a, const Circle& b, Point2D& collisionPoint) {
    const double distance = a.center.Distance(b.center);
    if (distance > a.radius + b.radius) {
        return false;
    }
    if (distance > 0.0) {
        collisionPoint = a.center + static_cast<float>(a.radius) * (b.center - a.center) *
                                        static_cast<float>(1.0 / distance);
    } else {
        collisionPoint = a.center;
    }
    return true;
}

bool CollideCircleRect(const Circle& circle, const Rect& rect, Point2D& collisionPoint) {
    const Point2D clamped(
        std::clamp(circle.center.x, rect.topLeft.x, rect.topLeft.x + rect.width),
        std::clamp(circle.center.y, rect.topLeft.y, rect.topLeft.y + rect.height));
    if (clamped.Distance(circle.center) <= circle.radius) {
        collisionPoint = clamped;
        return true;
    }
    return false;
}

bool CollideRectRect(const Rect& a, const Rect& b, Point2D& collisionPoint) {
    Rect intersection = a;
    intersection &= b;
    if (intersection.width <= 0.0f || intersection.height <= 0.0f) {
        return false;
    }
    collisionPoint =
        intersection.topLeft + Point2D(intersection.width / 2.0f, intersection.height / 2.0f);
    return true;
}

bool CollideShapes(const Shape& a, const Shape& b, Point2D& collisionPoint) {
    switch (a.t) {
        case ShapeType::kLine:
            switch (b.t) {
                case ShapeType::kLine:
                    return a.shape.line.Crosses(b.shape.line, collisionPoint);
                case ShapeType::kCircle:
                    return CollideLineCircle(a.shape.line, b.shape.circle, collisionPoint);
                case ShapeType::kRect:
                    return CollideLineRect(a.shape.line, b.shape.rect, collisionPoint);
            }
            break;
        case ShapeType::kCircle:
            switch (b.t) {
                case ShapeType::kLine:
                    return CollideLineCircle(b.shape.line, a.shape.circle, collisionPoint);
                case ShapeType::kCircle:
                    return CollideCircleCircle(a.shape.circle, b.shape.circle, collisionPoint);
                case ShapeType::kRect:
                    return CollideCircleRect(a.shape.circle, b.shape.rect, collisionPoint);
            }
            break;
        case ShapeType::kRect:
            switch (b.t) {
                case ShapeType::kLine:
                    return CollideLineRect(b.shape.line, a.shape.rect, collisionPoint);
                case ShapeType::kCircle:
                    return CollideCircleRect(b.shape.circle, a.shape.rect, collisionPoint);
                case ShapeType::kRect:
                    return CollideRectRect(a.shape.rect, b.shape.rect, collisionPoint);
            }
            break;
    }
    return false;
}

}  // namespace

Shape GameEngine::TransformShape(const Shape& shape) {
    DrawContext* context = mGameContext.ScreenContext;
    switch (shape.t) {
        case ShapeType::kLine:
            return Shape(Line(context->Transform(shape.shape.line.p1),
                              context->Transform(shape.shape.line.p2)));
        case ShapeType::kCircle:
            return Shape(Circle(context->Transform(shape.shape.circle.center),
                                shape.shape.circle.radius));
        case ShapeType::kRect:
            return Shape(context->Transform(shape.shape.rect));
    }
    return Shape(Rect());
}

void GameEngine::ResolveCollisionPair(const std::shared_ptr<CollisionObject>& a,
                                      const std::shared_ptr<CollisionObject>& b) {
    Rect intersection = a->GetBounds();
    intersection &= b->GetBounds();
    if (intersection.width <= 0.0f || intersection.height <= 0.0f) {
        return;
    }
    if (a->GetShapes().empty() || b->GetShapes().empty()) {
        // just give the bounding boxes
        mGameContext.CurrObject = a;
        a->CollisionEnter(b);
        mGameContext.CurrObject = b;
        b->CollisionEnter(a);
        return;
    }
    const Point2D offsetA = a->GetLocation();
    const float rotationA = a->GetRotation();
    const Point2D offsetB = b->GetLocation();
    const float rotationB = b->GetRotation();
    // move the shapes into world space for collisions

    mGameContext.ScreenContext->SetContextOffset(offsetA);
    mGameContext.ScreenContext->SetContextRotation(rotationA);
    std::vector<Shape> worldShapesA;
    for (const Shape& shape : a->GetShapes()) {
        worldShapesA.push_back(TransformShape(shape));
    }
    mGameContext.ScreenContext->SetContextOffset(offsetB);
    mGameContext.ScreenContext->SetContextRotation(rotationB);
    std::vector<Shape> worldShapesB;
    for (const Shape& shape : b->GetShapes()) {
        worldShapesB.push_back(TransformShape(shape));
    }
    for (const Shape& worldA : worldShapesA) {
        for (const Shape& worldB : worldShapesB) {
            Point2D collisionPoint;
            if (CollideShapes(worldA, worldB, collisionPoint)) {
                // collisions want local points to work with (say we want some collision animation and such)
                const Point2D localPointA = ToLocal(collisionPoint, offsetA, rotationA);
                const Point2D localPointB = ToLocal(collisionPoint, offsetB, rotationB);
                mGameContext.CurrObject = a;
                a->CollisionEnter(b, localPointA);
                mGameContext.CurrObject = b;
                b->CollisionEnter(a, localPointB);
                return;
            }
        }
    }
}

Point2D GameEngine::ToLocal(Point2D p, Point2D offset, float rotation) {
    mGameContext.ScreenContext->SetContextOffset(offset);
    mGameContext.ScreenContext->SetContextRotation(rotation);
    return mGameContext.ScreenContext->ReverseTransform(p);
}

/**
 * @brief Creates the game window, the font, and the game context.
 * @param width Window width in pixels.
 * @param height Window height in pixels.
 * @param name Window title text.
 * @return No return value.
 */
GameEngine::GameEngine(unsigned int width, unsigned int height, const std::string& name)
    : mFont(std::make_shared<sf::Font>()) {
    if (!mFont->openFromMemory(&_font, _font_len)) {
        fprintf(stderr, "WARNING: Font did not load.\n");
    }

    mWindow = std::make_shared<sf::RenderWindow>(
        sf::RenderWindow(sf::VideoMode(sf::Vector2u(width, height)), name));
    mWindow->setFramerateLimit(30);
    mWindow->setKeyRepeatEnabled(false);

    mGameContext.mEngineView = this;
    mGameContext.ScreenContext = new DrawContext(mWindow, mFont);
    mGameContext.GUIContext = new DrawContext(mWindow, mFont);
    mGameContext.mNotificationManager = new NotificationManager();
    mGameContext.currentFrame = 0;
}

/**
 * @brief Closes the window and releases the draw context.
 * @param None.
 * @return No return value.
 */
GameEngine::~GameEngine() {
    delete mGameContext.mNotificationManager;
    delete mGameContext.GUIContext;
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

void GameEngine::InstallKeyDownNotification(int key, const std::string& notification) {
    mKeyDownNotifications[key].push_back(notification);
}

void GameEngine::InstallKeyUpNotification(int key, const std::string& notification) {
    mKeyUpNotifications[key].push_back(notification);
}

GameEngine::const_iterator GameEngine::cbegin() const { return mGameObjects.cbegin(); }

GameEngine::const_iterator GameEngine::cend() const { return mGameObjects.cend(); }

GameEngine::const_iterator GameEngine::begin() const { return mGameObjects.begin(); }

GameEngine::const_iterator GameEngine::end() const { return mGameObjects.end(); }

/**
 * @brief Runs the main loop until the window closes.
 * @param None.
 * @return No return value. The method returns after the window closes.
 * @details The loop removes dead objects, activates pending objects, processes events,
 * updates objects, tests collisions, runs late updates, then renders background and foreground.
 */
void GameEngine::Run() {
    while (mWindow->isOpen()) {
        mGameContext.currentFrame++;

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
                mGameContext.CurrObject = pendingGameObject;
                pendingGameObject->Initialize(&mGameContext);
            }
            mGameObjects.push_back(pendingGameObject);
        }
        mPendingObjects.clear();

        // 2. Process events. key presses and releases send a notification via the notification manager (if its registered)
        while (const std::optional<sf::Event> event = mWindow->pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                mWindow->close();
                continue;
            }

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                NotifyKey(mGameContext.mNotificationManager, mKeyDownNotifications,
                          static_cast<int>(keyPressed->scancode));
            } else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {
                NotifyKey(mGameContext.mNotificationManager, mKeyUpNotifications,
                          static_cast<int>(keyReleased->scancode));
            }
        }

        // 3. Update game objects
        for (const std::shared_ptr<GameObject>& gameObjectPtr : mGameObjects) {
            if (GameObject* gameObject = gameObjectPtr.get()) {
                mGameContext.CurrObject = gameObjectPtr;
                gameObject->Update(&mGameContext);
            }
        }

        // 4. Test each unordered pair of collision objects once.
        std::vector<std::shared_ptr<CollisionObject>> colliders;
        for (const std::shared_ptr<GameObject>& gameObjectPtr : mGameObjects) {
            if (std::shared_ptr<CollisionObject> collider =
                    std::dynamic_pointer_cast<CollisionObject>(gameObjectPtr)) {
                colliders.push_back(collider);
            }
        }
        for (size_t i = 0; i < colliders.size(); i++) {
            for (size_t k = i + 1; k < colliders.size(); k++) {
                ResolveCollisionPair(colliders[i], colliders[k]);
            }
        }

        // 5. Late updates
        for (const std::shared_ptr<GameObject>& gameObjectPtr : mGameObjects) {
            if (GameObject* gameObject = gameObjectPtr.get()) {
                mGameContext.CurrObject = gameObjectPtr;
                gameObject->LateUpdate(&mGameContext);
            }
        }

        // Clear window
        mWindow->clear();

        // 6. Render background.
        for (const std::shared_ptr<GameObject>& gameObjectPtr : mGameObjects) {
            std::shared_ptr<GraphicsObject> graphicsObject =
                std::dynamic_pointer_cast<GraphicsObject>(gameObjectPtr);
            if (graphicsObject) {
                mGameContext.CurrObject = gameObjectPtr;
                mGameContext.ScreenContext->SetContextOffset(graphicsObject->GetLocation());
                mGameContext.ScreenContext->SetContextRotation(graphicsObject->GetRotation());
                graphicsObject->RenderBackground(&mGameContext);
            }
        }

        // 7. Render foreground
        for (const std::shared_ptr<GameObject>& gameObjectPtr : mGameObjects) {
            std::shared_ptr<GraphicsObject> graphicsObject =
                std::dynamic_pointer_cast<GraphicsObject>(gameObjectPtr);
            if (graphicsObject) {
                mGameContext.CurrObject = gameObjectPtr;
                mGameContext.ScreenContext->SetContextOffset(graphicsObject->GetLocation());
                mGameContext.ScreenContext->SetContextRotation(graphicsObject->GetRotation());
                graphicsObject->RenderForeground(&mGameContext);
            }
        }

        // Reset the transform so later passes draw in window space.
        mGameContext.ScreenContext->SetContextOffset(Point2D(0, 0));
        mGameContext.ScreenContext->SetContextRotation(0.0f);

        // 8. Render UI
        for (const std::shared_ptr<GameObject>& gameObjectPtr : mGameObjects) {
            if (GameObject* gameObject = gameObjectPtr.get()) {
                mGameContext.CurrObject = gameObjectPtr;
                gameObject->RenderUI(&mGameContext);
            }
        }

        // Actually render to window
        mWindow->display();
    }
}

}  // namespace CMPUT350
