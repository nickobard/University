#pragma once
#include "../structures/Texture.hpp"
#include "../structures/TextureSize.hpp"
#include "../game_objects/Tile.hpp"

/**
 * @brief Game Filesystem Class which handles media loading and storage.
 * 
 * @details Stores textures and other flyweight data used across the game.
 * Handles loading and freeing data used in the game.
 */
class GameFilesystem {

  public:

    /**
     * @brief All texture types stored in the filesystem.
     * 
     */
    enum TextureTypes {
      PACMAN_TEXTURE,
      GHOST_TEXTURE,
      WALL_TILE_TEXTURE,
      EMPTY_TILE_TEXTURE
    };

    /**
     * @brief Constructs Game Filesystem and instantly loads all resourses.
     * 
     */
    GameFilesystem();

    /**
     * @brief Destroys all resources, deallocating them.
     * 
     */
    ~GameFilesystem();

    /**
     * @brief Gets Pacman Texture.
     * 
     * @return Texture * texture of the pacman
     */
    inline Texture * GetTexture( const int type );

  private:

    /**
     * @brief Allocates and loads textures for the game.
     * 
     */
    void LoadTextures();

    /**
     * @brief Frees all allocated textures.
     * 
     */
    void FreeTextures();

    /**
     * @brief Inits all textures with null texture.
     * 
     */
    void InitTextures();


    /**
     * @brief Loads texture.
     * 
     * @param texture pointer to the texture which should be loaded.
     * @param path relative path where texture lies on the disk.
     */
    void LoadTexture(Texture *& texture, const string & path);

    
    /** 
     * @brief Loads texture.
     * @details If not loaded texture, assign nullTexture
     * @param texture pointer to the texture which should be loaded.
     * @param path relative path where texture lies on the disk.
     * @param size of the rendered texture in pixels.
     */
    void LoadTexture(Texture *& texture, const string & path, const TextureSize<float> & size);


    /**
     * @brief Check if texture wasn't set to null texture because of failed loading.
     * 
     * @param texture texture to be checked if is nullTexture. 
     * @return true if it is a null texture.
     * @return false if it is NOT a null texture.
     */
    bool notNullTexture(Texture * texture) const;


    // Maximum number of textures in the game.
    static constexpr size_t MAX_TEXTURES_NUMBER = 4;

    // Null Texture if not successfuly loaded some texture.
    Texture   nullTexture_;

    // Pacman character texture.
    Texture * textures_ [MAX_TEXTURES_NUMBER];

};

inline
Texture * GameFilesystem::GetTexture( const int type ){
  return textures_[type];
}