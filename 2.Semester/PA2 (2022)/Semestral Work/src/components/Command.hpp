#pragma once
#include "../game_objects/GameActor.hpp"

// Class which represents commands executed with given actors
struct Command {
  // Virtual destructor for derived classes
  virtual ~Command() = default;
  // Executes command on the actor
  virtual void Execute(GameActor * actor) const = 0;
};

struct TurnUpCommand : public Command {
  void Execute(GameActor * actor) const override;
};

struct TurnDownCommand : public Command {
  void Execute(GameActor * actor) const override;
};

struct TurnRightCommand : public Command {
  void Execute(GameActor * actor) const override;
};

struct TurnLeftCommand : public Command {
  void Execute(GameActor * actor) const override;
};

struct StopMoveCommand : public Command {
  void Execute(GameActor * actor) const override;
};