#ifndef GRAPHICS_OBJECT_H
#define GRAPHICS_OBJECT_H

#include "GameObject.h"

namespace CMPUT350 {

class GameContext;

class GraphicsObject : public GameObject {
public:
    /**
     * @brief Renders the background layer of the object.
     * @param context Pointer to the game context.
     * @return No return value.
     */
    virtual void RenderBackground(GameContext *context);
    /**
     * @brief Renders the foreground layer of the object.
     * @param context Pointer to the game context.
     * @return No return value.
     */
    virtual void RenderForeground(GameContext *context);
};

}  // namespace CMPUT350

#endif
