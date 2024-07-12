#include "EmptyTile.hpp"

EmptyTile::EmptyTile(Texture * texture)
: Tile(texture)
{}

void EmptyTile::Render( Vector2<float> position){
  graphics_->Render(position);
} 

int EmptyTile::GetType(){
  return EMPTY_TILE;
}
