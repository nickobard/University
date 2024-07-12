#include "Command.hpp"

void TurnUpCommand::Execute(GameActor *actor) {
    actor->TurnUp();
}

void TurnDownCommand::Execute(GameActor *actor) {
    actor->TurnDown();
}

void TurnRightCommand::Execute(GameActor *actor) {
    actor->TurnRight();
}

void TurnLeftCommand::Execute(GameActor *actor) {
    actor->TurnLeft();
}

void StopMoveCommand::Execute(GameActor *actor) {
    actor->StopMoving();
}

void MoveCommand::Execute(GameActor *actor) {
    actor->Move();
}