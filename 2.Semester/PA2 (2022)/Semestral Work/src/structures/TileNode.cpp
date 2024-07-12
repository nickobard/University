#include "TileNode.hpp"

TileNode::TileNode(Tile *wrapped)
        : upperNode(nullptr)
          , bottomNode(nullptr)
          , rightNode(nullptr)
          , leftNode(nullptr)
          , wrapped_(wrapped) {

}

TileNode::~TileNode() {
    delete wrapped_;
}

TileNode *TileNode::NextNode(const Vector2<float> &direction) {

    if (direction == Vector2<float>::Up())
        return upperNode;
    else if (direction == Vector2<float>::Down())
        return bottomNode;
    else if (direction == Vector2<float>::Right())
        return rightNode;
    else if (direction == Vector2<float>::Left())
        return leftNode;
    else
        return this;
}

Vector2<float> TileNode::GetOffsetFromNodeCenter(const GameActor &gameActor, const TileNode *node) {
    return Tile::GetOffsetFromTileCenter(gameActor, node->GetTile());
}