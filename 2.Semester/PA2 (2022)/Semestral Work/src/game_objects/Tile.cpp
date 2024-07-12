#include "Tile.hpp"

Tile::Tile( Texture * texture )
: graphics_(new GraphicsComponent(texture))
{}

Tile::~Tile() {
  delete graphics_;
}