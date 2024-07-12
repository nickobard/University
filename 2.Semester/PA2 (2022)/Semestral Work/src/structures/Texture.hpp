#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

using namespace std;

#include "Vector2.hpp"
#include "TextureSize.hpp"

// Texture wrapper class around SDL's texture.
class Texture {
  public:
    // Inits texture with nullptr and width and height with 0.
    Texture();
    // Use FreeTexture to free texture for safe destruction.
    ~Texture();
    // @brief Loads texture from .png image and applies it for renderer.
    // @param path path to the loaded image.
    bool LoadTexture(const string & path);
    // @brief Loads texture from .png image and applies it for renderer.
    // @param path path to the loaded image.
    // @param size dimensions of the texture. 
    bool LoadTexture(const string & path, const TextureSize<float> & size);
    // @brief Render this texture on the screen by renderer
    // @param position - position where to put image on the screen in pixels.
    void RenderTexture(const Vector2<float> & position) const;
    // Queries texture for its native image dimensions
    // and sets the size of the texture in pixels.
    bool SetNativeTextureDimensions ();
    // Set texture dimensions using user defined size in pixels.
    inline void SetTextureDimensions (const TextureSize<float> & size);
  private:
    // Creates geometry where to render the texture on the screen. 
    SDL_FRect CreateRenderRect(const Vector2<float> & position) const;
    // Destroys current texture and sets members to nullptr and 0.
    void FreeTexture();
    // Object to store and handle textures in SDL
    SDL_Texture * texture_;
    // Dimensions of the loaded texture (of the image) in pixels
    TextureSize<float> size_;
};

inline
void Texture::SetTextureDimensions (const TextureSize<float> & size){
  size_ = size;
}