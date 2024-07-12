#pragma once

#include "../game_objects/GameActor.hpp"
#include "Command.hpp"

/**
 * @brief Controller component class which controls given game object to this component.
 */
class ControllerComponent {

public:

    /**
     * @brief Constructs controller component.
     * @param actor to be controlled by this controller.
     */
    explicit ControllerComponent(GameActor *actor);

    /**
     * @brief Destroys component but not the actor.
     * Actor is destroyed by game itself when closing.
     */
    virtual ~ControllerComponent() = default;

    /**
     * @brief Updates controller component.
     */
    virtual void Update() = 0;

    virtual void FixedUpdate() = 0;

    /**
     * @brief Resets controlled game actor to some status.
     */
    virtual void ResetControlled() = 0;

protected:

    /// Game Actor under control of the given object.
    GameActor *controlled_;

};