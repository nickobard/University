#pragma once

#include "../structures/Vector2.hpp"

class TileNode;

class GameActor;

/**
 * @brief Component which resolves physics aspects of the game object.
 * Resolves collisions and interaction with other game objects,
 * while transform component only represents position in the world.
 */
class PhysicsComponent {

public:

    /**
     * @brief Constructs this physics component. O(1).
     * @param gameActor reference to game object where this component belongs to.
     */
    explicit PhysicsComponent(GameActor &gameActor);

    /**
     * @brief Check if next tile is obstacle. O(1).
     * @param direction from which to check next tile to this position.
     * @return true if next tile is obstacle.
     * @return false if next tile is NOT obstacle.
     */
    [[nodiscard]]
    bool TouchesObstacle(const Vector2<float> &direction) const;

    /**
     * @brief Checks if current game object is on the next tile. O(1).
     * @return true if game object is on the next tile.
     * @return false if game object is NOT on the next tile.
     */
    [[nodiscard]]
    bool isOnNextTile() const;

    /**
     * @brief Translates object to its current direction resolving collisions. O(1).
     * @param newPosition of the game object if no collisions occurs.
     */
    void Move(Vector2<float> newPosition);

    /// Current tile node where the game actor object is standing now.
    TileNode *currentNode_;

private:

    /**
     * @brief Check is this game object doesn't go out of screen bounds. O(1).
     * @param newPosition to check if on this position is out of bounds.
     * If is out of bounds change it back to normal position.
     */
    void ResolveOutOfScreenBounds(Vector2<float> &newPosition);

    /**
     * @brief Checks collisions and updates new position according to collision. O(1).
     * @param newPosition to check collisions
     */
    void ResolveCollisions(Vector2<float> &newPosition);

    /**
     * @brief Check if new position collides with obstacles. O(1).
     * @param oldPosition of the object before it moved.
     * @param newPosition of the object to check collision.
     */
    void ResolveObstacles(const Vector2<float> &oldPosition, Vector2<float> &newPosition);

    /// Game Object to which this component is attached.
    GameActor &gameActor_;
    /// True if static collision were already resolved until next tile.
    bool resolvedObstaclesCollision;
};
