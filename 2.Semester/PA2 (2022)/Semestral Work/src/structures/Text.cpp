#include "Text.hpp"
#include "../game_engine/GameLocator.hpp"

Text::Text()
        : font_(nullptr)
          , fontSize_(DefaultFontSize)
          , color_(TextColors::WHITE) {}

Text::~Text() {
    DestroyFont();
}

bool Text::LoadTexture(const string &msg) {

    auto textSurface = TTF_RenderText_Solid(font_, msg.c_str(), color_);
    if (textSurface == nullptr) {
        cerr << "Text '" + msg + "' with size " << fontSize_ << " could not be loaded! " <<
             "SDL_ttf Error: " << TTF_GetError() << endl;
        return false;
    }

    auto texture = SDL_CreateTextureFromSurface(GameLocator::GetRenderer(), textSurface);
    if (texture == nullptr) {
        cerr << "Texture from text '" + msg + "' with size " << fontSize_ << " could not be loaded! " <<
             "SDL Error: " << SDL_GetError() << endl;
        SDL_FreeSurface(textSurface);
        return false;
    }

    SetTextureSize(TextureSize<float>(textSurface->w, textSurface->h));
    SDL_FreeSurface(textSurface);
    DestroyTexture();
    texture_ = texture;
    text_ = msg;
    return true;
}

bool Text::LoadTexture(const string &msg, const TextureSize<float> &size) {

    auto textSurface = TTF_RenderText_Solid(font_, msg.c_str(), color_);
    if (textSurface == nullptr) {
        cerr << "Text '" + msg + "' with size " << fontSize_ << " could not be loaded! " <<
             "SDL_ttf Error: " << TTF_GetError() << endl;
        return false;
    }

    auto texture = SDL_CreateTextureFromSurface(GameLocator::GetRenderer(), textSurface);
    if (texture == nullptr) {
        cerr << "Texture from text '" + msg + "' with size " << fontSize_ << " could not be loaded! " <<
             "SDL Error: " << SDL_GetError() << endl;
        SDL_FreeSurface(textSurface);
        return false;
    }

    SDL_FreeSurface(textSurface);

    SetTextureSize(size);
    DestroyTexture();
    texture_ = texture;
    text_ = msg;
    return true;
}

void Text::RenderTexture(const Vector2<float> &position) const {
    SDL_FRect renderRect = CreateRenderRect(position);
    SDL_RenderCopyF(GameLocator::GetRenderer(), texture_, nullptr, &renderRect);
}

void Text::RenderTexture(const Vector2<float> &position, double angle) const {
    SDL_FRect renderRect = CreateRenderRect(position);
    SDL_RenderCopyExF(GameLocator::GetRenderer(), texture_, nullptr, &renderRect, angle, nullptr, SDL_FLIP_NONE);
}

void Text::DestroyFont() {
    if (font_ != nullptr) {
        TTF_CloseFont(font_);
        font_ = nullptr;
    }
}

bool Text::LoadFont(const string &path, size_t fontSize) {
    auto font = TTF_OpenFont(path.c_str(), fontSize);
    if (font == nullptr) {
        cerr << "Font " + path + "could not be loaded! SDL_ttf Error: " << TTF_GetError() << endl;
        return false;
    }

    DestroyFont();
    font_ = font;
    fontSize_ = fontSize;
    return true;
}

bool Text::LoadText(const string &msg, SDL_Color color) {
    auto lastColor = color_;
    color_ = color;

    if (!LoadTexture(msg)) {
        color_ = lastColor;
        return false;
    }

    text_ = msg;
    return true;
}

bool Text::LoadText(const string &msg, SDL_Color color, const TextureSize<float> &size) {

    auto lastColor = color_;
    color_ = color;

    if (!LoadTexture(msg, size)) {
        color_ = lastColor;
        return false;
    }
    text_ = msg;
    return true;
}

SDL_FRect Text::CreateRenderRect(const Vector2<float> &position) const {
    return {position.x_, position.y_,
            size_.width_, size_.height_};
}


