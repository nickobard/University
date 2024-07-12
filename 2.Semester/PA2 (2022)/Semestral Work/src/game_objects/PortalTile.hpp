#pragma once

#include "TunnelTile.hpp"

class PortalTile : public TunnelTile {
public:

    /**
     * @brief Constructs portal tile.
     * @param texture of the tile.
     * @param position of the tile in the game map.
     * @param direction where is the exit from the portal, not entrance.
     */
    PortalTile(Texture *texture, const Vector2<float> &position, const Vector2<float> &direction);

    TileType GetType() const override;

    bool isPortal() const override;

    void Teleport(GameActor &gameActor, TileNode &portal) override;
};