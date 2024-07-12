#include "Command.hpp"
#include "../game_objects/Tile.hpp"

/**
 * @brief Represent command where are interacting two objects.
 */
class TargetCommand {
public:
    virtual ~TargetCommand() = default;

    /**
     * @brief Executes command with give game actor objects.
     * @param controlled first object which does something.
     * @param target which is affected by the controlled object.
     */
    virtual void Execute(GameActor *controlled, GameActor *target) = 0;
};


/**
 * @brief TargetCommand to chase player given player object.
 */
class ChasePlayerCommand : public TargetCommand {
public:
    void Execute(GameActor *controlled, GameActor *target) override;

protected:

    /**
     * @brief Check whether current tile is cross tile where can decide where to go.
     */
    void CheckTile();

    /**
     * @brief Returns direction where to turn.
     * @return direction to turn.
     */
    Vector2<float> DecideDirection();

    /**
     * @brief Check if specified direction is better that previously best decision.
     * @param direction where to check if is better direction to turn.
     * @param decision currently best decision where to turn.
     */
    void CheckDirection(const Vector2<float> &direction, pair<Vector2<float>, float> &decision) const;

    /// Player game actor object.
    GameActor *player_;
    /// Game actor object under control of the command.
    GameActor *controlled_;
    /// Represents last tile node where decision already has been made.
    const TileNode *decidedNode_;

};

/**
 * @brief Command to try to catch target. If caught - report to game manager about the catch.
 */
class CatchPlayerCommand : public TargetCommand {
public:
    void Execute(GameActor *controlled, GameActor *target) override;

};