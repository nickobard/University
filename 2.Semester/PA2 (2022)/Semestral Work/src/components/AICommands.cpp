#include "AICommands.hpp"
#include "../game_engine/GameLocator.hpp"

void ChasePlayerCommand::Execute(GameActor *controlled, GameActor *target) {
    controlled_ = controlled;
    player_ = target;

    CheckTile();
}

void ChasePlayerCommand::CheckTile() {
    auto currentNode = controlled_->GetPhysics()->currentNode_;
    if (decidedNode_ == currentNode)
        return;
    if (currentNode->CanTurnAside(*controlled_)) {
        controlled_->TurnTo(DecideDirection());
        decidedNode_ = currentNode;
    }
}

Vector2<float> ChasePlayerCommand::DecideDirection() {

    auto decision = make_pair(Vector2<float>::Zero(), 0.0f);

    CheckDirection(controlled_->GetTransform()->direction_, decision);
    CheckDirection(controlled_->GetTransform()->direction_.ToRight(), decision);
    CheckDirection(controlled_->GetTransform()->direction_.ToLeft(), decision);

    if (decision.first == Vector2<float>::Zero())
        return controlled_->GetTransform()->direction_.ToBack();
    else
        return decision.first;
}

void ChasePlayerCommand::CheckDirection(const Vector2<float> &direction, pair<Vector2<float>, float> &decision) const {
    auto nextTile = controlled_->GetPhysics()->currentNode_->NextNode(direction);
    if (!nextTile->isObstacle()) {
        float dis = Vector2<float>::Distance(nextTile->GetTransform()->position_, player_->GetTransform()->position_);
        if (decision.first == Vector2<float>::Zero() || dis < decision.second) {
            decision = {direction, dis};
        }
    }
}

void CatchPlayerCommand::Execute(GameActor *controlled, GameActor *target) {
    if (controlled->GetPhysics()->currentNode_ == target->GetPhysics()->currentNode_) {
        GameLocator::GetManager().ReportPlayerCollision();
    }
}
