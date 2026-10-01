#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H

#include "DrawContext.h"
#include "EngineView.h"
#include "GameObject.h"

namespace CMPUT350 {

/**
 * @brief Holds shared engine services for game objects.
 * @details mEngineView adds new objects. ScreenContext draws shapes and text.
 */
class GameContext {
public:
    EngineView *mEngineView;
    DrawContext *ScreenContext;
};

}  // namespace CMPUT350

#endif  // GAMECONTEXT_H
