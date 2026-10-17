#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H
#include "GameObject.h"
#include <memory>
#include <unordered_map>
#include <vector>

namespace CMPUT350 {

/**
 * @brief Sends string messages between game objects without direct references.
 * @details Objects register as listeners for message keys. Notify passes a
 * message to every live listener immediately. The manager holds only weak
 * pointers, so it never keeps objects alive and drops listeners that expire.
 */
class NotificationManager {
public:
    /**
     * @brief Adds an object to the listeners of a message key.
     * @param object Weak pointer to the object that wants the message.
     * @param key Message key the object listens for.
     * @return No return value. Duplicate registrations are ignored.
     */
    void Register(std::weak_ptr<GameObject> object, const std::string& key);

    /**
     * @brief Removes an object from the listeners of a message key.
     * @param object Weak pointer to the object to remove.
     * @param key Message key the object no longer wants.
     * @return No return value. Expired listeners are also removed.
     */
    void Unregister(std::weak_ptr<GameObject> object, const std::string& key);

    /**
     * @brief Sends a message to every live listener registered for it.
     * @param message Message key to deliver.
     * @return No return value. Delivery happens immediately, and expired
     * listeners are dropped from the list during delivery.
     */
    void Notify(const std::string& message);

private:
    std::unordered_map<std::string, std::vector<std::weak_ptr<GameObject>>> mListeners;
};
}

#endif
