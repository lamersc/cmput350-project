#include "NotificationManager.h"

#include <algorithm>

namespace CMPUT350 {

void NotificationManager::Register(std::weak_ptr<GameObject> object, const std::string& key) {
    std::vector<std::weak_ptr<GameObject>>& listeners = mListeners[key];
    if (std::shared_ptr<GameObject> shared = object.lock()) {
        for (const std::weak_ptr<GameObject>& listener : listeners) {
            if (listener.lock() == shared) {
                return;
            }
        }
    }
    listeners.push_back(object);
}

void NotificationManager::Unregister(std::weak_ptr<GameObject> object, const std::string& key) {
    const auto entry = mListeners.find(key);
    if (entry == mListeners.end()) {
        return;
    }
    std::vector<std::weak_ptr<GameObject>>& listeners = entry->second;
    listeners.erase(std::remove_if(listeners.begin(), listeners.end(),
                                   [&object](const std::weak_ptr<GameObject>& listener) {
                                       return listener.expired() ||
                                              listener.lock() == object.lock();
                                   }),
                    listeners.end());
}

void NotificationManager::Notify(const std::string& message) {
    const auto entry = mListeners.find(message);
    if (entry == mListeners.end()) {
        return;
    }
    std::vector<std::weak_ptr<GameObject>>& listeners = entry->second;
    std::vector<std::weak_ptr<GameObject>> alive;
    alive.reserve(listeners.size());
    for (const std::weak_ptr<GameObject>& listener : listeners) {
        if (std::shared_ptr<GameObject> object = listener.lock()) {
            object->ReceiveNotification(message);
            alive.push_back(object);
        }
    }
    std::swap(listeners, alive);
}

}  // namespace CMPUT350
