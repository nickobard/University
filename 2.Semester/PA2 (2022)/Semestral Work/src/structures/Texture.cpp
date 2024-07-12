#include "Texture.hpp"
#include "../game_engine/GameLocator.hpp"

Texture::Texture()
        : texture_(nullptr) {}

Texture::~Texture() noexcept {
    DestroyTexture();
}

Texture::Texture(Texture &&src) noexcept
        : texture_(nullptr) {
    std::swap(texture_, src.texture_);
    size_ = src.size_;
}

bool Texture::LoadTexture(const string &path, const TextureSize<float> &size) {
    auto texture = IMG_LoadTexture(GameLocator::GetRenderer(), path.c_str());
    if (texture == nullptr) {
        cerr << "Texture " + path + " could not be loaded!"
                                    " SDL_image Error: " << SDL_GetError() << endl;
        return false;
    }

    DestroyTexture();
    texture_ = texture;
    SetTextureSize(size);
    return true;
}

bool Texture::LoadTexture(const string &path) {

    auto texture = IMG_LoadTexture(GameLocator::GetRenderer(), path.c_str());
    if (texture == nullptr) {
        cerr << "Texture " + path + " could not be loaded!"
                                    " SDL_image Error: " << SDL_GetError() << endl;
        return false;
    }
    if (!SetNativeTextureSize()) {
        cerr << "Texture native dimensions could not be loaded! "
                " SDL Error: " << SDL_GetError() << endl;
        SDL_DestroyTexture(texture);
        return false;
    }

    DestroyTexture();
    texture_ = texture;
    return true;
}

bool Texture::SetNativeTextureSize() {
    int w = 0, h = 0;
    if (SDL_QueryTexture(texture_, nullptr, nullptr, &w, &h) != 0)
        return false;
    size_.width_ = static_cast<float>(w);
    size_.height_ = static_cast<float>(h);
    return true;
}

SDL_FRect Texture::CreateRenderRectCentered(const Vector2<float> &position) const {
    return {position.x_ - size_.width_ / 2,
            position.y_ - size_.height_ / 2,
            size_.width_, size_.height_};
}

void Texture::RenderTexture(const Vector2<float> &position) const {
    SDL_FRect renderRect = CreateRenderRectCentered(position);
    SDL_RenderCopyF(GameLocator::GetRenderer(), texture_, nullptr, &renderRect);
}

void Texture::DestroyTexture() {
    if (texture_ != nullptr) {
        SDL_DestroyTexture(texture_);
        texture_ = nullptr;
    }
}

void Texture::RenderTexture(const Vector2<float> &position, double angle) const {
    SDL_FRect renderRect = CreateRenderRectCentered(position);
    SDL_RenderCopyExF(GameLocator::GetRenderer(), texture_, nullptr, &renderRect, angle, nullptr, SDL_FLIP_NONE);
}




