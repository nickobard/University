#pragma once

#include <unordered_map>

#include "../structures/Texture.hpp"
#include "../structures/NullTexture.hpp"
#include "../structures/TextureSize.hpp"
#include "../game_objects/Tile.hpp"

/// All texture types stored in the filesystem.
enum class TextureType {
    PACMAN, BLINKY_GHOST,
    NULL_TEXTURE, EMPTY, CROSS, TUNNEL,
    WALL_STRAIGHT, WALL_CORNER_OUTER, WALL_CORNER_INNER,
    BONUS
};

/// Namespace of all standard texture sizes used for game actors, tiles and other game object.
namespace TextureSizes {

    const TextureSize<float> ACTOR(40, 40);
    const TextureSize<float> TILE(22, 22);
    const TextureSize<float> BONUS(5, 5);
}

/**
 * @brief Game Filesystem Class which handles media loading and storage.
 * @details Stores textures and other flyweight data used across the game.
 * Handles loading and freeing data used in the game.
 */
class GameFilesystem {

public:

    /**
     * @brief Constructs Game Filesystem and instantly loads all resourses.
     */
    GameFilesystem();

    ~GameFilesystem();

    /// Gets texture from filesystem of some texture type.
    inline Texture *GetTexture(TextureType type);

private:

    /**
     * @brief Loads all textures.
     */
    void InitTextures();

    /**
     * @brief Loads texture.
     * @param type represents type of the texture to be loaded.
     * @param path represents relative path where texture lies on the disk.
     */
    void LoadTexture(TextureType type, const string &path);

    void LoadTexture(TextureType type, Texture *texture);

    /** 
     * @brief Loads all textures.
     * @param type represents type of the texture to be loaded.
     * @param path represents relative path where texture lies on the disk.
     * @param size of the rendered texture in pixels.
     */
    void LoadTexture(TextureType type, const string &path, const TextureSize<float> &size);

    /// All loaded textures.
    unordered_map<TextureType, Texture *> textures_;

};

inline Texture *GameFilesystem::GetTexture(TextureType type) {
    return textures_[type];
}

