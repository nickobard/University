#pragma once

#include "Tile.hpp"

/**
 * @brief Class that represents Empty tile subclass of the
 * Tile superclass.
 */
class EmptyTile : public Tile {

public:

    /**
     * @brief Construct a new Empty Tile object.
     * @param texture for graphics component to render the tile.
     * @param position where tile will be rendered in the world.
     */
    EmptyTile(Texture *texture, const Vector2<float> &position);

    ~EmptyTile() override;

    void Render() const override;

    bool AddBonus(Bonus *bonus) override;

    bool CollectBonus() override;

    [[nodiscard]]
    TileType GetType() const override;

    [[nodiscard]]
    bool CanTurnAside(const GameActor &gameActor) const override;

protected:

    /// Bonus on the tile.
    Bonus *bonus_;

};