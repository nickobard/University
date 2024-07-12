#include "PlayerController.hpp"
#include "../game_engine/GameLocator.hpp"

PlayerController::PlayerController(GameActor *actor)
        : ControllerComponent(actor)
          , buttonUp_(new TurnUpCommand())
          , buttonDown_(new TurnDownCommand())
          , buttonLeft_(new TurnLeftCommand())
          , buttonRight_(new TurnRightCommand())
          , buttonEscape_(new StopMoveCommand())
          , moveActor_(new MoveCommand()) {}

PlayerController::~PlayerController() {
    delete buttonUp_;
    delete buttonDown_;
    delete buttonLeft_;
    delete buttonRight_;
    delete buttonEscape_;
    delete moveActor_;
}

void PlayerController::Update() {

    const uint8_t *currentKeyStates = SDL_GetKeyboardState(nullptr);

    if (currentKeyStates[SDL_SCANCODE_UP])
        buttonUp_->Execute(controlled_);
    else if (currentKeyStates[SDL_SCANCODE_DOWN])
        buttonDown_->Execute(controlled_);
    else if (currentKeyStates[SDL_SCANCODE_LEFT])
        buttonLeft_->Execute(controlled_);
    else if (currentKeyStates[SDL_SCANCODE_RIGHT])
        buttonRight_->Execute(controlled_);
    else if (currentKeyStates[SDL_SCANCODE_ESCAPE])
        buttonEscape_->Execute(controlled_);

    moveActor_->Execute(controlled_);
}

void PlayerController::ResetControlled() {
    auto spawnTileNode = GameLocator::GetMap().GetMapInfo().playerSpawn_;
    controlled_->GetPhysics()->currentNode_ = spawnTileNode;
    controlled_->SetState(STANDING);
    controlled_->GetTransform()->direction_ = Vector2<float>::Right();
    controlled_->GetTransform()->position_ = spawnTileNode->GetTransform()->position_;
}