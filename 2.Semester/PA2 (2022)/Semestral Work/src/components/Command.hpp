#pragma once

#include "../game_objects/GameActor.hpp"

/**
 * @brief Class which represents commands executed with given game actor object.
 */
class Command {
public:
    virtual ~Command() = default;

    /**
     * @brief Executes command with give actor.
     * @param actor which should execute the command.
     */
    virtual void Execute(GameActor *actor) = 0;
};

class TurnUpCommand : public Command {
public:
    void Execute(GameActor *actor) override;
};

class TurnDownCommand : public Command {
public:
    void Execute(GameActor *actor) override;
};

class TurnRightCommand : public Command {
public:
    void Execute(GameActor *actor) override;
};

class TurnLeftCommand : public Command {
public:
    void Execute(GameActor *actor) override;
};

class StopMoveCommand : public Command {
public:
    void Execute(GameActor *actor) override;
};

class MoveCommand : public Command {
public:
    void Execute(GameActor *actor) override;
};
