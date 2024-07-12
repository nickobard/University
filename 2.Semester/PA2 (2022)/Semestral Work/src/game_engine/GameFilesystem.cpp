#include "GameFilesystem.hpp"

GameFilesystem::GameFilesystem() {
    InitTextures();
}

GameFilesystem::~GameFilesystem() {
    for (auto [type, texture]: textures_)
        delete texture;
}


void GameFilesystem::InitTextures() {

    LoadTexture(TextureType::PACMAN, "assets/images/pacman.png", TextureSizes::ACTOR);
    LoadTexture(TextureType::BLINKY_GHOST, "assets/images/blinky_ghost.png", TextureSizes::ACTOR);
    LoadTexture(TextureType::WALL_STRAIGHT, "assets/images/wall_tile_straight.png", TextureSizes::TILE);
    LoadTexture(TextureType::WALL_CORNER_INNER, "assets/images/wall_tile_corner_inner.png", TextureSizes::TILE);
    LoadTexture(TextureType::WALL_CORNER_OUTER, "assets/images/wall_tile_corner_outer.png", TextureSizes::TILE);
    LoadTexture(TextureType::EMPTY, new NullTexture);
    LoadTexture(TextureType::CROSS, new NullTexture);
    LoadTexture(TextureType::TUNNEL, new NullTexture);
    LoadTexture(TextureType::BONUS, "assets/images/bonus.png", TextureSizes::BONUS);
}

void GameFilesystem::LoadTexture(TextureType type, const string &path) {
    auto texture = new Texture();
    if (!texture->LoadTexture(path)) {
        cerr << "Filesystem error: Could not load texture: " + path << endl;
        throw exception();
    }
    textures_.emplace(type, texture);
}

void GameFilesystem::LoadTexture(TextureType type, const string &path, const TextureSize<float> &size) {
    auto texture = new Texture();
    if (!texture->LoadTexture(path, size)) {
        cerr << "Error: Could not load texture: " + path << endl;
        throw exception();
    }
    textures_.emplace(type, texture);
}

void GameFilesystem::LoadTexture(TextureType type, Texture *texture) {
    textures_.emplace(type, texture);
}


