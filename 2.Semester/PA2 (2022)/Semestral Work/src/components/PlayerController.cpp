#include "PlayerController.hpp"

PlayerController::PlayerController(GameActor * actor)
: ControllerComponent(actor)
, buttonUp_ (new TurnUpCommand())
, buttonDown_ (new TurnDownCommand())
, buttonLeft_ (new TurnLeftCommand())
, buttonRight_ (new TurnRightCommand())
, buttonEscape_ (new StopMoveCommand())
{}

PlayerController::~PlayerController(){
  FreeCommands();
}

void PlayerController::FreeCommands(){
  delete buttonUp_   ;
  delete buttonDown_ ;
  delete buttonLeft_ ;
  delete buttonRight_;
  delete buttonEscape_;
}

void PlayerController::Update(){
  const uint8_t * currentKeyStates = SDL_GetKeyboardState(nullptr);
  if (currentKeyStates[SDL_SCANCODE_UP])
    buttonUp_->Execute(actor_);
  else if (currentKeyStates[SDL_SCANCODE_DOWN])
    buttonDown_->Execute(actor_);
  else if (currentKeyStates[SDL_SCANCODE_LEFT])
    buttonLeft_->Execute(actor_);
  else if (currentKeyStates[SDL_SCANCODE_RIGHT])
    buttonRight_->Execute(actor_);
  else if (currentKeyStates[SDL_SCANCODE_ESCAPE])
    buttonEscape_->Execute(actor_);


}