#pragma once

#include "Tile.hpp"
#include "EmptyTile.hpp"

/**
 * @brief Class that represents Cross tile subclass of the
 * Tile superclass.
 */
class CrossTile : public EmptyTile {

public:

    /**
     * @brief Construct a new Empty Cross object.
     * @param texture for graphics component to render the tile.
     * @param position of the tile in the world.
     */
    CrossTile(Texture *texture, const Vector2<float> &position);

    void Render() const override;

    [[nodiscard]]
    bool CanTurnAside(const GameActor &gameActor) const override;

    [[nodiscard]]
    TileType GetType() const override;

private:

    /**
     * @brief Check if game object is in the center by threshold values. O(1).
     * @param obj game actor object standing on this tile.
     * @return true if is within threshold.
     * @return false if is NOT within threshold.
     */
    [[nodiscard]]
    bool isInThreshold(const GameActor &obj) const;

    /// Threshold when object is going to the center of the tile.
    static constexpr int IN_THRESHOLD = 5;
    /// Threshold when object is going away from center of the tile.
    static constexpr int OUT_THRESHOLD = 2;
};