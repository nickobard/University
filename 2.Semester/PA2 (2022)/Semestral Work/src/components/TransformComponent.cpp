#include "TransformComponent.hpp"

TransformComponent::TransformComponent()
: direction_(Vector2<float>::Right())
, position_({0,0})
, velocity_(GAME_SPEED)
{}

TransformComponent::TransformComponent(Vector2<float> initialPosition, int direction = UP  )
: position_(initialPosition)
, velocity_ (GAME_SPEED)
{
  SetDirection(direction);
}


TransformComponent::~TransformComponent() = default;

void TransformComponent::Translate(){
  Translate(velocity_);
}

void TransformComponent::Translate(const float & velocity){

  Vector2<float> newPosition = position_ + direction_ * velocity_ * GameLocator::GetTime().GetDeltaTime();

  if (newPosition.x_ > static_cast<float>(SCREED_WIDTH))
    newPosition.x_ = static_cast<float>(SCREED_WIDTH);
  else if (newPosition.x_ < 0.0f)
    newPosition.x_ = 0.0f;

  if (newPosition.y_ > static_cast<float>(SCREEN_HEIGHT))
    newPosition.y_ = static_cast<float>(SCREEN_HEIGHT);
  else if (newPosition.y_ < 0.0f)
    newPosition.y_ = 0.0f;

  position_ = newPosition;
}

void TransformComponent::SetDirection(const int value){

  switch(value){
    case UP:
      direction_= Vector2<float>::Down();
      break;
    case DOWN:
      direction_= Vector2<float>::Up();
      break;
    case RIGHT:
      direction_= Vector2<float>::Right();
      break;
    case LEFT:
      direction_= Vector2<float>::Left();
      break;
  } 

}