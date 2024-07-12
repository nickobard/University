#pragma  once

#include "../ControllerComponent.hpp"
#include "../AICommands.hpp"

/**
 * @brief Class that represents AI behavior component, defined through different commands.
 */
class AIComponent : public ControllerComponent {

public:

    /**
     * @brief Constructs AIComponent.
     * @param controlled object that is controlled by the AI.
     * @param player object of the player, used in target commands.
     */
    AIComponent(GameActor *controlled, GameActor *player);

    /**
     * @brief Destroys AI component with its allocated commands.
     */
    ~AIComponent() override;

    void Update() override;

    void FixedUpdate() override;

    void ResetControlled() override;

private:

    /// Command to move actor further.
    Command *moveActor_;

    /// Command to chase player.
    TargetCommand *chasePlayer_;
    /// Command to try catch player.
    TargetCommand *catchPlayer_;

    /// Player game actor object.
    GameActor *player_;

};