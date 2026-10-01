#ifndef COLLISION_OBJECT_H
#define COLLISION_OBJECT_H

#include <memory>

#include "GraphicsObject.h"
#include "MathUtil.h"

namespace CMPUT350 {

class CollisionObject : public GraphicsObject {
public:
    /**
     * @brief Responds to a collision with a different object.
     * @param obj Shared pointer to the other collision object.
     * @return No return value.
     */
    virtual void CollisionEnter(const std::shared_ptr<CollisionObject> &obj) = 0;
    /**
     * @brief Gets the bounding rectangle for collision tests.
     * @param None.
     * @return Constant reference to the bounding rectangle.
     */
    virtual const Rect &GetBounds() = 0;
};

}  // namespace CMPUT350

#endif
