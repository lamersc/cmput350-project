#ifndef ENGINEVIEW_H
#define ENGINEVIEW_H

#include <memory>
#include <vector>

namespace CMPUT350 {

class GameObject;

class EngineView {
    using tGameObject = std::vector<std::shared_ptr<GameObject>>;

public:
    /**
     * @brief Queues a game object for activation on the next frame.
     * @param gameObject Shared pointer to the object to add.
     * @return No return value.
     */
    virtual void AddGameObject(std::shared_ptr<GameObject> gameObject) = 0;

    /**
     * @brief Registers a notification to send when a key is pressed down.
     * @param key Key scancode to watch.
     * @param notification Message sent to the notification manager on press.
     * @return No return value. Multiple notifications can share one key.
     */
    virtual void InstallKeyDownNotification(int, const std::string &notification) = 0;
    /**
     * @brief Registers a notification to send when a key is released.
     * @param key Key scancode to watch.
     * @param notification Message sent to the notification manager on release.
     * @return No return value. Multiple notifications can share one key.
     */
    virtual void InstallKeyUpNotification(int, const std::string &notification) = 0;
    /**
     * @brief Iterator type over the objects contained in the engine.
     * @details Points to shared pointers of GameObject, in engine order.
     */
    using const_iterator = tGameObject::const_iterator;
    /**
     * @brief Gets an iterator to the first object in the engine.
     * @param None.
     * @return Constant iterator to the first contained object.
     */
    virtual const_iterator cbegin() const = 0;
    /**
     * @brief Gets an iterator past the last object in the engine.
     * @param None.
     * @return Constant iterator one past the final contained object.
     */
    virtual const_iterator cend() const = 0;
    /**
     * @brief Gets an iterator to the first object in the engine.
     * @param None.
     * @return Constant iterator to the first contained object.
     */
    virtual const_iterator begin() const = 0;
    /**
     * @brief Gets an iterator past the last object in the engine.
     * @param None.
     * @return Constant iterator one past the final contained object.
     */
    virtual const_iterator end() const = 0;

};

}  // namespace CMPUT350

#endif
