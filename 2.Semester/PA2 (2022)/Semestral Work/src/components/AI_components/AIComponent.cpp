#include "AIComponent.hpp"
#include "GameLocator.hpp"

AIComponent::AIComponent(GameActor *controlled, GameActor *target)
        : ControllerComponent(controlled)
          , moveActor_(new MoveCommand())
          , chasePlayer_(new ChasePlayerCommand())
          , catchPlayer_(new CatchPlayerCommand())
          , player_(target) {}

void AIComponent::Update() {

}

AIComponent::~AIComponent() {
    delete chasePlayer_;
    delete catchPlayer_;
    delete moveActor_;
}

void AIComponent::ResetControlled() {
    auto spawnTileNode = GameLocator::GetMap().GetMapInfo().ghostsSpawn_;
    controlled_->GetPhysics()->currentNode_ = spawnTileNode;
    controlled_->SetState(MOVING);
    controlled_->GetTransform()->direction_ = Vector2<float>::Right();
    controlled_->GetTransform()->position_ = spawnTileNode->GetTransform()->position_;
}

void AIComponent::FixedUpdate() {
    catchPlayer_->Execute(controlled_, player_);
    chasePlayer_->Execute(controlled_, player_);
    moveActor_->Execute(controlled_);
    catchPlayer_->Execute(controlled_, player_);
}
