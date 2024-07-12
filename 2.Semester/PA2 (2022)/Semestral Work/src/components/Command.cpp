#include "Command.hpp"

void TurnUpCommand::Execute(GameActor * actor) const{
  actor->TurnUp();
}
void TurnDownCommand::Execute(GameActor * actor) const{
  actor->TurnDown();
}
void TurnRightCommand::Execute(GameActor * actor) const{
  actor->TurnRight();
}
void TurnLeftCommand::Execute(GameActor * actor) const{
  actor->TurnLeft();
}
void StopMoveCommand::Execute(GameActor * actor) const{
  actor->StopMoving();
}
