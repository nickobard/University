#include "Pacman.hpp"


Pacman::Pacman (TransformComponent * transform, GraphicsComponent * graphics)
: GameActor (transform, graphics)
{}

void Pacman::TurnUp(){
  transform_->SetDirection(UP);
  transform_->SetDefaultVelocity();
}      
void Pacman::TurnDown(){
  transform_->SetDirection(DOWN);
  transform_->SetDefaultVelocity();

}
void Pacman::TurnRight(){
  transform_->SetDirection(RIGHT);
  transform_->SetDefaultVelocity();

}
void Pacman::TurnLeft(){
  transform_->SetDirection(LEFT);
  transform_->SetDefaultVelocity();

}
void Pacman::StopMoving(){
  transform_->SetVelocity(0.0f);
}

void Pacman::Update() {
  transform_->Translate();

}
void Pacman::Render() {
  graphics_->Render(transform_->GetPosition());
}