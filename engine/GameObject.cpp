#include "GameObject.h"

namespace CMPUT350 {

/**
 * @brief Initializes the object after the engine adds it.
 * @param context Pointer to the game context.
 * @return No return value. The default version does nothing.
 */
void GameObject::Initialize(GameContext *context) { return; }
/**
 * @brief Updates the object state once per frame.
 * @param context Pointer to the game context.
 * @return No return value. The default version does nothing.
 */
void GameObject::Update(GameContext *context) { return; }
/**
 * @brief Updates the object after collision processing.
 * @param context Pointer to the game context.
 * @return No return value. The default version does nothing.
 */
void GameObject::LateUpdate(GameContext *context) { return; }
/**
 * @brief Renders interface elements for the object.
 * @param contextrender Pointer to the game context.
 * @return No return value. The default version does nothing.
 */
void GameObject::RenderUI(GameContext *contextrender) { return; }
/**
 * @brief Handles a key press event.
 * @param context Pointer to the game context.
 * @param key Pressed character.
 * @return False. The default version consumes no key.
 */
bool GameObject::HandleKeyEvent(GameContext *context, char key) { return false; }
/**
 * @brief Checks if the object remains active.
 * @param None.
 * @return True. The default object lives until a subclass changes it.
 */
bool GameObject::IsAlive() const { return true; }
/**
 * @brief Marks the object for removal.
 * @param None.
 * @return No return value. The default version does nothing.
 */
void GameObject::Kill() {}
}  // namespace CMPUT350
