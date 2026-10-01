#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

namespace CMPUT350 {

class GameContext;

class GameObject {
public:
    /**
     * @brief Destroys the game object.
     * @param None.
     * @return No return value.
     */
    virtual ~GameObject() = default;
    /**
     * @brief Initializes the object after the engine adds it.
     * @param context Pointer to the game context.
     * @return No return value.
     */
    virtual void Initialize(GameContext *context);
    /**
     * @brief Updates the object state once per frame.
     * @param context Pointer to the game context.
     * @return No return value.
     */
    virtual void Update(GameContext *context);
    /**
     * @brief Updates the object after collision processing.
     * @param context Pointer to the game context.
     * @return No return value.
     */
    virtual void LateUpdate(GameContext *context);
    /**
     * @brief Renders interface elements for the object.
     * @param context Pointer to the game context.
     * @return No return value.
     */
    virtual void RenderUI(GameContext *context);
    /**
     * @brief Handles a key press event.
     * @param context Pointer to the game context.
     * @param key Pressed character.
     * @return True if the object consumes the key. False if not.
     */
    virtual bool HandleKeyEvent(GameContext *context, char key);
    /**
     * @brief Checks if the object remains active.
     * @param None.
     * @return True if the object is alive. False if the engine removes it.
     */
    virtual bool IsAlive() const;
    /**
     * @brief Marks the object for removal.
     * @param None.
     * @return No return value.
     */
    virtual void Kill();
};

}  // namespace CMPUT350

#endif  // GAMEOBJECT_H
