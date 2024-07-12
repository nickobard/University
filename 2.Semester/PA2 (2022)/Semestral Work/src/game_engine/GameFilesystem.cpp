#include "GameFilesystem.hpp"

GameFilesystem::GameFilesystem() {
    InitTextures();
}

void GameFilesystem::InitTextures() {

    LoadTexture(TextureType::PACMAN, "assets/pacman.png", TextureSizes::ACTOR);
    LoadTexture(TextureType::GHOST, "assets/ghost.png", TextureSizes::ACTOR);
    LoadTexture(TextureType::WALL, "assets/walltile.png", TextureSizes::TILE);
    LoadTexture(TextureType::EMPTY, "assets/void.png", TextureSizes::TILE);
    LoadTexture(TextureType::CROSS, "assets/void.png", TextureSizes::TILE);
    LoadTexture(TextureType::TUNNEL, "assets/void.png", TextureSizes::TILE);
    LoadTexture(TextureType::BONUS, "assets/bonus.png", TextureSizes::BONUS);
}

void GameFilesystem::LoadTexture(TextureType type, const string &path) {
    Texture newTexture;
    if (!newTexture.LoadTexture(path)) {
        cerr << "Filesystem error: Could not load texture: " + path << endl;
        throw exception();
    }
    textures_.emplace(type, std::move(newTexture));
}

void GameFilesystem::LoadTexture(TextureType type, const string &path, const TextureSize<float> &size) {
    Texture newTexture;
    if (!newTexture.LoadTexture(path, size)) {
        cerr << "Error: Could not load texture: " + path << endl;
        throw exception();
    }
    textures_.emplace(type, std::move(newTexture));
}

