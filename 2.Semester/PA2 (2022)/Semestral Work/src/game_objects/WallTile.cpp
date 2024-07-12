#include "WallTile.hpp"

WallTile::WallTile(Texture * texture)
: Tile(texture)
{}

void WallTile::Render( Vector2<float> position){
  graphics_->Render(position);
} 

int WallTile::GetType(){
  return WALL_TILE;
}
