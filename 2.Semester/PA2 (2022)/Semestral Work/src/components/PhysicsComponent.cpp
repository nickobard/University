#include "PhysicsComponent.hpp"
#include "../game_objects/GameActor.hpp"
#include "../structures/TileNode.hpp"
#include "../game_engine/GameLocator.hpp"

PhysicsComponent::PhysicsComponent(GameActor &gameActor)
        : currentNode_(nullptr)
          , gameActor_(gameActor)
          , resolvedObstaclesCollision(false) {
}

void PhysicsComponent::Move(Vector2<float> newPosition) {

    ResolveCollisions(newPosition);
    gameActor_.GetTransform()->Translate(newPosition);

    if (isOnNextTile()) {
        resolvedObstaclesCollision = false;
        currentNode_ = currentNode_->NextNode(gameActor_.GetTransform()->direction_);
    }

    if (currentNode_->isPortal()) {
        currentNode_->Teleport(gameActor_);
    }

}


void PhysicsComponent::ResolveOutOfScreenBounds(Vector2<float> &newPosition) {

    auto textureSizeOffset = gameActor_.GetGraphics()->GetTextureSize() / 2;

    if (auto rightBound = static_cast<float>(SCREEN_WIDTH) - textureSizeOffset.width_; newPosition.x_ > rightBound)
        newPosition.x_ = rightBound;
    else if (auto leftBound = 0.0f + textureSizeOffset.width_; newPosition.x_ < leftBound)
        newPosition.x_ = leftBound;

    if (auto upperBound = static_cast<float>(SCREEN_HEIGHT) - textureSizeOffset.height_; newPosition.y_ > upperBound)
        newPosition.y_ = upperBound;
    else if (auto bottomBound = 0.0f + textureSizeOffset.height_; newPosition.y_ < bottomBound)
        newPosition.y_ = bottomBound;
}

void PhysicsComponent::ResolveCollisions(Vector2<float> &newPosition) {

    auto oldPosition = gameActor_.GetTransform()->position_;

    ResolveOutOfScreenBounds(newPosition);
    ResolveObstacles(oldPosition, newPosition);

}

void PhysicsComponent::ResolveObstacles(const Vector2<float> &oldPosition, Vector2<float> &newPosition) {

    if (resolvedObstaclesCollision)
        return;

    auto offset = TileNode::GetOffsetFromNodeCenter(gameActor_, currentNode_);

    if (offset >= Vector2<float>::Zero()) {
        if (TouchesObstacle(gameActor_.GetTransform()->direction_))
            newPosition = currentNode_->GetTransform()->position_;
        else
            resolvedObstaclesCollision = true;
    }
}

bool PhysicsComponent::TouchesObstacle(const Vector2<float> &direction) const {
    auto nextTileNode = currentNode_->NextNode(direction);
    return nextTileNode->isObstacle();
}

bool PhysicsComponent::isOnNextTile() const {
    auto offset = TileNode::GetOffsetFromNodeCenter(gameActor_, currentNode_);
    auto threshold = Vector2<float>::Abs(gameActor_.GetTransform()->direction_) * TILE_SIZE / 2;
    return offset > threshold;
}
