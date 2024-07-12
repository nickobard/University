#pragma once
#include "ControllerComponent.hpp"
/**
 * @brief Controller to get user input and controll given actor
 * 
 */
class PlayerController : public ControllerComponent {
  public:
    // Contructs controller with injected actor
    PlayerController(GameActor * actor);
    // Destroys controller
    ~PlayerController();
    // Updates controller state - reads input and executes commands
    void Update() override;
  protected:
    // Command executed by up arrow button
    Command * buttonUp_   ; 
    // Command executed by down arrow button
    Command * buttonDown_ ;
    // Command executed by left arrow button
    Command * buttonLeft_ ;
    // Command executed by rifht arrow button
    Command * buttonRight_;
    // Command executed by escape button
    Command * buttonEscape_;
  private:
    // Deletes all allocated commands
    void FreeCommands() override;
};