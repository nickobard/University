#include "GameActor.hpp"
#include "../game_engine/GameLocator.hpp"

GameActor::GameActor(TransformComponent *transform, GraphicsComponent *graphics, GameActor &actor)
        : transform_(transform)
          , graphics_(graphics)
          , physics_(new PhysicsComponent(actor))
          , velocity_(GameManager::GAME_SPEED)
          , state_(STANDING) {}

GameActor::~GameActor() {
    delete transform_;
    delete graphics_;
    delete physics_;
}