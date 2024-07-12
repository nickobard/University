#pragma once

#include "ControllerComponent.hpp"

/**
 * @brief Controller to get user input and control given actor.
 */
class PlayerController : public ControllerComponent {

public:

    /**
     * @brief Constructs controller with injected actor.
     * @param actor to take control of by player.
     */
    explicit PlayerController(GameActor *actor);

    /**
     * @brief Destroys controller and its commands.
     */
    ~PlayerController() override;

    void Update() override;

    void FixedUpdate() override;

    void ResetControlled() override;

protected:

    /// Command executed by up arrow button.
    Command *buttonUp_;
    /// Command executed by down arrow button.
    Command *buttonDown_;
    /// Command executed by left arrow button.
    Command *buttonLeft_;
    /// Command executed by right arrow button.
    Command *buttonRight_;
    /// Command executed by escape button.
    Command *buttonEscape_;

    /// Command to move actor further.
    Command *moveActor_;

};