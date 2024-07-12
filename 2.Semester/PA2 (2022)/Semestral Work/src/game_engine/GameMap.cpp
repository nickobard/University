#include "GameMap.hpp"
#include "GameLocator.hpp"

GameMap::GameMap(){
  LoadTiles();
}

GameMap::~GameMap(){
  FreeTiles();
}

void GameMap::GenerateMap(){
  
}

void GameMap::LoadTiles(){
  
  tiles_[WALL_TILE] = new WallTile(GameLocator::GetFilesystem().GetTexture(GameLocator::GetFilesystem().WALL_TILE_TEXTURE));
  
  tiles_[EMPTY_TILE] = new WallTile(GameLocator::GetFilesystem().GetTexture(GameLocator::GetFilesystem().EMPTY_TILE_TEXTURE));

}

void GameMap::FreeTiles(){
  delete tiles_[WALL_TILE];
  delete tiles_[EMPTY_TILE];
}