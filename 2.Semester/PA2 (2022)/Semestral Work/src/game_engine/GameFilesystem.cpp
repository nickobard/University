#include "GameFilesystem.hpp"

GameFilesystem::GameFilesystem()
{
  InitTextures();
  LoadTextures();
}

GameFilesystem::~GameFilesystem(){
  FreeTextures();
}

void GameFilesystem::LoadTextures(){
  LoadTexture(textures_[PACMAN_TEXTURE],"assets/pacman.png",{40,40});
  LoadTexture(textures_[GHOST_TEXTURE],"assets/ghost.png",{40,40});
  LoadTexture(textures_[WALL_TILE_TEXTURE],"assets/walltile.png",{20,20});
  LoadTexture(textures_[EMPTY_TILE_TEXTURE],"assets/emptytile.png",{20,20});
}

void GameFilesystem::FreeTextures(){
  for ( size_t texture = 0; texture < MAX_TEXTURES_NUMBER; texture++ ){
    if (notNullTexture(textures_[texture]))
      delete textures_[texture]; 
  }
}

void GameFilesystem::LoadTexture(Texture *& texture, const string & path){
  texture = new Texture;
  if ( !texture->LoadTexture(path)){
    delete texture;
    texture = &nullTexture_;
  }
}

void GameFilesystem::LoadTexture(Texture *& texture, const string & path, const TextureSize<float> & size){
  texture = new Texture;
  if ( !texture->LoadTexture(path, size)){
    delete texture;
    texture = &nullTexture_;
  }
}

bool GameFilesystem::notNullTexture(Texture * texture) const {
  return texture != &nullTexture_;
}

void GameFilesystem::InitTextures(){
  for ( size_t texturePosition = 0; texturePosition < MAX_TEXTURES_NUMBER; texturePosition++ )
    textures_[texturePosition] = &nullTexture_;
}