#include "GameActor.hpp"

GameActor::GameActor (TransformComponent * transform, GraphicsComponent * graphics)
: transform_ (transform)
, graphics_ (graphics)
{}

GameActor::~GameActor (){
  FreeObject();
}

void GameActor::FreeObject(){
  delete transform_;
  delete graphics_ ;
}