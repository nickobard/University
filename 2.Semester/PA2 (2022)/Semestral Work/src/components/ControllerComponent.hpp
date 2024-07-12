#pragma once
#include "../game_objects/GameActor.hpp"
#include "Command.hpp"
/**
 * @brief Abstract class which controls given actor using commands
 * 
 */
class ControllerComponent{
  public:
    // Contructs component with given game actor
    ControllerComponent(GameActor * actor);
    // Destroys component and its actor
    virtual ~ControllerComponent() = default;
    // Updates controller component
    virtual void Update() = 0;
  protected:
    // Game Actor under control of the given object
    GameActor * actor_;
  private:
    // Deletes all commands in the subclasses
    virtual void FreeCommands() = 0;
};