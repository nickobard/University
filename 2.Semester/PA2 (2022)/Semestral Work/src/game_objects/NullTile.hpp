#pragma once

#include "Tile.hpp"

/**
 * @brief Class that represents Null tile subclass of the
 * Tile superclass.
 */
class NullTile : public Tile {

public:

    /**
     * @brief Construct a new Null Tile object.
     * @param position where tile will be rendered in the world.
     */
    NullTile(const Vector2<float> &position);

    void Render() const override;

    [[nodiscard]]
    TileType GetType() const override;

    [[nodiscard]]
    bool isObstacle() const override;

};