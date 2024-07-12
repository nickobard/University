#pragma once

#include "../components/GraphicsComponent.hpp"
#include "../components/TransformComponent.hpp"
#include "GameActor.hpp"
#include "Bonus.hpp"

/// Enum representing all types of tiles in the game.
enum class TileType {
    NONE, EMPTY, WALL, CROSS, TUNNEL, PORTAL

};

/// Enum that represents option features of tiles.
enum class TileOption {
    NONE, BONUS, BIG_BONUS, CHERRY,
    INNER_WALL_CORNER, OUTER_WALL_CORNER
};

/**
 * @brief Abstract class representing Tiles in the map.
 * 
 */
class Tile : public GameObject {

public:

    /**
     * @brief Construct a new Tile object. O(1).
     * @param texture texture to construct graphics component.
     * @param position of the tile in the map in pixels.
     */
    Tile(Texture *texture, const Vector2<float> &position);

    /**
     * @brief Destroys the Tile object. O(1).
     */
    ~Tile() override;

    /**
     * @brief Get the type of the tile. O(1).
     * @return type of the tile.
     */
    [[nodiscard]]
    virtual TileType GetType() const = 0;

    /**
     * @brief Render the tile on the game map. O(1).
     */
    virtual void Render() const;

    void Update() override;

    /**
     * @brief Check if this tile is obstacle or not. O(1).
     * @return true if tile is obstacle.
     */
    [[nodiscard]]
    virtual bool isObstacle() const;

    /**
     * @brief Check if this tile is tunnel.
     * @return true if is tunnel.
     */
    [[nodiscard]]
    virtual bool isTunnel() const;

    /**
     * @brief Check if this tile is portal.
     * @return true if is portal.
     */
    [[nodiscard]]
    virtual bool isPortal() const;

    /**
     * @brief Moves game actor transform and its current tile to another connected portalNode.
     * @param gameActor to be moved to another portalNode.
     * @param portalNode represents tile node of the portalNode, which teleports now the game actor.
     */
    virtual void Teleport(GameActor &gameActor, TileNode &portalNode);

    /**
     * @brief Check if game object standing on this tile can turn to the side, right or left or not. O(1).
     * @param gameActor standing on this tile and trying to turn to another direction.
     * @return true if game object can turn aside.
     */
    [[nodiscard]]
    virtual bool CanTurnAside(const GameActor &gameActor) const;

    /**
     * @brief Add bonus to tile.
     * @param bonus to be added to tile.
     * @return true if bonus was successfully added.
     */
    virtual bool AddBonus(Bonus *bonus);

    /**
     * @brief Collect bonus from tile.
     * @return true if successfully collected bonus.
     */
    virtual bool CollectBonus();

    /**
     * @brief Get distance between game object and its tile center according to the current direction. O(1).
     * @return offset vector from tile center to game object position.
     */
    [[nodiscard]]
    static Vector2<float> GetOffsetFromTileCenter(const GameActor &gameActor, const Tile *tile);

    /// Get Transform component of the tile. O(1).
    [[nodiscard]]
    inline TransformComponent *GetTransform();

    /// Get Transform component of the tile. O(1).
    [[nodiscard]]
    inline const TransformComponent *GetTransform() const;

protected:

    /// Graphics component of the tile class.
    GraphicsComponent *graphics_;
    /// Transform component of the tile class.
    TransformComponent *transform_;
};

inline TransformComponent *Tile::GetTransform() {
    return transform_;
}

inline const TransformComponent *Tile::GetTransform() const {
    return transform_;
}
