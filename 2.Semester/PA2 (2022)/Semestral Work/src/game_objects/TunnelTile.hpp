#pragma once

#include "EmptyTile.hpp"

class TunnelTile : public EmptyTile {
public:
    /**
     * @brief Construct a new Tunnel Tile object.
     * @param texture for graphics component to render the tile.
     * @param position where tile will be rendered in the world.
     */
    TunnelTile(Texture *texture, const Vector2<float> &position);

    TileType GetType() const override;

    bool isTunnel() const override;

};

