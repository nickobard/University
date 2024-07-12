#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

using namespace std;

#include "Vector2.hpp"
#include "TextureSize.hpp"

/**
 * @brief Texture wrapper class around SDL's texture.
 */
class Texture {

public:

    /**
     * @brief Construct and inits sdl texture with nullptr and width and height with 0. O(1).
     */
    Texture();

    /**
     * @brief Deletes texture. Use DestroyTexture to safely destroy sdl texture. O(1).
     */
    ~Texture() noexcept;

    /**
     * @brief Deleted copy constructor.
     */
    Texture(const Texture &src) = delete;

    /**
     * @brief Move constructor.
     */
    Texture(Texture &&src) noexcept;

    /**
     * @brief Loads texture from .png image and applies it for renderer. O(1).
     * @param path to the loaded image.
     * @return true if successfully loaded texture.
     * @return false if failed to load texture.
     */
    bool LoadTexture(const string &path);

    /**
     * @brief Loads texture from .png image and applies it for renderer. O(1).
     * @param path to the loaded image.
     * @param size of the texture.
     * @return true if successfully loaded texture.
     * @return false if failed to load texture.
     */
    bool LoadTexture(const string &path, const TextureSize<float> &size);

    /**
     * @brief Render this texture on the screen by renderer. O(1).
     * @param position in pixels where to show image on the screen.
     */
    void RenderTexture(const Vector2<float> &position) const;

    /**
     * @brief Queries texture for its native image dimensions
     * and sets the size of the texture in pixels. O(1).
     * @return true if successfully set up native size.
     * @return false if failed to query image size and set it up.
     */
    bool SetNativeTextureSize();

    /**
     * @brief Set texture dimensions using user defined size in pixels. O(1).
     * @param size to set to this texture.
     */
    inline void SetTextureSize(const TextureSize<float> &size);

    /**
     * @brief Get texture size of this texture. O(1).
     * @return reference to const texture size.
     */
    [[nodiscard]]
    inline const TextureSize<float> &GetSize() const;

private:

    /**
     * @brief Create SDL float rectangle object from center position.
     * Uses texture size to find left upper corner where SDL rect should
     * be defined for rendering. O(1).
     * @param position center of the game object position.
     * @return SDL_FRect rectangle structure prepared for rendering.
     */
    [[nodiscard]]
    SDL_FRect CreateRenderRect(const Vector2<float> &position) const;

    /**
     * @brief Destroys current texture and prepares for loading another texture. O(1).
     */
    void DestroyTexture();

    /// Object to store and handle textures in SDL.
    SDL_Texture *texture_;
    /// Dimensions of the loaded texture (of the image) in pixels
    TextureSize<float> size_;
};

inline void Texture::SetTextureSize(const TextureSize<float> &size) {
    size_ = size;
}

inline const TextureSize<float> &Texture::GetSize() const {
    return size_;
}
