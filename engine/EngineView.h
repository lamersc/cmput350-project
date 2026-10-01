#ifndef ENGINEVIEW_H
#define ENGINEVIEW_H

#include <memory>
#include <vector>

namespace CMPUT350 {

class GameObject;

class EngineView {
public:
    /**
     * @brief Queues a game object for activation on the next frame.
     * @param gameObject Shared pointer to the object to add.
     * @return No return value.
     */
    virtual void AddGameObject(std::shared_ptr<GameObject> gameObject) = 0;
};

}  // namespace CMPUT350

#endif
