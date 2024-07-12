#pragma once

#include "Vector2.hpp"
#include "../game_objects/Tile.hpp"

/**
 * @brief Represents connections between each adjacent tile in the map.
 */
class TileNode {

public:

    /**
     * @brief Constructs tile node object wrapping tile with pointers to adjacent nodes. O(1).
     */
    explicit TileNode(Tile *wrapped);

    /**
     * @brief Destroy tile node and wrapped tile. O(1).
     */
    ~TileNode();

    /**
     * @brief Get the type of the wrapped tile. O(1).
     * @return wrapped tile type.
     */
    inline TileType GetType() const;

    /**
     * @brief Render wrapped tile onto the screen. O(1).
     */
    inline void Render() const;

    /**
     * @brief Checks if wrapped tile is obstacle. O(1).
     * @return true if is obstacle.
     * @return false if is NOT obstacle.
     */
    [[nodiscard]]
    inline bool isObstacle() const;

    /**
     * @brief Checks if wrapped tile is tunnel.
     * @return true if is tunnel.
     * @return false if is NOT tunnel.
     */
    inline bool isTunnel() const;

    /**
     * @brief Checks if wrapped tile is portal.
     * @return true if is portal.
     * @return false if is NOT portal.
     */
    inline bool isPortal() const;

    /**
     * @brief Teleports game actor to the another portal node in the game map.
     * @param gameActor which is teleported to another tile node.
     */
    inline void Teleport(GameActor &gameActor);

    /**
     * @brief Checks if game actor object can turn right or left on the wrapped tile. O(1).
     * @param gameActor standing on the tile.
     * @return true if can turn aside.
     * @return false if can NOT turn aside.
     */
    [[nodiscard]]
    inline bool CanTurnAside(const GameActor &gameActor) const;

    /**
     * @brief Add bonus to the wrapped tile.
     * @param bonus to be added.
     * @return true if bonus was added.
     * @return flase if bonus wasn't added.
     */
    inline bool AddBonus(Bonus *bonus);

    /**
     * @brief Collect bonus from the wrapped tile.
     * @return true if bonus was collected.
     * @return false if bonus wasn't collected.
     */
    inline bool CollectBonus();

    /// Get transform component of the wrapped tile.
    inline TransformComponent *GetTransform();

    /// Get transform component of the wrapped tile.
    inline const TransformComponent *GetTransform() const;

    /// Get wrapped tile.
    inline Tile *GetTile();

    /// Get wrapped tile.
    inline const Tile *GetTile() const;

    /**
     * @brief Get next node to specified direction.
     * @param direction to which get next tile.
     * @return next tile node.
     */
    [[nodiscard]]
    TileNode *NextNode(const Vector2<float> &direction);

    /**
     * @brief Get distance between game object and its tile node center
     * according to the current game actor object direction. O(1).
     * @return offset vector from the tile node center to game object position.
     */
    static Vector2<float> GetOffsetFromNodeCenter(const GameActor &gameActor, const TileNode *node);

    /// Next TileNode to up in the game map.
    TileNode *upperNode;
    /// Next TileNode to down in the game map.
    TileNode *bottomNode;
    /// Next TileNode to right in the game map.
    TileNode *rightNode;
    /// Next TileNode to left in the game map.
    TileNode *leftNode;

private:

    /// Wrapped tile in the node.
    Tile *wrapped_;
};

inline TileType TileNode::GetType() const {
    return wrapped_->GetType();
}

inline void TileNode::Render() const {
    wrapped_->Render();
}

inline bool TileNode::isObstacle() const {
    return wrapped_->isObstacle();
}

inline bool TileNode::CanTurnAside(const GameActor &gameActor) const {
    return wrapped_->CanTurnAside(gameActor);
}

inline TransformComponent *TileNode::GetTransform() {
    return wrapped_->GetTransform();
}

inline const TransformComponent *TileNode::GetTransform() const {
    return wrapped_->GetTransform();
}

inline Tile *TileNode::GetTile() {
    return wrapped_;
}

inline const Tile *TileNode::GetTile() const {
    return wrapped_;
}

inline bool TileNode::AddBonus(Bonus *bonus) {
    return wrapped_->AddBonus(bonus);
}

inline bool TileNode::CollectBonus() {
    return wrapped_->CollectBonus();
}

bool TileNode::isTunnel() const {
    return wrapped_->isTunnel();
}

bool TileNode::isPortal() const {
    return wrapped_->isPortal();
}

void TileNode::Teleport(GameActor &gameActor) {
    wrapped_->Teleport(gameActor, *this);
}
