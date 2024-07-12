#pragma once

#include "Texture.hpp"

class NullTexture : public Texture {

public:

    bool LoadTexture(const std::string &path) override;

    bool LoadTexture(const std::string &path, const TextureSize<float> &size) override;

    void RenderTexture(const Vector2<float> &position) const override;

    bool SetNativeTextureSize() override;

};