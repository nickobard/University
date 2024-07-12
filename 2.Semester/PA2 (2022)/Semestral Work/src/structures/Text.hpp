#pragma once

#include "Texture.hpp"
#include <SDL2/SDL_ttf.h>



namespace TextColors {
    constexpr SDL_Color WHITE = {0xFF, 0xFF, 0xFF, 0xFF};
    constexpr SDL_Color BLACK = {0x00, 0x00, 0x00, 0xFF};
}

class Text : public Texture {
public:

    Text();

    ~Text() override;

    Text(const Text &src) = delete;

    bool LoadFont(const string &path, size_t fontSize = DefaultFontSize);

    bool LoadText(const string &msg, SDL_Color color);

    bool LoadText(const string &msg, SDL_Color color, const TextureSize<float> &size);

    bool LoadTexture(const string &msg) override;

    bool LoadTexture(const string &msg, const TextureSize<float> &size) override;

    void RenderTexture(const Vector2<float> &position) const override;

    void RenderTexture(const Vector2<float> &position, double angle) const override;

    static constexpr size_t DefaultFontSize = 16;

private:

    SDL_FRect CreateRenderRect(const Vector2<float> &position) const;

    void DestroyFont();

    TTF_Font * font_ ;
    size_t fontSize_;
    SDL_Color color_;
    string text_;

};